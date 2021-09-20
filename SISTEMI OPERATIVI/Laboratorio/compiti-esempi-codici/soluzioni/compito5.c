//2016 04 27

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define BUFSIZE 1024
#define DIM 10  

#define MUTEX 0
#define EMPTY 1
#define FULL 2
#define FULL_RES 3

enum tipoDato { NUMERO, RESIDUO , VUOTO, T_EOF};

typedef struct{
    long numero;
    char tipo;
}record;


int WAIT(int sem_des, int num_semaforo){
    struct sembuf operazioni[1] = {{num_semaforo,-1,0}};
    return semop(sem_des, operazioni, 1);
}

int SIGNAL(int sem_des, int num_semaforo){
    struct sembuf operazioni[1] = {{num_semaforo,+1,0}};
    return semop(sem_des, operazioni, 1);
}

int ciao=0;
void figlioM(int sem_ds,record* lista,int modulo)
{
    int eof=0;
    int i;
    while (1)
    {
        WAIT(sem_ds,FULL);
        WAIT(sem_ds,MUTEX);
       // printf("figlioM dentro %d\n",ciao);
        ciao++;
        for (i = 0; i < DIM; i++)
        {
            if (lista[i].tipo==NUMERO)
            {
                lista[i].numero=lista[i].numero % modulo;
                lista[i].tipo=RESIDUO;
            }
            else if (lista[i].tipo==T_EOF)
            {
                eof=1;
            }
        }
        SIGNAL(sem_ds,MUTEX);
        SIGNAL(sem_ds,FULL_RES);
        if (eof==1 && i==DIM)
        {
            break;
        }
    }

    exit(0);
}

void figlioO(int sem_ds,record* lista)
{
    int eof=0;
    int i=0;
    while (1)
    {
        WAIT(sem_ds,FULL_RES);
        WAIT(sem_ds,MUTEX);
      //  printf("figlioO dentro\n");
        for ( i = 0; i < DIM; i++)
        {
            if (lista[i].tipo==RESIDUO)
            {
                lista[i].tipo=VUOTO;
                printf("%ld\n",lista[i].numero);
            }
            else if (lista[i].tipo==T_EOF)
            {
                eof=1;
            }
            
        }

        SIGNAL(sem_ds,MUTEX);
        SIGNAL(sem_ds,EMPTY);

        if (eof==1 && i==DIM)
        {
            break;
        }
    }
    
    exit(0);
}



int main(int argc,char* argv[])
{
    FILE* file_input;
    struct stat statbuf;
    int modulo;
    int memoria;
    record* lista;
    int sem_ds;
    if (argc!=3)
    {
        perror("errore nei parametri");
        exit(1);
    }

    //vedere se il file è regolare
    if ((lstat(argv[1],&statbuf)==-1) || !S_ISREG(statbuf.st_mode))
    {
        perror(argv[1]); //file non apribile
        exit(1);
    }
    
    modulo=atol(argv[2]);
    if (modulo<=0)
    {
        perror("modulo non valido");
        exit(1);
    }
    
    //creare memoria condivisa
    if ((memoria=shmget(IPC_PRIVATE, sizeof(record)*DIM, IPC_CREAT | 0660))==-1)
    {
        perror("SHMGET");
        exit(1);
    }
    //memoria condivisa creata, attacchiamola

    //riporta all'indirizzo di inizio
    if ((lista=(record*)shmat(memoria,NULL, 0))==(record*)-1)
    {
        perror("shmat");
        exit(1);
    }

    //creare i semafori
    if ((sem_ds=semget(IPC_PRIVATE,4,IPC_CREAT |0660))==-1)
    {
        perror("semget");
        exit(1);
    }

    if ( semctl(sem_ds,MUTEX,SETVAL,1)==-1)
    {
        perror("semctl1");
        exit(1);
    }

      if (semctl(sem_ds,EMPTY,SETVAL,DIM)==-1)
    {
        perror("semctl2");
        exit(1);
    }

      if (semctl(sem_ds,FULL,SETVAL,0)==-1)
    {
        perror("semctl3");
        exit(1);
    }

      if (semctl(sem_ds,FULL_RES,SETVAL,0)==-1)
    {
        perror("semctl4");
        exit(1);
    }
    
    //semafori e memoria condivisa creati
    //creare figli
    int pidM;
    int pidO;
    
    if ((pidM=fork())==0)
    {
        //figlio M
        figlioM(sem_ds,lista,modulo);
    }
    else if ((pidO=fork())==0)
    {
        figlioO(sem_ds,lista);
    }
    else
    {
        //padre prende numeri dal file e li mette in memoria condivisa
        //Mettiamo tutti i dati a vuoto
        for (int i = 0; i < DIM; i++)
        {
            lista[i].tipo=VUOTO;
        }
        //apriamo il file
        file_input=fopen(argv[1],"r");

        //il padre legge da file_input e mette su shared mem
        char buffer[BUFSIZE];
        long numero;

        while (fgets(buffer,BUFSIZE,file_input))
        {
            if (buffer[strlen(buffer)-1]=='\n')
            {
                buffer[strlen(buffer)-1]='\0';
            }
            numero=atol(buffer);

           // printf("padre aspetta per mettere roba dentro\n");
            WAIT(sem_ds,EMPTY);
            WAIT(sem_ds,MUTEX);

            //Cerchiamo locazione vuota
            for (int i = 0; i < DIM; i++)
            {
                if (lista[i].tipo==VUOTO)
                {
                    lista[i].tipo=NUMERO;
                    lista[i].numero=numero;
                    break;
                }
            }

            SIGNAL(sem_ds,MUTEX);
            SIGNAL(sem_ds,FULL);
        }
        //arrivati qui vuol dire che file è finito
        //segnaliamo agli altri 2 processi che non si devono aspettare altri numeri

        WAIT(sem_ds,EMPTY);
        WAIT(sem_ds,MUTEX);

        for (int i = 0; i < DIM; i++)
        {
            if (lista[i].tipo==VUOTO)
            {
                lista[i].tipo=T_EOF;
                break;
            }
        }
        
        SIGNAL(sem_ds,MUTEX);

        SIGNAL(sem_ds,FULL);
        SIGNAL(sem_ds,FULL_RES);

        wait(NULL);
        wait(NULL);

        shmctl(memoria, IPC_RMID, NULL);
        semctl(sem_ds, 0, IPC_RMID, 0);
        
    }
    exit(0);
}
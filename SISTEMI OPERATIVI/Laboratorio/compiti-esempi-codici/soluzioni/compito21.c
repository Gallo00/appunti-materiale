#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

#define SEM_MUTEX 0 //valore: 1 , il primo figlio può entrare
#define SEM_PADRE 1 //valore: 0 , il padre dovrà attendere che l'ultimo figlio gli dia il permesso

#define ALPH_SIZE 26
#define BUFSIZE 1024

int WAIT(int sem_des, int num_semaforo){
    struct sembuf operazioni[1] = {{num_semaforo,-1,0}};
    return semop(sem_des, operazioni, 1);
}

int SIGNAL(int sem_des, int num_semaforo){
    struct sembuf operazioni[1] = {{num_semaforo,+1,0}};
    return semop(sem_des, operazioni, 1);
}


typedef struct
{
    int figli_finiti;
    char occur[ALPH_SIZE];
}memoria;


void reader(int sem_ds,memoria* segmento,char* nomeFile,int id,int numFigli)
{
    struct stat statbuf;
    stat(nomeFile,&statbuf);
    int fd=open(nomeFile,O_RDONLY);
    char* map;
    map=(char*)mmap(NULL,statbuf.st_size,PROT_READ,MAP_SHARED,fd,0);
    
    for (int i = 0; i < statbuf.st_size; i++)
    {
        char carattere_letto=map[i];
        int posizione=-1;
        if(carattere_letto>='a' && carattere_letto<='z')
        {
            posizione=carattere_letto - 'a';
        }
        else if (carattere_letto>='A' && carattere_letto<='Z')
        {
            posizione=carattere_letto - 'A';
        }
        if (posizione!=-1)
        {
            //potrei scrivere 
            WAIT(sem_ds,SEM_MUTEX);

            segmento->occur[posizione]++;

            SIGNAL(sem_ds,SEM_MUTEX);
            srand(time(NULL)+id);
            //usleep(rand()%1000001);

        }
    }
    WAIT(sem_ds,SEM_MUTEX);

    segmento->figli_finiti++;
    if (segmento->figli_finiti==numFigli)
    {
        SIGNAL(sem_ds,SEM_PADRE);
    }
    else
    {
        SIGNAL(sem_ds,SEM_MUTEX);
    }
    printf("READER%d: finisce\n",id);
    exit(0);
}

int main(int argc,char* argv[])
{
    if (argc<2)
    {
        perror("metti files");
        exit(1);
    }
    int num_figli=argc-1;

    //creare memoria condivisa
    int mem_ds;
    if ((mem_ds=shmget(IPC_PRIVATE,sizeof(memoria),IPC_CREAT | 0660))==-1)
    {
        perror("shmget");
        exit(1);
    }
    memoria* segmento;
    if ((segmento=(memoria*)shmat(mem_ds,NULL,0))==(memoria*)-1)
    {
        perror("shmat");
        exit(1);
    }
    int sem_ds;
    if ((sem_ds=semget(IPC_PRIVATE,2,IPC_CREAT | 0660))==-1)
    {
        perror("semget");
        exit(1);
    }

    if (semctl(sem_ds,SEM_MUTEX,SETVAL,1)==-1)
    {
        perror("semctl");
        exit(1);
    }

    if (semctl(sem_ds,SEM_PADRE,SETVAL,0)==-1)
    {
        perror("semctl");
        exit(1);
    }
    
    //il padre setta il segmento
    segmento->figli_finiti=0;
    for (int i = 0; i < ALPH_SIZE; i++)
    {
        segmento->occur[i]=0;
    }
    
    //generiamo i figli,a ognuno va dato un file
    for (int i = 1; i <= num_figli; i++)
    {
        if (fork()==0)
        {
            reader(sem_ds,segmento,argv[i],i,num_figli);
        }
    }
    int caratteri_totali=0;
    float percentuali[26];
    WAIT(sem_ds,SEM_PADRE);
    
    for (int i = 0; i < ALPH_SIZE; i++)
    {
        caratteri_totali = caratteri_totali + segmento->occur[i];
    }

    for (int i = 0; i < ALPH_SIZE; i++)
    {
        percentuali[i] = ((float)segmento->occur[i]/(float)caratteri_totali)*100.0;
    }
    
    for (int i = 0; i < ALPH_SIZE; i++)
    {
        printf("%c: %.*f\n",i+'a',3,percentuali[i]);
    }
    shmdt(segmento);
    semctl(sem_ds,SEM_PADRE,IPC_RMID,0);
}
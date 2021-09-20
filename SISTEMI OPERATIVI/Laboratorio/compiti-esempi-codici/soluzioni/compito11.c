#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <time.h>
#include <dirent.h>
#include <libgen.h>
#include <ctype.h>

#define BUFSIZE 1024
#define MAX_LEN 1024

#define NON_FINITO 1
#define FINITO 2

#define SEM_PADRE 0
#define SEM_FILTER 1

#define TOUPPER 1
#define TOLOWER 2
#define SUBS 3

typedef struct 
{
    int fine;
    char riga[MAX_LEN];
}record;

int WAIT(int sem_des, int num_semaforo){
    struct sembuf operazioni[1] = {{num_semaforo,-1,0}};
    return semop(sem_des, operazioni, 1);
}

int SIGNAL(int sem_des, int num_semaforo){
    struct sembuf operazioni[1] = {{num_semaforo,+1,0}};
    return semop(sem_des, operazioni, 1);
}

void togli_primoChar(char * str)
{
    int len=strlen(str);
    for (int i = 0; i < len-1; i++)
    {
        str[i]=str[i+1];
    }
    str[len-1]='\0';
}

int filter(int sem_ds,record* shmem,char* filtro,int id,int num_filter)
{
    printf("FILTER%d:\n",id+1);
    char* token;
    int azione;

    char* parola1;
    strcpy(parola1,filtro);
    togli_primoChar(parola1);

    char* parola2=NULL;
    if (filtro[0]=='^')
    {
        
        azione=TOUPPER;
    }
    else if (filtro[0]=='_')
    {
        azione=TOLOWER;
    }
    else
    {
        azione=SUBS;
        char buffer[BUFSIZE];
        strcpy(buffer,filtro);
        parola1=strtok(buffer,","); //qui prendiamo %parola1
        togli_primoChar(parola1);
        parola2=strtok(NULL,","); //qui prendiamo parola2
    }

    printf("FILTER%d: prima del while1\n",id+1);
    while (1)
    {
        printf("FILTER%d: appena prima la zona critica\n",id+1);
        WAIT(sem_ds,SEM_FILTER);
        printf("FILTER%d: dentro la zona critica\n",id+1);
        sleep(2);
        //aggiungere controllo per vedere se abbiamo finito
        if (shmem->fine==FINITO)
        {
            if (id==num_filter-1)
            {
                SIGNAL(sem_ds,SEM_PADRE);
            }
            else
            {
                SIGNAL(sem_ds,SEM_FILTER);
            }
            break;
        }
        
        char* point=strstr(shmem->riga,parola1);
        while (point)
        {
            if (azione==TOUPPER)
            {
                for (int i = 0; i < strlen(parola1); i++)
                {
                    point[i]=toupper(point[i]);
                }
            }
            else if (azione==TOLOWER)
            {
                for (int i = 0; i < strlen(parola1); i++)
                {
                    point[i]=tolower(point[i]);
                }
            }
            else
            {
                strcpy(point,parola2);
            }
            point=strstr(point+1,parola1); //prendiamo prox occorrenza
        }
        //se il filter è l'ultimo, da il permesso al padre di entrare,
        //altrimenti lo da al prox filter
        if (id==num_filter-1)
        {
            SIGNAL(sem_ds,SEM_PADRE);
        }
        else
        {
            SIGNAL(sem_ds,SEM_FILTER);
        }
    }
    printf("FILTER%d finisce\n",id+1);
    exit(0);
}

int main(int argc,char* argv[])
{
    int num_filtri=0;
    char* filtri[BUFSIZE]={"\0"};
    char buffer[BUFSIZE];
    struct stat statbuf;
    int mem_ds;
    int sem_ds;
    record* shmem;
    FILE* input;
    if (argc<3)
    {
        perror("errore nei params");
        exit(1);
    }
    
    if (stat(argv[1],&statbuf)==-1 || !S_ISREG(statbuf.st_mode))
    {
        perror("stat");
        exit(1);
    }
    if ((input=fopen(argv[1],"r"))==NULL)
    {
        perror("fopen");
        exit(1);
    }
    
    
    for (int i = 2; i < argc; i++)
    {
        //controllare se sono inserite stringhe correttamente
      //  printf("%s---",argv[i]);
        if (strlen(argv[i])>=2 && argv[i][0]=='^')
        {
            filtri[num_filtri]=argv[i];
            num_filtri++;
        }
        else if (strlen(argv[i])>=2 && argv[i][0]=='_')
        {
            filtri[num_filtri]=argv[i];
            num_filtri++;
        }
        else if (strlen(argv[i])>=3 && argv[i][0]=='%') //minimo sarebbe %x,
        {
            // %parola1,parola2
            //controllare parola1 sia lunga almeno un carattere
            char buff[BUFSIZE];
            strcpy(buff,argv[i]);
            char* token=strtok(buff,",");
            if (strcmp(token,"%")!=0)
            {
                filtri[num_filtri]=argv[i];
                num_filtri++;
            } 
        }
       // printf("%s \n",filtri[num_filtri-1]);
    }
    if (num_filtri==0)
    {
        perror("nessun filtro inserito correttamente");
        exit(1);
    }
    
    if ((mem_ds=shmget(IPC_PRIVATE,sizeof(record),IPC_CREAT | 0660))==-1)
    {
        perror("shmget");
        exit(1);
    }
    if ((shmem=(record*)shmat(mem_ds,NULL,0))==(record*)-1)
    {
        perror("shmat");
        exit(1);
    }
    //memoria condivisa creata e attaccata
    
    //idea: 1 semaforo per bloccare il padre,1 semaforo per creare una coda di processi bloccati
    //(da mettere nel giusto ordine)

    if ((sem_ds=semget(IPC_PRIVATE,2,IPC_CREAT | 0660))==-1)
    {
        perror("semget");
        exit(1);
    }
    if (semctl(sem_ds, SEM_PADRE ,SETVAL,1)==-1)
    {
        perror("semctl");
        exit(1);
    }
    if (semctl(sem_ds, SEM_FILTER ,SETVAL,0)==-1)
    {
        perror("semctl");
        exit(1);
    }


    for (int i = 0; i < num_filtri; i++)
    {
        //creare i processi
        if (fork()==0)
        {
           //printf("sono filter%d, sto chiamando la fun\n",i+1);
            filter(sem_ds,shmem,filtri[i],i,num_filtri);
        }
        sleep(3); //padre aspetta un pochino prima di avviare il figlio successivo,così creiamo
        //la coda nel modo giusto
    }

    //leggiamo il file
    sleep(num_filtri*3);
    while (fgets(buffer,MAX_LEN,input)!=NULL)
    {
        WAIT(sem_ds,SEM_PADRE);
        shmem->fine=NON_FINITO;
        strcpy(shmem->riga,buffer);
        if(strcmp(buffer,"\0")!=0 )printf("PADRE: metto %s",buffer);
        SIGNAL(sem_ds,SEM_FILTER); //in teoria il primo filter in coda prende questa signal e si avvia

        WAIT(sem_ds,SEM_PADRE);
        printf("\n%s\n\n",shmem->riga); //estrapolazione dati 
        SIGNAL(sem_ds,SEM_FILTER);
    }
    //segnaliamo al primo filter che abbiamo finito, lui penserà a segnalarlo al secondo che
    //segnalerà al terzo e così via
    WAIT(sem_ds,SEM_PADRE);
    shmem->fine=FINITO;
    SIGNAL(sem_ds,SEM_FILTER);

    for (int i = 0; i < num_filtri; i++)
    {
        wait(NULL);
    }
    
}

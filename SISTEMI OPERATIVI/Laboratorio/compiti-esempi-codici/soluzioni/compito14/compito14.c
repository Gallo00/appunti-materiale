//COMPITO 23 04 2019


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/shm.h>


#define MAX_LEN_NOME 1024

#define SEM_MUTEX 0

#define SEM_FILE_PIENO 1
#define SEM_FILE_VUOTO 2

#define SEM_DIR_PIENO 3
#define SEM_DIR_VUOTO 4

typedef struct 
{
    long dim;
    char nome[MAX_LEN_NOME];
    int reader_finiti;
}record;

int WAIT(int sem_des, int num_semaforo){
    struct sembuf operazioni[1] = {{num_semaforo,-1,0}};
    return semop(sem_des, operazioni, 1);
}

int SIGNAL(int sem_des, int num_semaforo){
    struct sembuf operazioni[1] = {{num_semaforo,+1,0}};
    return semop(sem_des, operazioni, 1);
}

void reader(int sem_ds,record* memoria,char* dirName,int id)
{
    DIR* directory=opendir(dirName);
    chdir(dirName);
    struct dirent* entry;
    struct stat statbuf;
    while ((entry=readdir(directory))!=NULL)
    {
        //voce della cartella, capire se è file regolare o cartella(o altro)
        if (stat(entry->d_name,&statbuf)!=-1)
        {
            if (S_ISREG(statbuf.st_mode))
            {
                //file regolare, entriamo nella memoria e scriviamo le sue informazioni
                WAIT(sem_ds,SEM_MUTEX);

                WAIT(sem_ds,SEM_FILE_VUOTO);
                WAIT(sem_ds,SEM_DIR_VUOTO);

                memoria->dim=statbuf.st_size;
                strcpy(memoria->nome,entry->d_name);

                SIGNAL(sem_ds,SEM_DIR_VUOTO);
                SIGNAL(sem_ds,SEM_FILE_PIENO);

                SIGNAL(sem_ds,SEM_MUTEX);
            }
            else if (S_ISDIR(statbuf.st_mode) && strcmp(entry->d_name,".")!=0 && strcmp(entry->d_name,"..")!=0)
            {
                //cartella, scriviamo nella memoria il suo nome
                WAIT(sem_ds,SEM_MUTEX);

                WAIT(sem_ds,SEM_DIR_VUOTO);
                WAIT(sem_ds,SEM_FILE_VUOTO);
            
                memoria->dim=-1; //simboleggia la cartella
                strcpy(memoria->nome,entry->d_name);

                SIGNAL(sem_ds,SEM_FILE_VUOTO);
                SIGNAL(sem_ds,SEM_DIR_PIENO);

                SIGNAL(sem_ds,SEM_MUTEX);
            }
        }
    }
    //alla fine il reader deve segnalare che ha finito
    WAIT(sem_ds,SEM_MUTEX);
    memoria->reader_finiti++;
    SIGNAL(sem_ds,SEM_MUTEX);
    
    SIGNAL(sem_ds,SEM_FILE_PIENO);
    SIGNAL(sem_ds,SEM_DIR_PIENO);
    printf("PROCESSO READER %d FINISCE\n",id);
    exit(0);
}

void fileConsumer(int sem_ds,record* memoria,int numCartelle)
{
    while (1)
    {
        WAIT(sem_ds , SEM_FILE_PIENO);
        if (memoria->reader_finiti==numCartelle)
        {
            break;
        }
        printf("%s file di %ld byte \n", memoria->nome , memoria->dim);
        SIGNAL(sem_ds , SEM_FILE_VUOTO);
    }
    printf("FILE CONSUMER FINISCE \n");
    exit(0);
}

void dirConsumer(int sem_ds,record* memoria,int numCartelle)
{
    while (1)
    {
        WAIT(sem_ds , SEM_DIR_PIENO);
        if (memoria->reader_finiti==numCartelle)
        {
            break;
        }
        printf("%s directory\n", memoria->nome);
        SIGNAL(sem_ds ,SEM_DIR_VUOTO);
    }
    printf("DIR CONSUMER FINISCE \n");
    exit(0);
}

int main(int argc,char* argv[])
{
    if (argc<2)
    {
        perror("errore parametri");
        exit(1);
    }
    struct stat statbuf;
    int numCartelle=0;
    for (int i = 1; i < argc; i++)
    {
        if (stat(argv[i],&statbuf)!=-1 && S_ISDIR(statbuf.st_mode))
        {
            numCartelle++;
        }
    }
    if (numCartelle==0)
    {
        perror("errore nei param");
        exit(1);
    }
    //creare memoria condivisa e attaccarla
    int mem_ds;
    record* memoria;
    if ((mem_ds=shmget(IPC_PRIVATE,sizeof(record),IPC_CREAT | 0660))==-1)
    {
        perror("shmget");
        exit(1);
    }

    if ((memoria=(record*)shmat(mem_ds,NULL,0))==(record*)-1)
    {
        perror("shmat");
        exit(1);
    }
    memoria->reader_finiti=0;

    //creare semafori, facciamo 1 mutex e 2 contatori: uno che conta i file in memoria(così evitiamo che FILE-CONSUMER entri ) e 
    //stesso discorso per dir-consumer
    int sem_ds;
    if ((sem_ds=semget(IPC_PRIVATE,5,IPC_CREAT | 0660))==-1)
    {
        perror("semget");
        exit(1);
    }

    if (semctl(sem_ds,SEM_MUTEX,SETVAL,1)==-1)
    {
        perror("semctl 1");
        exit(1);
    }
    
    if (semctl(sem_ds,SEM_FILE_PIENO,SETVAL,0)==-1)
    {
        perror("semctl 2");
        exit(1);
    }
    if (semctl(sem_ds,SEM_FILE_VUOTO,SETVAL,1)==-1)
    {
        perror("semctl 3");
        exit(1);
    }

    if (semctl(sem_ds,SEM_DIR_PIENO,SETVAL,0)==-1)
    {
        perror("semctl 4");
        exit(1);
    }

    if (semctl(sem_ds,SEM_DIR_VUOTO,SETVAL,1)==-1)
    {
        perror("semctl 5");
        exit(1);
    }

    //creare i figli reader
    for (int i = 1; i < argc; i++)
    {
        if (stat(argv[i],&statbuf)!=-1 && S_ISDIR(statbuf.st_mode))
        {
            if (fork()==0)
            {
                //processo figlio reader
                reader(sem_ds,memoria,argv[i],i);
            }
        } 
    }
    //creare i figli consumer
    if (fork()==0)
    {
        fileConsumer(sem_ds,memoria,numCartelle);
    }
    if (fork()==0)
    {
        dirConsumer(sem_ds,memoria,numCartelle);
    }

    for (int i = 0; i < numCartelle; i++)
    {
        wait(NULL);
    }
    wait(NULL);
    wait(NULL);
}
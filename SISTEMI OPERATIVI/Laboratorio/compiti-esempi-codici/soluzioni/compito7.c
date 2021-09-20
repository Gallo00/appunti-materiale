
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>

#define MUTEX_CHAR 0
#define MUTEX_AL 1
#define MUTEX_MZ 2

#define ALPHABET_SIZE 26

int WAIT(int sem_des, int num_semaforo){
    struct sembuf operazioni[1] = {{num_semaforo,-1,0}};
    return semop(sem_des, operazioni, 1);
}

int SIGNAL(int sem_des, int num_semaforo){
    struct sembuf operazioni[1] = {{num_semaforo,+1,0}};
    return semop(sem_des, operazioni, 1);
}

//finito serve per segnalare ai due figli che appunto è finito il file


void figlioAL(long* mem_occur,char* mem_char,int sem_ds)
{
    while (1)
    {
        WAIT(sem_ds,MUTEX_AL);
        mem_occur[(*mem_char) -'a']++;
        SIGNAL(sem_ds,MUTEX_CHAR);
    }
}

void figlioMZ(long* mem_occur,char* mem_char,int sem_ds)
{
    while (1)
    {
        WAIT(sem_ds,MUTEX_MZ);
        mem_occur[(*mem_char) -'a']++;
        SIGNAL(sem_ds,MUTEX_CHAR);
    }
}

int main(int argc,char* argv[])
{
    struct stat statbuf;
    int sem_ds;

    int mem_ds_occur;
    long* mem_occur;

    int mem_ds_char;
    char* mem_char;

    if (argc!=2)
    {
        perror("errore coi params");
        exit(1);
    }
    if (lstat(argv[1],&statbuf)==-1 || !S_ISREG(statbuf.st_mode))
    {
        perror(argv[1]);
        exit(1);
    }
    //creiamo i 2 segmenti di memoria condivisa e li attacchiamo

    if ((mem_ds_occur=shmget(IPC_PRIVATE, sizeof(long)*ALPHABET_SIZE,IPC_CREAT | 0660))==-1)
    {
        perror("shmget");
        exit(1);
    }
    if ((mem_ds_char=shmget(IPC_PRIVATE, sizeof(char),IPC_CREAT | 0660))==-1)
    {
        perror("shmget");
        exit(1);
    }

    if ((mem_occur=(long*)shmat(mem_ds_occur,NULL,0))==(long*)-1)
    {
        perror("shmat");
        exit(1);
    }
    if ((mem_char=(char*)shmat(mem_ds_char,NULL,0))==(char*)-1)
    {
        perror("shmat");
        exit(1);
    }
    //creare i semafori di controllo della memoria condivisa
    //serve un mutex per la mem_char e un mutex per la mem_occur

    if ((sem_ds=semget(IPC_PRIVATE,3,IPC_CREAT | 0660))==-1)
    {
        perror("semget");
        exit(1);
    }

    if (semctl(sem_ds,MUTEX_CHAR,SETVAL,1)==-1)
    {
        perror("semctl");
    }

    if (semctl(sem_ds,MUTEX_AL,SETVAL,0)==-1)
    {
        perror("semctl");
    }
    if (semctl(sem_ds,MUTEX_MZ,SETVAL,0)==-1)
    {
        perror("semctl");
    }

    //settiamo il char a bloccato e tutte le occur a 0
    for (int i = 0; i <ALPHABET_SIZE; i++)
    {
        mem_occur[i]=0;
    }
    //non ci dovrebbero essere problemi di corse critiche dato che i figli ancora non esistono
    int pidAL;
    int pidMZ;
    if ((pidAL=fork())==0)
    {
        figlioAL(mem_occur,mem_char,sem_ds);
    }
    if ((pidMZ=fork())==0)
    {
        figlioMZ(mem_occur,mem_char,sem_ds);
    }
    //padre deve leggere dal file(con mappatura)
    int file_ds;
    if ((file_ds=open(argv[1],O_RDONLY))==-1)
    {
        perror("open");
        exit(1);
    }
    char* map;
    if ((map=(char*)mmap(NULL,statbuf.st_size,PROT_READ,MAP_SHARED,file_ds,0))==MAP_FAILED)
    {
        perror("mmap");
        exit(1);
    }

    for (int i = 0; i <statbuf.st_size; i++)
    {
        WAIT(sem_ds,MUTEX_CHAR);
        if ((map[i]>='a' && map[i]<='l')||(map[i]>='A' && map[i]<='L'))
        {
            if ((map[i]>='A' && map[i]<='L'))
            {
                (*mem_char)=map[i] + 32;
            }
            else
            {
                (*mem_char)=map[i];
            }
            SIGNAL(sem_ds,MUTEX_AL);
        }
        else if ((map[i]>='m' && map[i]<='z')||(map[i]>='M' && map[i]<='Z'))
        {
            if ((map[i]>='M' && map[i]<='Z'))
            {
                (*mem_char)=map[i] + 32;
            }
            else
            {
                (*mem_char)=map[i];
            }
            SIGNAL(sem_ds,MUTEX_MZ);
        }
        else
        {
            SIGNAL(sem_ds,MUTEX_CHAR);
        }
    }

    //lettura mem_occur
    WAIT(sem_ds,MUTEX_CHAR);
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        printf("%c:%ld\n",'a'+ i,mem_occur[i]);
    }
    SIGNAL(sem_ds,MUTEX_CHAR);

    //distruggere le strutture ipc
    munmap(map, statbuf.st_size);
    shmdt(mem_occur);
    shmdt(mem_char);

    semctl(sem_ds,MUTEX_CHAR,IPC_RMID,0); //DISTRUGGe array semafori

    kill(pidAL,SIGKILL);
    kill(pidMZ,SIGKILL);
    
}
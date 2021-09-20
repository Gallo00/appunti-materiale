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

#define BUFSIZE 1024
#define MAX_PATH_LEN 2048

#define SEM_SCANNER 0
#define SEM_STATER 1

#define MESSAGGIO 1
#define FINE 2
typedef struct {
    long tipo;
    long idscanner;
    long dim;
}msg;

#define NON_FINITO 1
#define FINITO 2
typedef struct{
    long idscanner;
    char path[MAX_PATH_LEN];
    int fine;
}record;

int WAIT(int sem_des, int num_semaforo){
    struct sembuf operazioni[1] = {{num_semaforo,-1,0}};
    return semop(sem_des, operazioni, 1);
}

int SIGNAL(int sem_des, int num_semaforo){
    struct sembuf operazioni[1] = {{num_semaforo,+1,0}};
    return semop(sem_des, operazioni, 1);
}

void stater(int codamsg,record* shmem,int sem_ds,int num_cartelle)
{
    int contatore_finiti=0; //conta quanti scanner sono finiti
    char buffer[MAX_PATH_LEN];
    struct stat statbuf;
    int fine_while=0;
    while (1)
    {
        WAIT(sem_ds,SEM_STATER); //aspetta il permesso da uno scanner per entrare
        if (shmem->fine==FINITO)
        {
            contatore_finiti++;
            printf("sono finiti %d scanner\n",contatore_finiti);
            if (contatore_finiti==num_cartelle)
            {
                fine_while=1;
            }
        }
        else
        {
            //gli arriva il pathname di un file, lo apriamo (vediamo le sue stats e mandiamo il num di blocchi)
            strncpy(buffer,shmem->path,MAX_PATH_LEN);
            printf("stater vede:%s\n",buffer);
            if (stat(buffer,&statbuf)==-1)
            {
                perror("stat");
                exit(1);
            }
            //adesso possiamo inviare num di blocchi
            msg messaggio;
            messaggio.dim=statbuf.st_blocks;
            messaggio.tipo=MESSAGGIO;
            messaggio.idscanner=shmem->idscanner;
            printf("stater invia a padre:%ld\n",messaggio.dim);
            msgsnd(codamsg,&messaggio,sizeof(msg)-sizeof(long),0);    
        }
        //segnaliamo agli scanner che ora si può accedere alla memoria
        SIGNAL(sem_ds,SEM_SCANNER); //diamo il permesso agli scanner di entrare
        if (fine_while)
        {
            break;
        }
    }
    //segnaliamo al padre che sono finiti gli scanner(dunque i messaggi da inviargli)
    msg messaggio;
    messaggio.tipo=FINE;
    msgsnd(codamsg,&messaggio,sizeof(msg)-sizeof(long),0); 
    printf("stater finisce\n");
    exit(0);
}

void scanner(record* shmem,int sem_ds,char* pathDIR,int id,int chiamata)
{
    printf("scanner%d sono in %s\n",id+1,pathDIR);
    DIR* directory;
    if ((directory=opendir(pathDIR))==NULL)
    {
        perror("non ho aperto la cartella");
        exit(1);
    }
    
    struct dirent* entry;
    struct stat statbuf;
    while ((entry=readdir(directory))!=NULL)
    {
        //controllare se è file o directory
        printf("scanner%d voce attuale della cartella:%s\n",id+1,entry->d_name);

        char buffer[MAX_PATH_LEN];
        strncpy(buffer,pathDIR,MAX_PATH_LEN);
        strcat(buffer,"/");
        strcat(buffer,entry->d_name);

        if ((stat(buffer,&statbuf)==-1))
        {
            perror("stat in scanner");
            exit(1);
        }
        if (S_ISREG(statbuf.st_mode))
        {
            printf("file regolare:%s\n",entry->d_name);

            //concatenazione
            char pathfile[MAX_PATH_LEN]={'\0'};
            strncpy(pathfile,pathDIR,MAX_PATH_LEN);
            strcat(pathfile,"/");
            strcat(pathfile,entry->d_name);


            printf("scanner%d manda:%s\n",id+1,pathfile);

            WAIT(sem_ds,SEM_SCANNER);
            shmem->idscanner=id;
            shmem->fine=NON_FINITO;
            strncpy(shmem->path,pathfile,MAX_PATH_LEN);
            SIGNAL(sem_ds,SEM_STATER);
        }
        else if (S_ISDIR(statbuf.st_mode))
        {
            //controlliamo di non essere in una cartella virtuale(. e ..)
            if ((strcmp(basename(entry->d_name),".")==0) || strcmp(basename(entry->d_name),"..")==0 )
            {
                continue;
            }
            //dobbiamo concatenare ( pathDIR , "/" , entry->d_name )
            char new_pathDIR[MAX_PATH_LEN]={'\0'};
            strncpy(new_pathDIR,pathDIR,MAX_PATH_LEN);
            strcat(new_pathDIR,"/");

            strcat(new_pathDIR,entry->d_name);
            //strcat(new_pathDIR,"\0");
            printf("newPathdir è:%s\n",new_pathDIR);
            scanner(shmem,sem_ds,new_pathDIR,id,chiamata+1); //chiamata ricorsiva nella prox cartella
        }
    }
    //printf("ho saltato il while\n");
    closedir(directory);
    //fine del ciclo, dobbiamo capire in qualche modo se era la prima chiamata
    //se è la prima dobbiamo segnalare a stater che questo scanner ha finito e deve
    //terminare il processo
    printf("scanner%d chiamata%d\n",id+1,chiamata);
    if (chiamata==1)
    {
        //prima chiamata, termina tutto
        WAIT(sem_ds,SEM_SCANNER);
        shmem->idscanner=id;
        shmem->fine=FINITO;
        SIGNAL(sem_ds,SEM_STATER);
        printf("scanner%d finisce\n",id+1);
        exit(1);
    }
}

int main(int argc,char* argv[])
{
    if (argc<2)
    {
        perror("indicare almeno un percorso");
        exit(1);
    }
    int num_cartelle=0;
    struct stat statbuf;
    char* percorsi_indicati[BUFSIZE];
    msg messaggio;
    int codamsg;
    int mem_ds;
    record* shmem;
    int sem_ds;

    for (int i = 1; i < argc; i++)
    {
        if ((stat(argv[i],&statbuf)!=-1) && (S_ISDIR(statbuf.st_mode)))
        {
            //è una cartella
            percorsi_indicati[num_cartelle]=argv[i];
            num_cartelle++;
        }
    }
    printf("NUM CARTELLE:%d\n",num_cartelle);
    if (num_cartelle==0)
    {
        perror("nessuno dei campi è valido");
        exit(1);
    }
    //creare coda messaggi: comunicazione PADRE <--> STATER
    if ((codamsg=msgget(IPC_PRIVATE,IPC_CREAT | 0660))==-1)
    {
        perror("msgget");
        exit(1);
    }
    
    //Creare mem condivisa: comunicazione SCANNER --> STATER
    if ((mem_ds=shmget(IPC_PRIVATE,sizeof(record),IPC_CREAT | 0660))==-1)
    {
        perror("shmget");
        exit(1);
    }
    //attacchiamo la memoria
    if ((shmem=(record*)shmat(mem_ds,NULL,0))==(record*)-1)
    {
        perror("shmat");
        exit(1);
    }
    //creiamo semafori
    if ((sem_ds=semget(IPC_PRIVATE,2,IPC_CREAT | 0660))==-1)
    {
        perror("semget");
        exit(1);
    }

    if (semctl(sem_ds,SEM_SCANNER,SETVAL,1)==-1) //0 o 1?
    {
        perror("semctl");
        exit(1);
    }

    if (semctl(sem_ds,SEM_STATER,SETVAL,0)==-1) //0 o 1?
    {
        perror("semctl");
        exit(1);
    }
    
    if (fork()==0)
    {
        //processo stater
        stater(codamsg,shmem,sem_ds,num_cartelle);
    }

    for (int i = 0; i < num_cartelle; i++)
    {
        if (fork()==0)
        {
            //processo scanner
            scanner(shmem,sem_ds,percorsi_indicati[i],i,1);
        }
    }
    
    //processo padre non fa altro che parlare con stater, stater gli manda messaggi
    //ogni messaggio contiene la dim e l'id dello scanner
    long dim_totali[num_cartelle];
    for (int i = 0; i < num_cartelle; i++)
    {
        dim_totali[i]=0;
    }
    
    while (1)
    {
        if (msgrcv(codamsg,&messaggio,sizeof(msg),0,0)==-1)
        {
            perror("msgrcv");
            exit(1);
        }
        if (messaggio.tipo==FINE)
        {
            break;
        }
        dim_totali[messaggio.idscanner]+=messaggio.dim;
    }
    wait(NULL);
    for (int i = 0; i < num_cartelle; i++)
    {
        wait(NULL);
    }
    
    printf("\n\n");
    for (int i = 0; i < num_cartelle; i++)
    {
        printf("%ld %s\n",dim_totali[i],percorsi_indicati[i]);
    }
    if (shmdt(shmem)==-1)
    {
        perror("shmdt");
        exit(1);
    }
    if (msgctl(codamsg,IPC_RMID,NULL)==-1)
    {
        perror("msgctl");
        exit(1);
    }
    
}
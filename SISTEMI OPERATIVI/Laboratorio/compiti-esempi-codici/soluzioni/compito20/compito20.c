#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>

#include <dirent.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>

#define LINE_SIZE 2048
#define WORD_SIZE 64

#define SEM_IN 0     //VALORE: 1
#define SEM_DBrcv 1  //VALORE: 0
#define SEM_DBsnd 2  //VALORE: 1
#define SEM_OUT 3    //VALORE: 0

int WAIT(int sem_des, int num_semaforo){
    struct sembuf operazioni[1] = {{num_semaforo,-1,0}};
    return semop(sem_des, operazioni, 1);
}

int SIGNAL(int sem_des, int num_semaforo){
    struct sembuf operazioni[1] = {{num_semaforo,+1,0}};
    return semop(sem_des, operazioni, 1);
}

#define FINITO 1
#define NON_FINITO 2
typedef struct
{
    int id;
    char query[LINE_SIZE];
    int fine;
}memoriaINDB;

typedef struct
{
    int id;
    int valore;
    int fine;
}memoriaDBOUT;

void IN1(int sem_ds,memoriaINDB* mem_IN_DB,char* nomeFile)
{
    FILE* file_input=fopen(nomeFile,"r");
    char buffer[LINE_SIZE];
    while (fgets(buffer,LINE_SIZE,file_input))
    {
        //query è in buffer
        //"inviamola" a DB
        //verifichiamo se abbiamo il permesso di entrare
        for (int i = strlen(buffer) - 1; i >= 0; i--)
        {
            if (isspace(buffer[i])!=0)
            {
                buffer[i]=0;
            }
            else
            {
                i=-1;
            }
        }
        printf("%s(len=%ld)\n",buffer,strlen(buffer));


        WAIT(sem_ds,SEM_IN);
        printf("IN1: zona critica\n");
        //inseriamo query
        strcpy(mem_IN_DB->query,buffer);
        mem_IN_DB->id=1;
        mem_IN_DB->fine=NON_FINITO;
        printf("IN1: %s(len=%ld)\n",mem_IN_DB->query,strlen(mem_IN_DB->query));

        //abbiamo inserito una query
        //diamo il permesso a DB di entrare
        SIGNAL(sem_ds,SEM_DBrcv);
        printf("IN1: DB può entrare\n");
    }
    //ciclo finito, segnaliamo a DB
    WAIT(sem_ds,SEM_IN);

    mem_IN_DB->id=1;
    mem_IN_DB->fine=FINITO;

    //diamo il permesso a DB di entrare
    SIGNAL(sem_ds,SEM_DBrcv);
    printf("IN1: FINISCE\n");
    exit(0);
}

void IN2(int sem_ds,memoriaINDB* mem_IN_DB,char* nomeFile)
{
    FILE* file_input=fopen(nomeFile,"r");
    char buffer[LINE_SIZE];
    while (fgets(buffer,LINE_SIZE,file_input))
    {
        //togliamo tutti gli spazi alla fine della stringa
        for (int i = strlen(buffer) - 1; i >= 0; i--)
        {
            if (isspace(buffer[i])!=0)
            {
                buffer[i]=0;
            }
            else
            {
                i=-1;
            }
        }
        printf("%s(len=%ld)\n",buffer,strlen(buffer));
        
        
        //query è in buffer
        //"inviamola" a DB
        //verifichiamo se abbiamo il permesso di entrare
        WAIT(sem_ds,SEM_IN);
        
        printf("IN2: zona critica\n");
        //inseriamo query
        strcpy(mem_IN_DB->query,buffer);
        mem_IN_DB->id=2;
        mem_IN_DB->fine=NON_FINITO;
        printf("IN2: %s(len=%ld)\n",mem_IN_DB->query,strlen(mem_IN_DB->query));

        //abbiamo inserito una query
        //diamo il permesso a DB di entrare
        SIGNAL(sem_ds,SEM_DBrcv);
        printf("IN2: DB può entrare\n");
        strcpy(buffer,"\0");
    }
    //ciclo finito, segnaliamo a DB
    WAIT(sem_ds,SEM_IN);

    mem_IN_DB->id=2;
    mem_IN_DB->fine=FINITO;

    //diamo il permesso a DB di entrare
    SIGNAL(sem_ds,SEM_DBrcv);
    printf("IN2: finisce\n");
    exit(0);
}


void DB(int sem_ds,memoriaINDB* mem_IN_DB,memoriaDBOUT* mem_DB_OUT,char* database)
{
    //mettiamo il database dentro 2 array
    FILE* db_file=fopen(database,"r");
    FILE* stream_righe=fopen(database,"r");
    int records=0;
    char buffer[LINE_SIZE]; //Valore esagerato
    while (fgets(buffer,LINE_SIZE,stream_righe))
    {
        records++;
    }
    //ci sono records righe
    //facciamo 2 array, uno contiene nome e l'altro valore
    char** arrayNomi;
    arrayNomi=malloc(sizeof(char*)*records);
    for (int i = 0; i < records; i++)
    {
        arrayNomi[i]=malloc(sizeof(char)*WORD_SIZE);
    }
    int valori[records];
    int i=0;
    while (i<records)
    {
        fgets(buffer,LINE_SIZE,db_file);
        //estrapoliamo nome e valore
        //nome:valore\n
        char* nome=strtok(buffer,":");
        char* valore=strtok(NULL,"\n");
        //printf("ho messo %s in arrayNomi\n",nome);
        strcpy(arrayNomi[i],nome);
        valori[i]=atoi(valore);
        i++;
    }
    int IN_finiti=0;

    while (1)
    {
        //vediamo se abbiamo il permesso di entrare
        WAIT(sem_ds,SEM_DBrcv);
        printf("DB: zona critica\n");
        //controllo di fine
        if (mem_IN_DB->fine==FINITO)
        {
            IN_finiti++;
            if (IN_finiti==2)
            {
                printf("sono qui\n");
                break;
            }
            else
            {
                printf("sono qui2\n");
                mem_IN_DB->fine=NON_FINITO;
                SIGNAL(sem_ds,SEM_IN);
                continue;
            }
        }

        //cerchiamo la stringa nel nostro array
        printf("CERCARE: %s(len=%ld)\n",mem_IN_DB->query,strlen(mem_IN_DB->query));
        for (int i = 0; i < records; i++)
        {
            //ERRORI NELLA RICERCA NEL DATABASE
            printf("%s(len=%ld)\n",arrayNomi[i],strlen(arrayNomi[i]));
            if (strcmp(mem_IN_DB->query,arrayNomi[i])==0)
            {
                //trovata,prendiamo il valore e lo inviamo a OUT
                //vediamo se abbiamo il permesso di scrivere
                printf("DB: sto per entrare in zona critica OUT\n");
                WAIT(sem_ds,SEM_DBsnd);
                printf("DB: zona critica per OUT\n");
                mem_DB_OUT->fine=NON_FINITO;
                mem_DB_OUT->id=mem_IN_DB->id;
                mem_DB_OUT->valore=valori[i];

                SIGNAL(sem_ds,SEM_OUT); //diamo il permesso a OUT di accedere alla cella
                printf("DB: OUT può entrare \n");
                i=records; //forziamo l'uscita dal for
            }
        }
        printf("DB: un IN può entrare\n");
        SIGNAL(sem_ds,SEM_IN); //cella consumata, diamo il permesso a un IN di entrare
    }
    //fine ciclo
    //segnaliamo a OUT di terminare
    printf("DB: sto per entrare in zona critica OUT(fuori dal while)\n");
    WAIT(sem_ds,SEM_DBsnd);

    mem_DB_OUT->fine=FINITO;

    SIGNAL(sem_ds,SEM_OUT);
    exit(0);
}

void OUT(int sem_ds,memoriaDBOUT* mem_DB_OUT)
{
    int totaleIN1=0;
    int totaleIN2=0;
    while (1)
    {
        //accedere alla memoria 
        WAIT(sem_ds,SEM_OUT);
        printf("OUT: zona critica\n");
        if (mem_DB_OUT->fine==FINITO)
        {
            break;
        }
        
        if (mem_DB_OUT->id==1)
        {
            totaleIN1 = totaleIN1 + mem_DB_OUT->valore;
        }
        else if(mem_DB_OUT->id==2)
        {
            totaleIN2 = totaleIN2 + mem_DB_OUT->valore;
        }
        SIGNAL(sem_ds,SEM_DBsnd);
        printf("OUT: DB può entrare(memoria DB_OUT)\n");
    }
    //fine ciclo, stampiamo i totali e usciamo
    printf("OUT: totaleIN1=%d\n",totaleIN1);
    printf("OUT: totaleIN2=%d\n",totaleIN2);
    exit(0);
}

int main(int argc,char* argv[])
{
    if (argc!=4)
    {
        perror("metti db query1 query2");
        exit(1);
    }
    //vediamo se i file sono utilizzabili
    struct stat statbuf;
    if (stat(argv[1],&statbuf)==-1 || !S_ISREG(statbuf.st_mode))
    {
        perror(argv[1]);
        exit(1);
    }
    if (stat(argv[2],&statbuf)==-1 || !S_ISREG(statbuf.st_mode))
    {
        perror(argv[2]);
        exit(1);
    }
    if (stat(argv[3],&statbuf)==-1 || !S_ISREG(statbuf.st_mode))
    {
        perror(argv[3]);
        exit(1);
    }

    //creare segmenti condivisi
    int IN_DB_ds;
    if ((IN_DB_ds=shmget(IPC_PRIVATE,sizeof(memoriaINDB),IPC_CREAT | 0660))==-1)
    {
        perror("shmget");
        exit(1);
    }
    memoriaINDB* mem_IN_DB;
    if ((mem_IN_DB=(memoriaINDB*)shmat(IN_DB_ds,NULL,0))==(memoriaINDB*)-1)
    {
        perror("shmat");
        exit(1);
    }
    

    int DB_OUT_ds;
    if ((DB_OUT_ds=shmget(IPC_PRIVATE,sizeof(memoriaDBOUT),IPC_CREAT | 0660))==-1)
    {
        perror("shmget");
        exit(1);
    }
    memoriaDBOUT* mem_DB_OUT;
    if ((mem_DB_OUT=(memoriaDBOUT*)shmat(DB_OUT_ds,NULL,0))==(memoriaDBOUT*)-1)
    {
        perror("shmat");
        exit(1);
    }
    
    //creare semafori
    //dovrebbero bastarne 4
    int sem_ds;
    if ((sem_ds=semget(IPC_PRIVATE,4,IPC_CREAT | 0660))==-1)
    {
        perror("semget");
        exit(1);
    }

    if (semctl(sem_ds,SEM_IN,SETVAL,1)==-1) //da il permesso a IN di entrare Memoria_IN_DB
    {
        perror("semctl");
        exit(1);
    }

    if (semctl(sem_ds,SEM_DBrcv,SETVAL,0)==-1) //da il permesso a DB di entrare Memoria_IN_DB
    {
        perror("semctl");
        exit(1);
    }

    if (semctl(sem_ds,SEM_DBsnd,SETVAL,1)==-1) //da il permesso a DB di entrare Memoria_DB_OUT
    {
        perror("semctl");
        exit(1);
    }

    if (semctl(sem_ds,SEM_OUT,SETVAL,0)==-1) //da il permesso a OUT di entrare Memoria_DB_OUT
    {
        perror("semctl");
        exit(1);
    }

    if (fork()==0)
    {
        OUT(sem_ds,mem_DB_OUT);
    }

    if (fork()==0)
    {
        DB(sem_ds,mem_IN_DB,mem_DB_OUT,argv[1]);
    }
    sleep(1);
    if (fork()==0)
    {
        IN1(sem_ds,mem_IN_DB,argv[2]);
    }
    if (fork()==0)
    {
        IN2(sem_ds,mem_IN_DB,argv[3]);
    }
    
    wait(NULL);
    wait(NULL);
    wait(NULL);
    wait(NULL);

    shmdt(mem_IN_DB);
    shmdt(mem_DB_OUT);
    
}

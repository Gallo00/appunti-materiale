
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <time.h>

#define LINE_SIZE 1024
#define WORD_SIZE 64
#define BUFFER_SIZE 1024

#define FINITO 1
#define NON_FINITO 2

#define DEST_DB 1
#define DEST_OUT 2

typedef struct
{
    long tipo;
    char query[LINE_SIZE];
    int id;
    int fine;
}msgINDB;

typedef struct
{
    long tipo;
    int id;
    int valore;
    int fine;
}msgDBOUT;

void IN1(int codaINDB,char* nomeFile)
{
    FILE* file_input=fopen(nomeFile,"r");
    char buffer[LINE_SIZE];
    while (fgets(buffer,LINE_SIZE,file_input))
    {
        //inviare la query a DB
        //togliamo il \n
        int len=strlen(buffer);
        printf("prima %ld ",strlen(buffer));
        if (buffer[len - 1]=='\n')
        {
            buffer[len - 1]=0;
        }
        printf("dopo %ld\n",strlen(buffer));
        msgINDB messaggio;
        messaggio.fine=NON_FINITO;
        messaggio.tipo=DEST_DB;
        messaggio.id=1;
        strcpy(messaggio.query,buffer);
        printf("IN1 manda:%sC\n",messaggio.query);
        msgsnd(codaINDB,&messaggio,sizeof(msgINDB)-sizeof(long),0);
    }
    //fine ciclo, è finito il file
    //inviamo messaggio di segnalazione
    msgINDB messaggio;
    messaggio.fine=FINITO;
    messaggio.tipo=DEST_DB;
    messaggio.id=1;
    msgsnd(codaINDB,&messaggio,sizeof(msgINDB) - sizeof(long),0);
    printf("IN1 finisce\n");
    exit(0);
}

void IN2(int codaINDB,char* nomeFile)
{
    FILE* file_input=fopen(nomeFile,"r");
    char buffer[LINE_SIZE];
    while (fgets(buffer,LINE_SIZE,file_input))
    {
        //inviare la query a DB
        //togliamo il \n
        if (buffer[strlen(buffer) - 1]=='\n')
        {
            buffer[strlen(buffer) - 1]='\0';
        }

        msgINDB messaggio;
        messaggio.fine=NON_FINITO;
        messaggio.tipo=DEST_DB;
        messaggio.id=2;
        strcpy(messaggio.query,buffer);
        printf("IN2 manda:%s\n",messaggio.query);
        msgsnd(codaINDB,&messaggio,sizeof(msgINDB)-sizeof(long),0);
    }
    //fine ciclo, è finito il file
    //inviamo messaggio di segnalazione
    msgINDB messaggio;
    messaggio.fine=FINITO;
    messaggio.tipo=DEST_DB;
    messaggio.id=2;
    msgsnd(codaINDB,&messaggio,sizeof(msgINDB) - sizeof(long),0);
    printf("IN2 finisce\n");
    exit(0);
}

void DB(int codaINDB,int codaDBOUT,char* database)
{
    //leggere intero contenuto del file
    FILE* db_file=fopen(database,"r");
    FILE* stream_righe=fopen(database,"r");
    int records=0;
    char buffer[BUFFER_SIZE]; //Valore esagerato
    while (fgets(buffer,BUFFER_SIZE,stream_righe))
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
        fgets(buffer,BUFFER_SIZE,db_file);
        //estrapoliamo nome e valore
        //nome:valore\n
        char* nome=strtok(buffer,":");
        char* valore=strtok(NULL,"\n");
        printf("ho messo %s in arrayNomi\n",nome);
        strcpy(arrayNomi[i],nome);
        valori[i]=atoi(valore);
        i++;
    }
    
    //Adesso il database è conservato nei 2 array
    int IN_finiti=0;
    while (1)
    {
        //riceviamo messaggio da un IN
        msgINDB messaggioRicevuto;
        msgrcv(codaINDB,&messaggioRicevuto,sizeof(msgINDB)-sizeof(long),DEST_DB,0);
        if (messaggioRicevuto.fine==FINITO)
        {
            IN_finiti++;
            if (IN_finiti==2)
            {
                break;
            }
            else
            {
                continue;
            }
        }
        //vedere se la word ricevuta sta nell'array
        int presente=0;
        printf("DB riceve:(len=%ld) %s\n",strlen(messaggioRicevuto.query),messaggioRicevuto.query);
        printf("-----------CMP------------\n");
        for (int i = 0; i < records; i++)
        {
            printf("da comparare(len=%ld) %s\n",strlen(arrayNomi[i]),arrayNomi[i]);
            if (strncmp(messaggioRicevuto.query,arrayNomi[i],strlen(arrayNomi[i]))==0)
            {
                printf("sono uguali,mando mex a out\n");
                presente=1;
                i=records;
            }
        }
        printf("-----------CMP------------\n");
        if (presente==1)
        {
            //inviare messaggio a OUT
            msgDBOUT messaggioInviato;
            messaggioInviato.fine=NON_FINITO;
            messaggioInviato.id=messaggioRicevuto.id;
            messaggioInviato.tipo=DEST_OUT;
            messaggioInviato.valore=valori[i];
            msgsnd(codaDBOUT,&messaggioInviato,sizeof(msgDBOUT) - sizeof(long),0);
        }
    }
    //alla fine del ciclo inviamo messaggio di segnalazione a OUT
    msgDBOUT messaggioInviato;
    messaggioInviato.fine=FINITO;
    messaggioInviato.tipo=DEST_OUT;
    msgsnd(codaDBOUT,&messaggioInviato,sizeof(msgDBOUT) - sizeof(long),0);
    printf("DB finisce\n");
    exit(0);
}

void OUT(int codaDBOUT)
{
    int totaleIN1=0;
    int totaleIN2=0;
    while (1)
    {
        //riceve messaggio,aggiorna le variabili e poi stampa
        msgDBOUT messaggio;
        msgrcv(codaDBOUT,&messaggio,sizeof(msgDBOUT),DEST_OUT,0);
        if (messaggio.fine==FINITO)
        {
            break;
        }

        if (messaggio.id==1)
        {
            totaleIN1+= messaggio.valore;
        }
        else
        {
            totaleIN2+= messaggio.valore;
        }
    }
    //fine while, stampiamo i totali e usciamo
    printf("totale IN1:%d\n",totaleIN1);
    printf("totale IN2:%d\n",totaleIN2);
    exit(0);
}


int main(int argc,char* argv[])
{
    if (argc!=4)
    {
        perror("metti db file1 file2");
        exit(1);
    }
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

    //CREARE CODE DI MESSAGGI
    int codaINDB;
    if ((codaINDB=msgget(IPC_PRIVATE,IPC_CREAT | 0660))==-1)
    {
        perror("msgget");
        exit(1);
    }
    int codaDBOUT;
    if ((codaDBOUT=msgget(IPC_PRIVATE,IPC_CREAT | 0660))==-1)
    {
        perror("msgget");
        exit(1);
    }

    //creare processi
    if (fork()==0)
    {
        DB(codaINDB,codaDBOUT,argv[1]);
    }
    sleep(1);

    if (fork()==0)
    {
        IN1(codaINDB,argv[2]);
    }

    if (fork()==0)
    {
        IN2(codaINDB,argv[3]);
    }
    
    if (fork()==0)
    {
        OUT(codaDBOUT);
    }
    
    wait(NULL);
    wait(NULL);
    wait(NULL);
    wait(NULL);

    msgctl(codaDBOUT,IPC_RMID,NULL);
    msgctl(codaINDB,IPC_RMID,NULL);
}
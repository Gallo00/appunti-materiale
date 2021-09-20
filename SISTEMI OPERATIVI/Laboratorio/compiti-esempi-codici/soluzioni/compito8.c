#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/wait.h>

#define MSG_SIZE 2048

#define MESSAGGIO 2
#define FINE 1

typedef struct{
    long tipo;
    char riga[MSG_SIZE];
}msg;

void figlioR(int canaleScrittura,char* nomeFile)
{
    FILE* finput=fopen(nomeFile,"r");
    FILE* foutput=fdopen(canaleScrittura,"w");
    char buffer[MSG_SIZE];

    while (fgets(buffer,MSG_SIZE,finput)!=NULL)
    {
        fputs(buffer,foutput);
        sleep(1);
    }
    //fine file
    fputs("stringaExit\n",foutput);
    exit(0);
}

void figlioW(int codamsg)
{
    msg messaggio;
    while (1)
    {
        if(msgrcv(codamsg,&messaggio,sizeof(msg),0,0)==-1)
        {
            perror("msgrcv");
            exit(1);
        }
        if (messaggio.tipo==FINE)
        {
            break;
        }
        else
        {
            printf("OUTPUT: %s",messaggio.riga);
            sleep(1);
        }
    }
    exit(0);
}

int main(int argc,char* argv[])
{
    if (argc!=3)
    {
        perror("errore nei params");
        exit(1);
    }
    //char* parola=argv[1];
    //char* nomeFile=argv[2];
    struct stat statbuf;
    int pipeRP[2];
    int codamsg;
    char buffer[MSG_SIZE]={'\0'};
    msg messaggio;

    if (lstat(argv[2],&statbuf)==-1 || !S_ISREG(statbuf.st_mode))
    {
        perror(argv[2]);
        exit(1);
    }

    if ((codamsg=msgget(IPC_PRIVATE,IPC_CREAT | 0660))==-1)
    {
        perror("msgget");
        exit(1);
    }

    if (pipe(pipeRP)==-1)
    {
        perror("pipe");
        exit(1);
    }

    if (fork()==0)
    {
        //FIGLIO R
        close(pipeRP[0]);
        figlioR(pipeRP[1],argv[2]);
    }
    if (fork()==0)
    {
        //figlio W
        close(pipeRP[0]);
        close(pipeRP[1]);
        figlioW(codamsg);
    }
    //padre apre stream sulla pipe
    close(pipeRP[1]);
    FILE* streamLettura=fdopen(pipeRP[0],"r");
    while (fgets(buffer,MSG_SIZE,streamLettura) && strcmp(buffer,"stringaExit\n")!=0)
    {
        //vedere se nella riga c'è la parola
        //buffer[strlen(buffer)-1]='\0';
        if (strstr(buffer,argv[1])!=NULL)
        {
            //inviare 
            messaggio.tipo=MESSAGGIO;
            strncpy(messaggio.riga,buffer,MSG_SIZE);
            msgsnd(codamsg,&messaggio,sizeof(msg)-sizeof(long),0);
        }
    }
    //fine, manda messaggio di segnalazione a W
    messaggio.tipo=FINE;
    msgsnd(codamsg,&messaggio,sizeof(msg)-sizeof(long),0);


    wait(NULL);
    wait(NULL);

    msgctl(codamsg,IPC_RMID, NULL);
}
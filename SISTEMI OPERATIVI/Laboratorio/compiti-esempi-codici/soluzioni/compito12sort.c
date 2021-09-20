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

#define MAX_WORD_LEN 32

#define SORTER 1
#define COMPARER 2

#define ALGORITMO_FINITO 1
#define ALGORITMO_NON_FINITO 2

typedef struct
{
    long tipo;
    char word1[MAX_WORD_LEN];
    char word2[MAX_WORD_LEN];
    int esito; // word1 < word2 = -1  ,  word1=word2 = 0 , word1 > word2 = 1
    int fineAlg;
}msg;

void bubbleSort(char** parole,int dim,int msg_ds)
{
    msg messaggio;
    for (int i = 0; i < dim-1; i++)
    {
        for (int j = i+1; j < dim; j++)
        {
            //inviamo il messaggio al comparer contenente le stringhe da comparare
            messaggio.tipo=COMPARER;
            messaggio.fineAlg=ALGORITMO_NON_FINITO;
            strcpy(messaggio.word1,parole[i]);
            strcpy(messaggio.word2,parole[j]);
            msgsnd(msg_ds,&messaggio,sizeof(msg)-sizeof(long),0);

            usleep(50);

            //confronto: se parole[i] < parole[j]  li swappiamo
            //il confronto lo affidiamo a comparer, gli inviamo un messaggio
            msgrcv(msg_ds,&messaggio,sizeof(msg),SORTER,0);
            if (messaggio.esito==1)
            {
                //parole[j] è maggiore, swappiamoli
                char tmp[MAX_WORD_LEN];
                strcpy(tmp,parole[i]);
                strcpy(parole[i],parole[j]);
                strcpy(parole[j],tmp);
            }
            
        }
    }
    //alla fine del bubble sort mandiamo un messaggio speciale a comparer per dirgli che può terminare
    messaggio.tipo=COMPARER;
    messaggio.fineAlg=ALGORITMO_FINITO;
    msgsnd(msg_ds,&messaggio,sizeof(msg)-sizeof(long),0);
}

void sorter(int coda_msg,int canaleScrittura,char* nomeFile)
{
    FILE* file;
    FILE* output_pipe;
    FILE* stream_righe;
    if ((file=fopen(nomeFile,"r"))==NULL)
    {
        perror("fopen");
        exit(1);
    }
    if ((stream_righe=fopen(nomeFile,"r"))==NULL)
    {
        perror("fopen");
        exit(1);
    }
    if ((output_pipe=fdopen(canaleScrittura,"w"))==NULL)
    {
        perror("fdopen");
        exit(1);
    }
    //suggerimento: vedere quante righe ci sono , sfruttare stream_righe  
    int N=0;
    char buffer[MAX_WORD_LEN];
    while (fgets(buffer,MAX_WORD_LEN,stream_righe)!=NULL)
    {
        N++;
    }
    //allocare dinamicamente un array(di char*) di N celle
    char** parole=malloc(sizeof(char*)*N);
    for (int i = 0; i < N; i++)
    {
        parole[i]=malloc(sizeof(char)*MAX_WORD_LEN);
    }
    

    //riscansioniamo il file
    for (int i = 0; i < N; i++)
    {
        fgets(parole[i],MAX_WORD_LEN,file);
    }
    //il nostro array di N stringhe è pronto, dobbiamo fare il sort
    bubbleSort(parole,N,coda_msg);
    //appena finisce il bubble sort scriviamo tutte le stringhe sulla pipe
    for (int i = 0; i < N; i++)
    {
        fputs(parole[i],output_pipe);
        usleep(10);
    }
    //segnaliamo al padre che abbiamo finito
    fputs("stringExit\n",output_pipe);
    exit(0); 
}

void comparer(int msg_ds)
{
    msg messaggio;
    while (1)
    {
        //ci limitiamo a ricevere messaggi, confrontare e inviare l'esito
        //se ci arriva un messaggio speciale di uscita facciamo break
        msgrcv(msg_ds,&messaggio,sizeof(msg),COMPARER,0);
        if (messaggio.fineAlg==ALGORITMO_FINITO)
        {
            break;
        }
        else
        {
            int esito=strcasecmp(messaggio.word1,messaggio.word2);
            if (esito < 0)
            {
                //mandiamo -1
                messaggio.esito=-1;
            }
            else if (esito==0)
            {
                //mandiamo 0
                messaggio.esito=0;
            }
            else
            {
                //mandiamo 1
                messaggio.esito=1;
            }
            messaggio.tipo=SORTER;
            msgsnd(msg_ds,&messaggio,sizeof(msg)-sizeof(long),0);
        }
    }
    exit(0);
}

int main(int argc,char* argv[])
{
    if (argc!=2)
    {
        perror("params");
        exit(1);
    }
    //creare coda di messaggi e pipe
    int pipeSP[2];
    int msg_ds;
    msg messaggio;
    FILE* input_pipe;
    char buffer[MAX_WORD_LEN];
    if (pipe(pipeSP)==-1)
    {
        perror("pipe");
        exit(1);
    }
    if ((msg_ds=msgget(IPC_PRIVATE,IPC_CREAT | 0660))==-1)
    {
        perror("msgget");
        exit(1);
    }
    if (fork()==0)
    {
        //sorter sulla pipe dovrà scrivere
        close(pipeSP[0]);
        sorter(msg_ds,pipeSP[1],argv[1]);
    }
    if (fork()==0)
    {
        close(pipeSP[0]);
        close(pipeSP[1]);
        //al figlio comparer non interessa la pipe
        comparer(msg_ds);
    }
    //al padre non serve il canale di scrittura della pipe
    close(pipeSP[1]);
    if ((input_pipe=fdopen(pipeSP[0],"r"))==NULL)
    {
        perror("fdopen");
        exit(1);
    }
    
    while(1)
    {
        //il padre prende stringhe dalla pipe, scritte dal figlio sorter
        //il padre provvede a stamparle, se visualizza una stringa speciale di uscita
        //si rompe il ciclo
        fgets(buffer,MAX_WORD_LEN,input_pipe);
        if (strcmp(buffer,"stringExit\n")==0)
        {
            break;
        }
        else
        {
            //printf("%ld %s",strlen(buffer),buffer);
            printf("%s",buffer);
        }
    }
    wait(NULL);
    wait(NULL);
    close(pipeSP[0]);
    msgctl(msg_ds,IPC_RMID,NULL);
}
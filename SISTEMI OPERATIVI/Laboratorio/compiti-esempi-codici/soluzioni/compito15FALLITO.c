//compito 25 settembre 2020

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <ctype.h>

#define DEST_P 1


#define MAX_WORD_LEN 32

#define FINITO 1
#define NON_FINITO 2    
typedef struct
{
    long tipo;
    int finito;
    char parola[MAX_WORD_LEN];
}msg;

int wordStaInArray(char* word , char** array,int numParole)
{
    //printf("parola= %s",word);
    if (word[strlen(word) - 1]=='\n')
    {
        word[strlen(word) - 1]='\0';
    }
    
    for (int i = 0; i < numParole; i++)
    {
        if (strcasecmp(word,array[i])==0)
        {
            return 1; //c'è
        }
    }
    return 0; //non c'è
}

void pulisci(char* word)
{
    //se il primo char è spazio togliamo
    if (isspace(word[0])!=0)
    {
        printf("sono dentro a pulire %s",word);
        for (int i = 0; i < strlen(word) - 1; i++)
        {
            word[i]=word[i+1];
        }
        word[strlen(word)-1]='\0';
    }
    
    if (isspace(word[strlen(word) - 1])!=0)
    {
        word[strlen(word) - 1]='\0';
    }
}

void R1(int msg_ds,char* nomeFile,int id)
{
    //leggiamo nomeFile
    printf("R1 il mio file e' %s\n",nomeFile);
    FILE* file_input;
    if ((file_input=fopen(nomeFile,"r"))==NULL)
    {
        perror("fopen");
    }
    char buffer[MAX_WORD_LEN];
    //fgets(buffer,MAX_WORD_LEN,file_input);
    //printf("%s",buffer);
    while (fgets(buffer,MAX_WORD_LEN,file_input))
    {
     //   printf("R1 %s",buffer);
        //inviamola
        msg messaggio;
        messaggio.finito=NON_FINITO;
        messaggio.tipo=DEST_P;
        strcpy(messaggio.parola,buffer);
        msgsnd(msg_ds,&messaggio,sizeof(msg)-sizeof(long),0);
    }
    //inviamo un messaggio di tipo finito a p
    msg messaggio;
    messaggio.finito=FINITO;
    messaggio.tipo=DEST_P;
    msgsnd(msg_ds,&messaggio,sizeof(msg)-sizeof(long),0);
    printf("R1 ha finito\n");
    exit(0);
}

void R2(int msg_ds,char* nomeFile,int id)
{
    //leggiamo nomeFile
    printf("R2 il mio file e' %s\n",nomeFile);
    FILE* file_input;
    if ((file_input=fopen(nomeFile,"r"))==NULL)
    {
        perror("fopen");
    }
    char buffer[MAX_WORD_LEN];
    //fgets(buffer,MAX_WORD_LEN,file_input);
    //printf("%s",buffer);
    while (fgets(buffer,MAX_WORD_LEN,file_input))
    {
    //    printf("R2 %s",buffer);
        //inviamola
        msg messaggio;
        messaggio.finito=NON_FINITO;
        messaggio.tipo=DEST_P;
        strcpy(messaggio.parola,buffer);
        msgsnd(msg_ds,&messaggio,sizeof(msg)-sizeof(long),0);
    }
    msg messaggio;
    messaggio.finito=FINITO;
    messaggio.tipo=DEST_P;
    msgsnd(msg_ds,&messaggio,sizeof(msg)-sizeof(long),0);
    printf("R2 ha finito\n");
    exit(0);
}

void W(int canaleLettura)
{
    FILE* pipe_P=fdopen(canaleLettura,"r");
    char buffer[MAX_WORD_LEN];
 //   printf("w inizia\n");
    while (fgets(buffer,MAX_WORD_LEN,pipe_P)!=NULL)
    {
        //se è stringExit\n usciamo, altrimenti visualizziamo
        if (strcmp(buffer,"stringExit\n")==0)
        {
            break;
        }
        else
        {
            printf("W stampa: %s",buffer); //in teoria il \n dovrebbe già essere dentro buffer
        }
    }
  //  printf("w finisce\n");
    close(canaleLettura);
    exit(0);
}

int main(int argc,char* argv[])
{
    if (argc!=3)
    {
        perror("parametri sbagliati");
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
    int msg_ds;
    //creiamo una coda di messaggi(P--R1--R2)
    if ((msg_ds=msgget(IPC_PRIVATE,IPC_CREAT | 0660))==-1)
    {
        perror("msgget");
        exit(1);
    }

    //partoriamo R1 e R2
    if (fork()==0)
    {
        //processo R1
        R1(msg_ds,argv[1],1);
    }

    if (fork()==0)
    {
        R2(msg_ds,argv[2],2);
    }
    
    //creiamo una pipe
    int pipePW[2];
    if (pipe(pipePW)==-1)
    {
        perror("pipe");
        exit(1);
    }
    
    //creiamo il processo W
    if (fork()==0)
    {
        //W vuole solo leggere dalla pipe
        close(pipePW[1]);
        W(pipePW[0]);
    }
    //P vuole solo scrivere sulla pipe
    close(pipePW[0]);
    FILE* pipe_W;
    pipe_W=fdopen(pipePW[1],"w");
    //adesso P si mette in attesa dei messaggi da parte di R1 e R2 
    //nel caso li inoltra a W
    //creiamo un array per tenerci le parole incontrate
    char** paroleIncontrate; //200 parole perchè ogni file è al più 100 righe
    paroleIncontrate=malloc(200*sizeof(char*));
    for (int i = 0; i < 200; i++)
    {
        paroleIncontrate[i]=malloc(sizeof(char)*MAX_WORD_LEN);
        strcpy(paroleIncontrate[i],"\0");
    }
    
    int numParole=0;
    int R_finiti=0;
    sleep(2);
    while (1)
    {
        msg messaggio;
        msgrcv(msg_ds,&messaggio,sizeof(msg),DEST_P,0);
        //controllo di fine
        if (messaggio.finito==FINITO)
        {
            printf("un R ha finito\n");
            R_finiti++;
            if (R_finiti==2)
            {
                printf("padre esce dal while\n");
                break;
            }
            else
            {
                continue;
            }
        }
        printf("P:%s",messaggio.parola);
        sleep(1);
        //controllare se è nelle parole incontrate

        int A=0;
        if (messaggio.parola[strlen(messaggio.parola) - 1]=='\n')
        {
            messaggio.parola[strlen(messaggio.parola) - 1]='\0';
        }

        for (int i = 0; i < numParole; i++)
        {
            if (strcasecmp(messaggio.parola,paroleIncontrate[i])==0)
            {
                A=1;
                break;
            }
        }
        if (A==0)
        {
            printf("%s c'e' \n",messaggio.parola);
        }
        
        if (A==0)
        {
            //la parola non c'è, la inseriamo e la mandiamo a W
            strcpy(paroleIncontrate[numParole],messaggio.parola);
            //la stringa ci arriva senza il \n
            strcat(paroleIncontrate[numParole],"\n");
            //lo mettiamo così il processo W grazie alla fgets la può prendere
            fputs(messaggio.parola,pipe_W);
            numParole++;
        }
    }
    //alla fine dobbiamo segnalare a W che abbiamo finito
    fputs("stringExit\n",pipe_W);
    wait(NULL);
    wait(NULL);
    wait(NULL);
    close(pipePW[1]);
    msgctl(msg_ds,IPC_RMID,NULL);
    printf("padre finisce\n");
}
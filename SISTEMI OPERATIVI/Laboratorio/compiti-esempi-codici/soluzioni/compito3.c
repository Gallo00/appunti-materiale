#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>

#define MSG_SIZE 24
#define BUFSIZE 2048

#define P 1
#define R 2
#define W 3

typedef struct{
    long type;
    char text[MSG_SIZE];
}msg;

int palindroma(char* str)
{
    int len=strlen(str);
    for (int i = 0; i <len/2; i++)
    {
        if (str[i]!=str[len-1-i])
        {
            return 0; //non palindroma
        }
    }
    return 1; //palindroma
}

void figlioR(FILE* fin, int coda)
{
    //figlio che deve leggere da fin e mandare messaggi su coda
    char buffer[MSG_SIZE];
    msg messaggio;

    while (fgets(buffer,MSG_SIZE,fin)!=NULL && strcmp(buffer,"quit\n")!=0)
    {
        //potrebbe esserci \n 
        if (buffer[strlen(buffer)-1]=='\n')
        {
            buffer[strlen(buffer)-1]='\0';
        }
        //mandare messaggio
        messaggio.type=P;
        strncpy(messaggio.text,buffer,MSG_SIZE);
        msgsnd(coda, &messaggio, sizeof(msg)-sizeof(long),0);
        usleep(5);
    }
    //fine file o su stdin è stato scritto quit, mandare quit
    messaggio.type=P;
    strncpy(messaggio.text,"quit",MSG_SIZE);
    msgsnd(coda, &messaggio, sizeof(msg)-sizeof(long),0);
    printf("figlioR finisce...\n");
    exit(1);
}

void figlioW(FILE* fout,int coda)
{
    //gli arrivano messaggi e li scrive su fout, se gli arriva quit si interrompe
    msg messaggio;
    while (1)
    {
        msgrcv(coda, &messaggio,sizeof(msg) - sizeof(long),W,0);
        if (strcmp(messaggio.text,"quit")==0)
        {
            //fine processo
            break;
        }
        else
        {
            fprintf(fout, "%s\n",messaggio.text);
        }
    }
    printf("figlioW finisce...\n");
    exit(1);
}

int main(int argc,char* argv[])
{
    FILE* fin=stdin;
    FILE* fout=stdout;
    int coda;
    char buffer[BUFSIZE];
    msg messaggio;


    if (argc==3)
    {
        if ((fin=fopen(argv[1],"r"))==NULL)
        {
            perror("fopen");
            exit(1);
        }
        if ((fout=fopen(argv[2],"w"))==NULL)
        {
            perror("fopen");
            exit(1);
        }
    }
    else if (argc==2)
    {
        if ((fin=fopen(argv[1],"r"))==NULL)
        {
            perror("fopen");
            exit(1);
        }
    }
    //aprire coda
    if ((coda=msgget(IPC_PRIVATE,IPC_CREAT | 0660))==-1)
    {
        perror("msgget");
        exit(1);
    }

    //creare figli
    if (fork()==0)
    {
        figlioR(fin,coda); //figlioR alla fine richiama una exit
    }

    if (fork()==0)
    {
        figlioW(fout,coda); //figlioW alla fine richiama una exit
    }

    //riceve messaggi
    int i=0;
    do
    {
        if (i%10000==0)
        {
            printf("parole filtrate:%d\n",i);
        }
        
        if(msgrcv(coda, &messaggio,sizeof(msg) - sizeof(long),P,0)==-1)
        {
            perror("messaggio con errore");
            continue;
        }
        //operazione di filtraggio, se la parola è palindroma la inviamo a W
        if((strcmp(messaggio.text,"quit")!=0) && (palindroma(messaggio.text)))
        {
            //stringa palindroma, inviamo
            messaggio.type=W;
            if (msgsnd(coda, &messaggio,sizeof(msg) - sizeof(long),0)==-1)
            {
                perror("invio non riuscito");
            }
        }
        i++;
    } while (strcmp(messaggio.text,"quit")!=0);
    //segnaliamo a W che deve finire
    strncpy(messaggio.text,"quit",MSG_SIZE);
    messaggio.type=W;
    msgsnd(coda, &messaggio,sizeof(msg) - sizeof(long),0);
    
    //operazioni finite, chiudiamo la coda e fin e fout(se non sono stdin e stdout)
    msgctl(coda,IPC_RMID, NULL);
    if (fin!=stdin)
    {
         fclose(fin);
    }
    if (fout!=stdout)
    {
         fclose(fout);
    }
}
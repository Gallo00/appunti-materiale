
//debuggare
#define _GNU_SOURCE 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#define TEMPLATE_NOME_FIFO "/tmp/miaFifo%d.fifo"
#define BUFSIZE 1024

void figlioR(char* file_input,int canaleScrittura)
{
    FILE* finput,*foutput;
    char buffer[BUFSIZE];
    if (file_input==NULL)
    {
        finput=stdin;
    }
    else
    {
        if ((finput=fopen(file_input,"r"))==NULL)
        {
            perror("errore apertura stream");
            exit(1);
        }
    }

    if ((foutput=fdopen(canaleScrittura,"w"))==NULL)
    {
        perror("fdopen");
        exit(1);
    }

    //stream di input e output pronti, inviamo le righe
    while (fgets(buffer,BUFSIZE,finput)!=NULL)
    {
        fputs(buffer,foutput);
        if (strcmp(buffer,"exit\n")==0)
        {
            break;
        }
        
    }
    exit(0);
}

void figlioF(int canaleLettura,char* fifo,char* word,int insensitive,int logica_inversa)
{
    FILE* finput;
    FILE* foutput;
    char buffer[BUFSIZE];
    if ((finput=fdopen(canaleLettura,"r"))==NULL)
    {
        perror("fdopen");
        exit(1);
    }
    if ((foutput=fopen(fifo,"w"))==NULL)
    {
        perror("fopen");
        exit(1);
    }

    while (fgets(buffer,BUFSIZE,finput)!=NULL)
    {
        //controllare se nella riga contenuta in buffer vi è word
        int trovata=0;
        if (insensitive)
        {
            //se si vuole trovare una stringa in una riga ricordarsi strstr() e strcasestr
            if (strcasestr(buffer,word)!=NULL)
            {
                trovata=1;
            }
        }
        else
        {
            if (strstr(buffer,word)!=NULL)
            {
                trovata=1;
            }
        }
        if (logica_inversa==0 && trovata==1)
        {
            //inviare
            fputs(buffer,foutput);
        }
        else if (logica_inversa==1 && trovata==0)
        {
            //inviare
            fputs(buffer,foutput);
        }
    }
    exit(0);
}

void figlioW(char* fifo)
{
    //prende in input fifo da cui legge e deve scrivere su stdout
    FILE* stream;
    char buffer[BUFSIZE];

    if ((stream=fopen(fifo,"r"))==NULL)
    {
        perror("fopen");
        exit(1);
    }

    while (fgets(buffer,BUFSIZE,stream)!=NULL)
    {
        fputs(buffer,stdout);
    }
    exit(0);
}

int main(int argc,char* argv[])
{
    char* word=NULL;
    char* file_input=NULL;
    int logica_inversa=0;
    int insensitive=0;
    char buffer[BUFSIZE];
    struct stat statbuf;
    int pipeRF[2];
    char fifo[BUFSIZE];
    if (argc<2)
    {
        exit(1);
    }
    
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i],"-i")==0)
        {
            insensitive=1;
        }
        else if (strcmp(argv[i],"-v")==0)
        {
            logica_inversa=1;
        }
        else if (strlen(argv[i])>0)
        {
            if (word==NULL)
            {
                word=argv[i];
            }
            else
            {
                if ((lstat(argv[i],&statbuf)==0) && S_ISREG(statbuf.st_mode))
                {
                    file_input=argv[i];
                }
                else
                {
                    //problemi col file
                    printf("qua\n");
                    perror(argv[i]);
                    exit(1);
                }
            }
        }
    }
    
    if (word==NULL)
    {
        perror("inserisci bene i params");
        exit(1);
    }
    
    // ci sono 2 canali di comunicazione ovvero una pipe e una fifo
    if (pipe(pipeRF)==-1)
    {
        perror("pipe");
        exit(1);
    }

    //usiamo nel nome della fifo il pid del padre
    snprintf(fifo,BUFSIZE,TEMPLATE_NOME_FIFO,getpid());

    //snprintf scrive su una stringa (fifo) massimo BUFSIZE usando il format
    //creare la fifo

    //vediamo se esiste già una fifo con quel nome
    if (lstat(fifo,&statbuf)==-1)
    {
        if (!S_ISFIFO(statbuf.st_mode))
        {
            unlink(fifo);
        }

        if (mkfifo(fifo, 0660)==-1)
        {
            perror("mkfifo");
            exit(1);
        }
    }

    //abbiamo creato le strutture IPC, creiamo i processi
    if (fork()==0)
    {
        //figlioR, vuole scrivere sulla pipe, non gli interessa leggerla
        close(pipeRF[0]);
        figlioR(file_input,pipeRF[1]);
    }
    
    if (fork()==0)
    {
        //figlioF,vuole leggere dalla pipe, non gli interessa scrivere
        close(pipeRF[1]);
        figlioF(pipeRF[0],fifo,word,insensitive,logica_inversa);
    }

    if (fork()==0)
    {
        //figlioW
        close(pipeRF[0]);
        close(pipeRF[1]);
        figlioW(fifo);
    }
    
    close(pipeRF[0]);
    close(pipeRF[1]);

    wait(NULL);
    wait(NULL);
    wait(NULL);
    

    if (unlink(fifo) == -1) {
        perror(fifo);
        exit(1);
    }
    printf("\n");
    exit(0);
    
}
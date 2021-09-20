#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>

#define BUFSIZE 1024

int palindroma(char* str)
{
    //verificare se str è palindroma
    int len=strlen(str);
    if (str[len-1]=='\n')
    {
        str[len-1]='\0';
    }
    len=strlen(str);
    for (int i = 0; i <len/2; i++)
    {
        if (str[i]!=str[len-1-i])
        {
            return 0;
        }
    }
    return 1;
}

void figlioR(FILE* canaleScrittura ,FILE* fin)
{
    //apriamo uno stream su canaleScrittura
    char buffer[BUFSIZE]={'\0'};
    
    //dobbiamo leggere da fin
    while ((fgets(buffer,BUFSIZE,fin)!=NULL) && (strcmp(buffer,"quit\n")!=0))
    {
        //mettiamo su stream
        /*
        if (buffer[strlen(buffer)-1]=='\n')
        {
            buffer[strlen(buffer)-1]='\0';
        }
        */
        fprintf(canaleScrittura,"%s",buffer);
        usleep(50);
        //printf(" %d\n",fprintf(canaleScrittura,"%s",buffer));
    }
    //fine file o c'è stata una quit, segnaliamo a P
    fprintf(canaleScrittura,"quit\n");
    //fprintf(canaleScrittura,"%s","quit");
    printf("uscendo da R\n");
    exit(1);
}

void figlioW(FILE* canaleLettura,FILE* fout)
{
    //apriamo uno stream su canaleLettura
    char buffer[BUFSIZE]={'\0'};

    while ((fgets(buffer,BUFSIZE,canaleLettura)) && (strcmp(buffer,"quit\n")!=0))
    {
        fprintf(fout,"%s",buffer);
    }
    printf("uscendo da W\n");
    exit(1);
}


int main(int argc,char* argv[])
{
    FILE* fin=stdin;
    FILE* fout=stdout;

    char buffer[BUFSIZE];
    if (argc!=1 && argc!=2)
    {
        perror("errore nei parametri");
        exit(1);
    }
    
    if (argc==2)
    {
        if ((fin=fopen(argv[1], "r"))==NULL)
        {
            perror("fopen");//errore nell'apertura del file, uso stdin
            fin=stdin;
        }
    }
    //creiamo 2 pipe, una che fa R->P e una che fa P->W
    int pipeRP[2];
    int pipePW[2];

    if (pipe(pipeRP))
    {
        perror("pipe");
        exit(1);
    }
    if (pipe(pipePW))
    {
        perror("pipe");
        exit(1);
    }
    //apriamo gli stream
    //creiamo 2 processi figli, R e W
    if (fork()==0)
    {
        //figlio R vuole solo scrivere sulla PipeRP
        close(pipeRP[0]);

        close(pipePW[0]);
        close(pipePW[1]);

        FILE* streamScritturaRP;
        streamScritturaRP=fdopen(pipeRP[1],"w");
        figlioR(streamScritturaRP,fin);
    }

    if (fork()==0)
    {
        //figlio W vuole solo leggere dalla pipePW
        close(pipePW[1]);

        close(pipeRP[0]);
        close(pipeRP[1]);

        FILE* streamLetturaPW;
        streamLetturaPW=fdopen(pipePW[0],"r");
        figlioW(streamLetturaPW,fout);
    }

    FILE* streamScrittura;
    streamScrittura=fdopen(pipePW[1],"w");
    FILE* streamLettura;
    streamLettura=fdopen(pipeRP[0],"r");

    //il padre vuole usare pipeRP in ricezione 
    close(pipeRP[1]); //non gli interessa scrivere, solo leggere

    //il padre vuole usare pipePW solo in trasmissione
    close(pipePW[0]); //non gli interessa leggere, solo scrivere

    while ((fgets(buffer,BUFSIZE,streamLettura))  && (strcmp(buffer,"quit\n")!=0))
    {
        //vediamo se è palindroma
        /*
        buffer[strlen(buffer)-1]='\0';
        printf("padre %s",buffer); //stampa compresa di \n ?
        */
        
        if (palindroma(buffer))
        {
            //inviamo a W
            fprintf(streamScrittura,"%s",buffer);
        }
        else
        {
            printf("non palindroma\n");
        }
    }
    //abbiamo finito, segnaliamo a W di terminarsi
    fprintf(streamScrittura,"quit\n");
    close(pipePW[1]);
    close(pipeRP[0]);

    fclose(streamLettura);
    fclose(streamScrittura);

    if (fin!=stdin)
    {
        //lo chiudiamo
        fclose(fin);
    }
    printf("sto uscendo P\n");
    
}
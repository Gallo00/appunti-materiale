#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>

#define MAX_WORD_LEN 64

#define PAROLA1_MAGGIORE 1
#define PAROLA2_MAGGIORE 2
#define PAROLE_UGUALI 3

#define FINITO 1
#define NON_FINITO 2

#define DEST_C 1
#define DEST_S 2
typedef struct
{
    long tipo;
    char parola1[MAX_WORD_LEN];
    char parola2[MAX_WORD_LEN];
    int esito;  
    int fine;
}msg;

void bubblesort(char** arrayParole,int numParole,int codaMSG)
{
    for (int i = 0; i < numParole-1; i++)
    {
        for (int j = i+1; j < numParole; j++)
        {
            //mandare messaggio a comparer, se ne occuperà lui
            msg messaggioInviato;
            messaggioInviato.esito=-1;
            messaggioInviato.fine=NON_FINITO;
            messaggioInviato.tipo=DEST_C;
            strcpy(messaggioInviato.parola1,arrayParole[i]);
            strcpy(messaggioInviato.parola2,arrayParole[j]);
            msgsnd(codaMSG,&messaggioInviato,sizeof(msg)-sizeof(long),0);

            msg messaggioArrivato;
            msgrcv(codaMSG,&messaggioArrivato,sizeof(msg),DEST_S,0);
            if (messaggioArrivato.esito==PAROLA2_MAGGIORE)
            {
                //swappiamo
                char tmp[MAX_WORD_LEN];
                strcpy(tmp,arrayParole[i]);
                strcpy(arrayParole[i],arrayParole[j]);
                strcpy(arrayParole[j],tmp);
            }
        }
    }
    //bubble sort finito,inviamo un messaggio di segnalazione a comparer
    msg messaggioInviato;
    messaggioInviato.esito=-1;
    messaggioInviato.fine=FINITO;
    messaggioInviato.tipo=DEST_C;
    msgsnd(codaMSG,&messaggioInviato,sizeof(msg)-sizeof(long),0);
    exit(0);
}

void sorter(int canale_scrittura,int codaMSG,char* nomeFile)
{
    FILE* file_input=fopen(nomeFile,"r");
    FILE* pipeS=fdopen(canale_scrittura,"r");
    FILE* stream_righe=fopen(nomeFile,"r");
    int numRighe=0;
    char buffer[MAX_WORD_LEN];
    while (fgets(buffer,MAX_WORD_LEN,stream_righe))
    {
        numRighe++;
    }

    char** arrayParole;
    arrayParole=malloc(sizeof(char*)*numRighe);
    for (int i = 0; i < numRighe; i++)
    {
        arrayParole[i]=malloc(sizeof(char)*MAX_WORD_LEN);
    }
    int i=0;
    while (fgets(buffer,MAX_WORD_LEN,stream_righe))
    {
        strcpy(arrayParole[i],buffer);
        i++;
    }
    //file salvato in arrayParole
    bubblesort(arrayParole,numRighe,codaMSG);
    
    //bubble sort finito
    //mandiamo le stringhe a padre tramite la pipe
    for (int i = 0; i < numRighe; i++)
    {
        fputs(arrayParole[i],pipeS);
    }
    fputs("stringExit\n",pipeS);
    exit(0);
}

void comparer(int codaMSG)
{
    while(1)
    {
        msg messaggioArrivato;
        msg messaggioInviato;
        msgrcv(codaMSG,&messaggioArrivato,sizeof(msg),DEST_C,0);

        if (messaggioArrivato.fine==FINITO)
        {
            break;
        }
        int x=strcasecmp(messaggioArrivato.parola1,messaggioArrivato.parola2);
        if (x < 0)
        {
            messaggioInviato.esito=PAROLA2_MAGGIORE;
        }
        else if (x > 0)
        {
            messaggioInviato.esito=PAROLA1_MAGGIORE;
        }
        else
        {
            messaggioInviato.esito=PAROLE_UGUALI;
        }
        messaggioInviato.tipo=DEST_S;
        messaggioInviato.fine=NON_FINITO;
        msgsnd(codaMSG,&messaggioInviato,sizeof(msg)-sizeof(long),0);
    }
}

int main(int argc,char* argv[])
{
    if (argc!=2)
    {
        perror("metti il file");
        exit(1);
    }
    struct stat statbuf;
    if (stat(argv[1],&statbuf)==-1)
    {
        perror("file non usabile");
        exit(1);
    }
    int codaMSG;
    if ((codaMSG=msgget(IPC_PRIVATE,IPC_CREAT | 0660))==-1)
    {
        perror("msgget");
        exit(1);
    }
    int pipeSP[2];
    if (pipe(pipeSP)==-1)
    {
        printf("pipe");
        exit(1);
    }

    //creiamo i 2 processi
    if (fork()==0)
    {
        close(pipeSP[0]);
        sorter(pipeSP[1],codaMSG,argv[1]);
    }

    if (fork()==0)
    {
        close(pipeSP[0]);
        close(pipeSP[1]);
        comparer(codaMSG);
    }
    
    close(pipeSP[1]);
    FILE* canale_lettura=fdopen(pipeSP[0],"r");
    char buffer[MAX_WORD_LEN];
    while (fgets(buffer,MAX_WORD_LEN,canale_lettura))
    {
        if (strcmp(buffer,"StringExit\n")==0)
        {
            break;
        }
        printf("%s",buffer);
    }
    
    wait(NULL);
    wait(NULL);
    msgctl(codaMSG,IPC_RMID,NULL);
}
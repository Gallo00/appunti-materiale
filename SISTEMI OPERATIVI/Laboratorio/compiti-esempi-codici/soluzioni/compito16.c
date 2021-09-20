
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <ctype.h>

#define ALPH_SIZE 26
#define LINE_SIZE 1024
#define FINITO 1
#define NON_FINITO 2
#define DEST_P 1
#define DEST_C 2

typedef struct
{
    long tipo;
    int occorrenze[ALPH_SIZE];
    int finito;
}msgCP;

typedef struct
{
    long tipo;
    char riga[LINE_SIZE];
    int finito;
}msgRC;

void counter(int codaCP,int codaRC,int numFile)
{
    //riceve una riga e conteggia i char
    int reader_finiti=0;
    while (1)
    {
        msgRC messaggioArrivato;
        msgrcv(codaRC,&messaggioArrivato,sizeof(msgRC),DEST_C,0);
        //printf("mi e' arrivato %s",messaggioArrivato.riga);
        //controllo fine
        if (messaggioArrivato.finito==FINITO)
        {
            reader_finiti++;
            if (reader_finiti==numFile)
            {
                break;
            }
        }
        else
        {
            //controllare occorrenza di ogni char
            msgCP messaggioDaMandare;
            messaggioDaMandare.finito=NON_FINITO;
            messaggioDaMandare.tipo=DEST_P;
            for (int i = 0; i < ALPH_SIZE; i++)
            {
                messaggioDaMandare.occorrenze[i]=0;
            }
            
            for (int i = 0; i < ALPH_SIZE; i++)
            {
                char carattere= i + 'a';
                for (int j = 0; j < strlen(messaggioArrivato.riga) - 1; j++)
                {
                    if (tolower(messaggioArrivato.riga[j])==carattere)
                    {
                        messaggioDaMandare.occorrenze[i]++;
                    }
                }
            }
            /*
            printf("%s---sto inviando: \n",messaggioArrivato.riga);
            for (int i = 0; i < ALPH_SIZE; i++)
            {
                printf("%c : %d \n",i+'a',messaggioDaMandare.occorrenze[i]);
            }
            */
            msgsnd(codaCP,&messaggioDaMandare,sizeof(msgCP)-sizeof(long),0);
        }
    }
    //se sono fuori dal while ho finito, segnalo a Padre
    msgCP messaggioDaMandare;
    messaggioDaMandare.finito=FINITO;
    messaggioDaMandare.tipo=DEST_P;
    msgsnd(codaCP,&messaggioDaMandare,sizeof(msgCP)-sizeof(long),0);
    exit(0);
}

void reader(int codaRC,char* nomeFile)
{
    //legge dal file
    FILE* file_input=fopen(nomeFile,"r");
    char buffer[LINE_SIZE];
    while (fgets(buffer,LINE_SIZE,file_input))
    {
        //printf("%s",buffer);
        msgRC messaggio;
        messaggio.finito=NON_FINITO;
        messaggio.tipo=DEST_C;
        strcpy(messaggio.riga,buffer);
        msgsnd(codaRC,&messaggio,sizeof(msgRC) - sizeof(long), 0);
    }
    //quando abbiamo finito inviamo un messaggio di segnalazione
    msgRC messaggio;
    messaggio.finito=FINITO;
    messaggio.tipo=DEST_C;
    msgsnd(codaRC,&messaggio,sizeof(msgRC) - sizeof(long), 0);
    exit(0);
}

int main(int argc,char* argv[])
{
    if (argc<2)
    {
        perror("metti parametri");
        exit(1);
    }

    struct stat statbuf;
    int numFile=0;
    //controlliamo i file
    for (int i = 1; i < argc; i++)
    {
        if (stat(argv[i],&statbuf)!=-1 && S_ISREG(statbuf.st_mode))
        {
            numFile++;
        }
    }
    if (numFile==0)
    {
        perror("nemmeno un file valido");
        exit(1);
    }

    //creare coda di messaggi R -> C
    int codaRC;
    if ((codaRC=msgget(IPC_PRIVATE ,IPC_CREAT | 0660))==-1)
    {
        perror("msgget");
        exit(1);
    }

    //creare coda di messaggi C -> P
    int codaCP;
    if ((codaCP=msgget(IPC_PRIVATE ,IPC_CREAT | 0660))==-1)
    {
        perror("msgget");
        exit(1);
    }
    
    //creare i figli
    if (fork()==0)
    {
        //processo counter
        counter(codaCP,codaRC,numFile);
    }
    
    for (int i = 1; i < argc; i++)
    {
        if (stat(argv[i],&statbuf)!=-1 && S_ISREG(statbuf.st_mode))
        {
            if (fork()==0)
            {
                reader(codaRC,argv[i]);
            }
        }
    }
    int occorrenze_totali[ALPH_SIZE];
    for (int i = 0; i <ALPH_SIZE; i++)
    {
        occorrenze_totali[i]=0;
    }
    
    while(1)
    {
        //ascoltiamo i messaggi di counter
        msgCP messaggio;
        msgrcv(codaCP,&messaggio,sizeof(msgCP),DEST_P,0);
        if (messaggio.finito==FINITO)
        {
            break;
        }
        else
        {
            for (int i = 0; i < ALPH_SIZE; i++)
            {
                occorrenze_totali[i]+=messaggio.occorrenze[i];
            }
        }
    }
    //alla fine del while visualizziamo le occorrenze
    printf("--------------OCCORRENZE TOTALI-----------------\n");
    for (int i = 0; i < ALPH_SIZE; i++)
    {
        printf("%c : %d \n",i+'a',occorrenze_totali[i]);
    }
    exit(0);
    
}
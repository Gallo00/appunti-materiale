
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

#define DEST_J 1 //padre

#define SCONFITTA 1
#define VITTORIA 2
#define PATTA 3
#define FINE_TORNEO 4

typedef struct
{
    long tipo;
    int mossa;
    int esito;
}msg;

void giocatore(int msg_ds,int id)
{
    srand(time(NULL) + id);
    //il giocatore si mette in un while(1)
    while (1)
    {
        //invia messaggio
        msg messaggio;
        messaggio.tipo=DEST_J;
        messaggio.esito=-1;
        messaggio.mossa=rand()% 10; //numero casuale tra 0 e 9 , se avessimo voluto tra 2 e 9 era rand()%(9-2) +2
        msgsnd(msg_ds,&messaggio,sizeof(msg) - sizeof(long),0);
        
        //inviato il messaggio aspettiamo una risposta
        msgrcv(msg_ds,&messaggio,sizeof(msg),id,0);
        if (messaggio.esito==FINE_TORNEO)
        {
            break;
        }
        //non ci preoccupiamo di tenere il nostro punteggio, lo fa il padre
    }
    //printf("giocatore_%d finisce \n",id);
    exit(0);
}

int main(int argc,char* argv[])
{
    if (argc!=3)
    {
        perror("errore parametri");
        exit(1);
    }
    int n=atoi(argv[1]);
    int m=atoi(argv[2]);
    if (n<2 || n>6)
    {
        perror("n deve essere tra 2 e 6");
        exit(1);
    }
    if (m < 1)
    {
        perror("m deve essere almeno 1");
        exit(1);
    }
    
    //creare coda di messaggi
    int msg_ds;
    if ((msg_ds=msgget(IPC_PRIVATE, IPC_CREAT | 0660))==-1)
    {
        perror("msgget");
        exit(1);
    }
    //creare gli n figli
    for (int i = 0; i < n; i++)
    {
        if (fork()==0)
        {
            //processo giocatore i
            giocatore(msg_ds,i+1); //ID vanno da 1 in poi
        }
    }
    int partite_finite=0;
    int punti[n];
    for (int i = 0; i < n; i++)
    {
        punti[i]=0;
    }
    
    while(1)
    {
        msg arrayMessaggi[n];
        for (int i = 0; i < n; i++)
        {
            msgrcv(msg_ds,&(arrayMessaggi[i]),sizeof(msg),DEST_J,0);
        }
        //controllare se c'è parità
        int patta=0;
        for (int i = 0; i < n-1; i++)
        {
            for (int j = i+1; j < n; j++)
            {
                if (arrayMessaggi[i].mossa==arrayMessaggi[j].mossa)
                {
                    patta=1;
                    i=n;
                    j=n;
                }
            }
        }
        if (patta==0)
        {
            //possiamo eseguire la partita
            int vincitore=0;
            for (int i = 0; i < n; i++)
            {
                vincitore+=arrayMessaggi[i].mossa;
            }
            vincitore=vincitore % n;
            punti[vincitore]++;
            //segnaliamo ai giocatori
            for (int i = 0; i < n; i++)
            {
                arrayMessaggi[i].esito=SCONFITTA;
                arrayMessaggi[i].tipo=i+1; 
            }
            arrayMessaggi[vincitore].esito=VITTORIA;
            for (int i = 0; i < n; i++)
            {
                msgsnd(msg_ds,&(arrayMessaggi[i]),sizeof(msg) - sizeof(long),0);
            }
            partite_finite++;
            if (partite_finite==m)
            {
                break;
            }
        }
        else
        {
            //segnaliamo ai giocatori che c'è stata parità
            for (int i = 0; i < n; i++)
            {
                arrayMessaggi[i].esito=PATTA;
                arrayMessaggi[i].tipo=i+1; 
            }
            for (int i = 0; i < n; i++)
            {
                msgsnd(msg_ds,&(arrayMessaggi[i]),sizeof(msg) - sizeof(long),0);
            }
        }
    }
    //fine del while ovvero fine torneo, segnaliamo ai giocatori
    msg arrayMessaggi[n]; 
    for (int i = 0; i < n; i++)
    {
        arrayMessaggi[i].esito=FINE_TORNEO;
        arrayMessaggi[i].tipo=i+1; 
    }
    for (int i = 0; i < n; i++)
    {
        msgsnd(msg_ds,&(arrayMessaggi[i]),sizeof(msg) - sizeof(long),0);
    }
    for (int i = 0; i < n; i++)
    {
        wait(NULL);
    }
    for (int i = 0; i < n; i++)
    {
        printf("giocatore_%d ha fatto %d punti\n",i+1,punti[i]);
    }
    int esisteVincitore=1;
    //trovare il massimo
    int ind_max=0;
    int max=-1;
    for (int i = 0; i < n; i++)
    {
        if (punti[i] > max)
        {
            max=punti[i];
            ind_max=i;
        }
    }
    //printf("%d %d\n",max,ind_max);
    //vedere se ha duplicati
    for (int i = 0; i < n; i++)
    {
        if (punti[i]==max && i!=ind_max)
        {
            esisteVincitore=0;
            break;
        }
    }
    if (esisteVincitore==1)
    {
        printf("vincitore: giocatore_%d\n",ind_max + 1);
    }
    msgctl(msg_ds,IPC_RMID,NULL);
}

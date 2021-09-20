#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/ipc.h>
#include <sys/msg.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PATH 2048

#define DEST_P 1
#define DEST_A 2

#define FINITO 1
#define NON_FINITO 2

typedef struct
{
    long tipo;
    char file[PATH];
    int fine;
    int tot;
}msg;

void scanner(int codaMSG,char* dirName,int chiamata)
{
    //chdir(dirName);
    printf("SCANNER SONO IN %s\n",dirName);
    DIR* directory=opendir(dirName);
    struct dirent* entry;
    struct stat statbuf;
    while ((entry=readdir(directory))!=NULL)
    {
        //3 casi
        //file regolare: inviare mex a analyzer
        //directory: entrare ricorsivamente
        //file non leggibile: non fare nulla

        char buffer[PATH];
        strcpy(buffer,dirName);
        strcat(buffer,"/");
        strcat(buffer,entry->d_name);

        if (stat(buffer,&statbuf)==-1)
        {
            continue;
        }
        if (S_ISREG(statbuf.st_mode))
        {
            printf("SCANNER: %s\n",buffer);
            msg messaggio;
            messaggio.fine=NON_FINITO;
            messaggio.tipo=DEST_A;
            messaggio.tot=-1; //non è un valore di suo interesse
            strcpy(messaggio.file,buffer);
            msgsnd(codaMSG,&messaggio,sizeof(msg) - sizeof(long),0);
        }
        else if (S_ISDIR(statbuf.st_mode) && strcmp(entry->d_name,".")!=0 && strcmp(entry->d_name,"..")!=0)
        {
            //fare ricorsione
            scanner(codaMSG,buffer,chiamata+1);
        }
    }
    //fine ciclo, se è la prima chiamata chiudiamo il processo
    //segnalandolo ad analyzer
    if (chiamata==1)
    {
        msg messaggio;
        messaggio.fine=FINITO;
        messaggio.tipo=DEST_A;
        messaggio.tot=-1; //non è un valore di suo interesse
        msgsnd(codaMSG,&messaggio,sizeof(msg) - sizeof(long),0);
        printf("SCANNER FINISCE\n");
        exit(0);
    }
}

void analyzer(int codaMSG)
{
    while (1)
    {
        msg messaggioRicevuto;
        msgrcv(codaMSG,&messaggioRicevuto,sizeof(msg),DEST_A,0);
        if (messaggioRicevuto.fine==FINITO)
        {
            break;
        }
        //apriamo il file
        int fd=open(messaggioRicevuto.file,O_RDONLY);
        //scopriamone la size
        struct stat statbuf;
        stat(messaggioRicevuto.file,&statbuf);
        //mappiamo il file ricevuto
        char* map;
        map=mmap(NULL,statbuf.st_size,PROT_READ,MAP_SHARED,fd,0);

        int counter=0; //conta i caratteri alfabetici
        //adesso possiamo leggere il file
        for (int i = 0; i < statbuf.st_size; i++)
        {
            if ((map[i]>='a' && map[i]<='z') || (map[i]>='A' && map[i]<='Z') )
            {
                counter++;
            }
        }
        //lettura file finita, demappiamo
        munmap(map,statbuf.st_size);
        
        //stampa risultato
        printf("ANALYZER: %s %d\n",messaggioRicevuto.file,counter);
        //prepariamo un messaggio per il padre
        msg messaggioInviato;
        messaggioInviato.fine=NON_FINITO;
        messaggioInviato.tot=counter;
        messaggioInviato.tipo=DEST_P;
        msgsnd(codaMSG,&messaggioInviato,sizeof(msg) - sizeof(long),0);
    }
    //fine del ciclo e del processo, segnaliamo al padre
    msg messaggioInviato;
    messaggioInviato.fine=FINITO;
    messaggioInviato.tipo=DEST_P;
    msgsnd(codaMSG,&messaggioInviato,sizeof(msg) - sizeof(long),0);
    printf("ANALYZER FINISCE\n");
    exit(0);
}

int main(int argc,char* argv[])
{
    char directory[PATH];
    getcwd(directory,PATH);
    if (argc!=1 && argc!=2)
    {
        perror("o niente o cartella");
        exit(1);
    }
    if (argc==2)
    {
        strcpy(directory,argv[1]);
    }

    //creare coda di messaggi
    int codaMSG;
    if ((codaMSG=msgget(IPC_PRIVATE ,IPC_CREAT | 0660))==-1)
    {
        perror("msgget");
        exit(1);
    }

    //creare figli
    if (fork()==0)
    {
        scanner(codaMSG,directory,1);
    }
    
    if (fork()==0)
    {
        analyzer(codaMSG);
    }
    
    int num_alph=0;
    while (1)
    {
        //ci mettiamo in ascolto e aggiorniamo la variabile num_alph
        msg messaggio;
        msgrcv(codaMSG,&messaggio,sizeof(msg),DEST_P,0);
        //controllo fine
        if (messaggio.fine==FINITO)
        {
            break;
        }
        num_alph+=messaggio.tot;
    }
    //fine ciclo, visualizziamo il totale
    wait(NULL);
    wait(NULL);
    printf("PADRE: totale di %d caratteri alfabetici\n",num_alph);
    msgctl(codaMSG,IPC_RMID,NULL);
}
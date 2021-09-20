
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>


#define ALPH_SIZE 26

typedef struct{
    long type;
    long occorrenze[ALPH_SIZE];
}msg;

void figlio(int numfiglio,char* file,int coda)
{
    //il figlio deve contare le occorrenze di ogni lettera contenuta in file e mandare un messaggio al padre
    //su coda con queste informazioni
    //stamperà anche a schermo le sue info 'locali'
    //il tutto va fatto mappando la memoria

    msg messaggio;
    int fd;
    char* map; //mappa del file che andremo a scorrere come fosse un array

    messaggio.type=1;
    for (int i = 0; i < ALPH_SIZE; i++)
    {
        messaggio.occorrenze[i]=0;
    }

    //controllare se è file regolare
    struct stat statbuf;
    if (stat(file,&statbuf)==-1)
    {
        messaggio.type=2; //errore
        msgsnd(coda,&messaggio,sizeof(msg) - sizeof(long),0);
        exit(1);
    }

    //apriamo il file
    if ((fd=open(file,O_RDONLY))==-1)
    {
        messaggio.type=2; //errore
        msgsnd(coda,&messaggio,sizeof(msg) - sizeof(long),0);
        exit(1);
    }

    //mappiamo il file
    if ((map=mmap(NULL,statbuf.st_size,PROT_READ,MAP_SHARED,fd,0))==MAP_FAILED)
    {
        messaggio.type=2; //errore
        msgsnd(coda,&messaggio,sizeof(msg) - sizeof(long),0);
        exit(1);
    }
    
    //adesso possiamo leggere map
    for (int i = 0; i <statbuf.st_size; i++)
    {
        //solo char alfabeto
        if (map[i]>='a' && map[i]<='z')
        {
            messaggio.occorrenze[map[i] - 'a']++;
        }
        else if (map[i]>='A' && map[i]<='Z')
        {
            messaggio.occorrenze[map[i]-'A']++;
        }
    }
    //informazioni ottenute, stampiamo le info, inviamo il messaggio e poi chiudiamo file descriptor e memoria mappata
    printf("figlio %d :",numfiglio);
    for (int i = 0; i < ALPH_SIZE; i++)
    {
        printf("%c:%ld" , 'a' + i,messaggio.occorrenze[i]);
    }
    printf("\n");

    msgsnd(coda,&messaggio,sizeof(msg) - sizeof(long),0);
    close(fd);
    munmap(map,statbuf.st_size);
    exit(0);
}

int main(int argc, char* argv[])
{
    int qmsg;
    long occorrenze_tot[ALPH_SIZE];
    msg messaggio;
    if (argc<=1)
    {
        perror("errore coi parametri");
        exit(1);
    }

    //creare coda di messaggi
    if ((qmsg= msgget( IPC_PRIVATE,IPC_CREAT | 0660))==-1)
    {
        perror("msgget");
        exit(1);
    }
    
    //dedicare un processo a ogni file
    for (int i = 1; i < argc; i++)
    {
        if (fork()==0)
        {
            //codice figlio
            figlio(i,argv[i],qmsg);
        }
    }
    int figli=argc-1;

    //settare occ tot a 0
    for (int i = 0; i < ALPH_SIZE; i++)
    {
        occorrenze_tot[i]=0;
    }
    
    //si deve ora aspettare il padre un messaggio da ciascun figlio per aggiornare occorrenze tot
    for (int i = 0; i < figli; i++)
    {
        if (msgrcv(qmsg, &messaggio,sizeof(msg) - sizeof(long), 0,0)==-1)
        {
            perror("msgrcv");
            exit(1);
        }
        if (messaggio.type==2)
        {
            printf("errore dal figlio, lo ignoro\n"); //l'errore potrebbe essere qualsias, file non esistente ad esempio
            continue;
        }
        //arrivati qua sommiamo l'array dentro messaggio a occorrenze tot
        for (int j = 0; j < ALPH_SIZE; j++)
        {
            occorrenze_tot[j] = occorrenze_tot[j] + messaggio.occorrenze[j];
        }
    }
    
    //visualizzare totali e vedere se c'è un massimo assoluto
    int pos_max=0;
    int parita=0;
    for (int i = 0; i < ALPH_SIZE; i++)
    {
        printf("%c: %ld" , 'a' + i,occorrenze_tot[i]);
        if (occorrenze_tot[i]==occorrenze_tot[pos_max])
        {
            parita=1;
        }
        else if (occorrenze_tot[i]>occorrenze_tot[pos_max])
        {
            pos_max=i;
            parita=0;
        }
    }
    printf("\n");
    if (!parita)
    {
        printf("il max assoluto e':%c",'a'+pos_max);
    }
    //lavoro del padre praticamente finito, deve rimuovere la coda

    if (msgctl(qmsg,IPC_RMID,NULL)==-1)
    {
        perror("msgctl");
        exit(1);
    }
    
}
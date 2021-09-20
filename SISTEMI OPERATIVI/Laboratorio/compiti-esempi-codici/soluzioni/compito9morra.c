
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <time.h>

#define SEM_G 0
#define SEM_P1 1
#define SEM_P2 2
#define SEM_T 3

#define S 0
#define C 1
#define F 2

#define P1 1
#define P2 2
#define PAREGGIO 3

#define FINITO 1
#define NON_FINITO 2

typedef struct{
    int mossa_P1;
    int mossa_P2;
    int vincitore;
    int fine_torneo;
}partita;

int scontro(int mossa1,int mossa2)
{
    if (mossa1==mossa2)
    {
        return 0; //pareggio
    }
    else if (mossa1==S && mossa2==C)
    {
        return 1; //vittoria mossa2
    }
    else if (mossa1==S && mossa2==F)
    {
        return -1; //vittoria mossa1
    }
    else if (mossa1==C && mossa2==S)
    {
        return -1; //vittoria mossa1
    }
    else if (mossa1==C && mossa2==F)
    {
        return 1; //vittoria mossa2
    }
    else if (mossa1==F && mossa2==S)
    {
        return 1; //vittoria mossa2
    }
    else if (mossa1==F && mossa2==C)
    {
        return -1; //vittoria mossa1
    }
    printf("errore nella funzione scontro\n");
    return 2; //in teoria non dovrebbe mai ritornarlo
}

int WAIT(int sem_des, int num_semaforo){
    struct sembuf operazioni[1] = {{num_semaforo,-1,0}};
    return semop(sem_des, operazioni, 1);
}

int SIGNAL(int sem_des, int num_semaforo){
    struct sembuf operazioni[1] = {{num_semaforo,+1,0}};
    return semop(sem_des, operazioni, 1);
}

void player1(int sem_ds,partita* record,int numero_partite)
{
    srand(333222111);
    while(1)
    {
        WAIT(sem_ds,SEM_P1);
        if (record->fine_torneo==FINITO)
        {
            //fine torneo
            break;
        }
        int mossa=rand()%3; //torna valore tra 0,1 e 2
        (*record).mossa_P1=mossa;
        if(mossa==C) printf("P1 mossa:CARTA\n");
        if(mossa==S) printf("P1 mossa:SASSO\n");
        if(mossa==F) printf("P1 mossa:FORBICE\n");
        sleep(3);
        SIGNAL(sem_ds,SEM_G);
    }
    exit(0);
}

void player2(int sem_ds,partita* record,int numero_partite)
{
    srand(111222333);
    while(1)
    {
        WAIT(sem_ds,SEM_P2);
        if (record->fine_torneo==FINITO)
        {
            //fine torneo
            break;
        }
        int mossa=rand()%3; //torna valore tra 0,1 e 2
        (*record).mossa_P2=mossa;
        if(mossa==C) printf("P2 mossa:CARTA\n");
        if(mossa==S) printf("P2 mossa:SASSO\n");
        if(mossa==F) printf("P2 mossa:FORBICE\n");
        sleep(3);
        SIGNAL(sem_ds,SEM_G);
    }
    exit(0);
}
void giudice(int sem_ds,partita* record,int numero_partite)
{
    for (int i = 1; i <= numero_partite; i++)
    {
        SIGNAL(sem_ds,SEM_P1);
        SIGNAL(sem_ds,SEM_P2);
        WAIT(sem_ds,SEM_G);
        WAIT(sem_ds,SEM_G);

        //arrivato a questo punto può controllare il risultato
        switch (scontro(record->mossa_P1,record->mossa_P2))
        {
        case -1:
            //vittoria mossa1
            record->vincitore=P1;
            printf("G: vincitore partita n.%d P1\n",i);
            //segnaliamo a tabellone di fare aggiornamento
            SIGNAL(sem_ds,SEM_T);
            WAIT(sem_ds,SEM_G); //ci mettiamo in attesa(ci risveglierà T)
            break;
        case 0:
            //pareggio
            record->vincitore=PAREGGIO;
            printf("G:partita n.%d pareggiata, da ripetere\n",i);
            i--;
            //in caso di pareggio non c'è bisogno di segnalare nulla a T
            break;
        case 1:
            //vittoria mossa2
            record->vincitore=P2;
            printf("G: vincitore partita n.%d P2\n",i);
            //segnaliamo a tabellone di fare aggiornamento
            SIGNAL(sem_ds,SEM_T);
            WAIT(sem_ds,SEM_G); //ci mettiamo in attesa(ci risveglierà T)
            break;
        }
        sleep(3);
    }
    //arrivati qui è finita la partita, lo segnaliamo a player1 e player2 facendo una signal e usando il campo
    //torneo finito
    record->fine_torneo=FINITO;
    SIGNAL(sem_ds,SEM_P1);
    SIGNAL(sem_ds,SEM_P2);

    //facciamo signal a tabellone, vedrà il campo fine torneo e manderà le ultime stats
    SIGNAL(sem_ds,SEM_T);

    exit(0);
}
void tabellone(int sem_ds,partita* record)
{
    int puntiP1=0;
    int puntiP2=0;
    while (1)
    {
        WAIT(sem_ds,SEM_T);
        if (record->fine_torneo==FINITO)
        {
            //fine torneo
            break;
        }
        if (record->vincitore==P1)
        {
            puntiP1++;
        }
        else
        {
            puntiP2++; 
        }
        printf("T: classifica temp: P1:%d , P2:%d\n",puntiP1,puntiP2);
        sleep(3);
        SIGNAL(sem_ds,SEM_G);
    }
    //fine partita
    printf("T: classifica finale: P1:%d , P2:%d\n",puntiP1,puntiP2);
    if (puntiP1==puntiP2)
    {
        printf("pareggio\n");
    }
    else if (puntiP1>puntiP2)
    {
        printf("Vincitore:P1\n");
    }
    else
    {
        printf("Vincitore:P2\n");
    }
    sleep(3);
    exit(0);
}

int main(int argc,char* argv[])
{
    int numero_partite;
    int mem_ds;
    partita* record;
    int sem_ds;
    if (argc!=2)
    {
        perror("errore nei params");
        exit(1);
    }
    numero_partite=atoi(argv[1]);
    if (numero_partite<=0)
    {
        perror("errore nei params");
        exit(1);
    }

    //creare memoria e semafori per gestirla
    if ((mem_ds=shmget(IPC_PRIVATE,sizeof(partita),IPC_CREAT | 0660))==-1)
    {
        perror("shmget");
        exit(1);
    }
    
    if ((record=(partita*)shmat(mem_ds,NULL,0))==(partita*)-1)
    {
        perror("shmat");
        exit(1);
    }
    
    if ((sem_ds=semget(IPC_PRIVATE,4,IPC_CREAT | 0660))==-1)
    {
        perror("semget");
        exit(1);
    }
    
    if (semctl(sem_ds,SEM_G,SETVAL,0)==-1)
    {
        perror("semctl");
        exit(1);
    }
    if (semctl(sem_ds,SEM_P1,SETVAL,0)==-1)
    {
        perror("semctl");
        exit(1);
    }
    if (semctl(sem_ds,SEM_P2,SETVAL,0)==-1)
    {
        perror("semctl");
        exit(1);
    }
    if (semctl(sem_ds,SEM_T,SETVAL,0)==-1)
    {
        perror("semctl");
        exit(1);
    }
    
    (*record).fine_torneo=NON_FINITO;

    if (fork()==0)
    {
        player1(sem_ds,record,numero_partite);
    }
    if (fork()==0)
    {
        player2(sem_ds,record,numero_partite);
    }
    if (fork()==0)
    {
        giudice(sem_ds,record,numero_partite);
    }
    if (fork()==0)
    {
        tabellone(sem_ds,record);
    }
    wait(NULL);
    wait(NULL);
    wait(NULL);
    wait(NULL);



}
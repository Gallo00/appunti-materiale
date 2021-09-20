
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/msg.h>

#define WORD_LEN 32
#define FILE_LEN 128
#define LINE_LEN 1024

typedef struct
{
    long figlio;
    char parola[WORD_LEN];
}msg_PF;

#define FINITO 1
#define NON_FINITO 2
typedef struct
{
    long tipo;
    char parolaTrovata[WORD_LEN];
    int numRiga;
    char riga[FILE_LEN];
    int finito;
}msg_FP;

void ricercatore(int codaPF,int codaFP,char* nomeFile,int id,int numParole)
{
    FILE* stream_righe=fopen(nomeFile,"r"); //serve a scoprire quanti \n ci sono
    FILE* file_input=fopen(nomeFile,"r");
    char buffer[LINE_LEN];
    int numRighe=0;
    while (fgets(buffer,LINE_LEN,stream_righe)!=NULL)
    {
        numRighe++;
    }
    char** arrayRighe;
    arrayRighe=malloc(numRighe*sizeof(char*));
    for (int i = 0; i < numRighe; i++)
    {
        arrayRighe[i]=malloc(sizeof(char)*LINE_LEN);
        fgets(arrayRighe[i],LINE_LEN,file_input);
    }
    //Ora in arrayRighe ci sono tutte le righe del nostro file
    for (int i = 0; i < numParole; i++)
    {
        //ascoltiamo la parola ed effettuiamo la ricerca(sull'array)
        char parola[WORD_LEN];
        msg_PF messaggioPF;
        msgrcv(codaPF,&messaggioPF,sizeof(msg_PF), id ,0);
        strcpy(parola,messaggioPF.parola);
        printf("figlio%d devo cercare %s\n",id,parola);

        for (int j = 0; j < numRighe; j++)
        {
            if (strstr(arrayRighe[j],parola)!=NULL)
            {
                //parola trovata, inviamo un mex
                msg_FP messaggioFP;
                messaggioFP.tipo=id;
                messaggioFP.finito=NON_FINITO;
                messaggioFP.numRiga=j;
                strcpy(messaggioFP.riga,arrayRighe[j]);
                strcpy(messaggioFP.parolaTrovata,parola);
                msgsnd(codaFP, &messaggioFP , sizeof(msg_FP) - sizeof(long), 0);
            }
        }
    }
    //alla fine di questo for avremo fatto la ricerca di tutte le parole nel file e avremo inviato i messaggi
    //inviare un ultimo messaggio per segnalare il fatto che abbiamo finito
    msg_FP messaggioFP;
    messaggioFP.tipo=id;
    messaggioFP.finito=FINITO;
    msgsnd(codaFP, &messaggioFP , sizeof(msg_FP) - sizeof(long), 0);
    exit(0);
}

int main(int argc,char* argv[])
{
    if (argc<4)
    {
        perror("metti: nomeExe word1 [word2 ...] @ file1 [file2 ...]");
        exit(1);
    }

    //contiamo le parole
    //i file saranno ARGC - (1+NUMPAROLE+1)  i due 1 sono: NomeEXE e @
    int i=1;
    int numParole=0;
    while(strcmp(argv[i],"@")!=0)
    {
        numParole++;
        i++;
    }
    if (numParole==0)
    {
        perror("metti: nomeExe word1 [word2 ...] @ file1 [file2 ...]");
        exit(1);
    }
    int numFile=argc - (1+numParole+1);
    if (numFile==0)
    {
        perror("metti: nomeExe word1 [word2 ...] @ file1 [file2 ...]");
        exit(1);
    }
    
    int codaPF_ds;
    int codaFP_ds;
    struct stat statbuf;
    //creiamo le code di messaggi
    if ((codaPF_ds=msgget(IPC_PRIVATE,IPC_CREAT | 0660))==-1)
    {
        perror("msgget");
        exit(1);
    }
    if ((codaFP_ds=msgget(IPC_PRIVATE,IPC_CREAT | 0660))==-1)
    {
        perror("msgget");
        exit(1);
    }

    //creiamo i figli, gli associamo a ognuno un file
    for ( i = 1 + numParole + 1; i < argc; i++)
    {
        //prima controlliamo il file vada bene
        // printf("%s\n",argv[i]);
        if (stat(argv[i],&statbuf)!=-1 && S_ISREG(statbuf.st_mode))
        {
            if (fork()==0)
            {
                //processo figlio
                ricercatore(codaPF_ds,codaFP_ds,argv[i],i-(numParole +1),numParole); //id : 1,2 ...
            }
        }
        else
        {
            numFile--; //c'è un file che non va bene
        }
    }
    if (numFile==0)
    {
        //se è così sono avvenute 0 fork
        perror("Nemmeno un file valido");
        exit(1);
    }
    sleep(2);
    msg_PF messaggioPF;
    for ( i = 1; i <= numParole; i++)
    {
        //inviamo word-i a tutti i figli
        for (int j = 1 + numParole + 1; j < argc; j++)
        {
            messaggioPF.figlio= j - (1 + numParole + 1) +1;  //come figli facciamo 1, 2 e così via invece di partire da 0
            strcpy(messaggioPF.parola,argv[i]);
            printf("padre: invio %s a %ld\n",argv[i],messaggioPF.figlio);
            msgsnd(codaPF_ds,&messaggioPF, sizeof(msg_PF) - sizeof(long),0);
        }
    }
    
    //adesso deve mettersi in ascolto dei figli,un figlio con un id
    //quando trova parola in una riga manda
    //parola@nome-file:numeroLinea:interaLinea

    //il padre dovrà tenere dei contatori, alla fine di tutti i messaggi
    //visualizzerà
    /*
    nome-file-1:occorrenze-totali-per-tutte-le-parole //in sostanza se Figlio1 ha mandato 4 messaggi il campo occorrenze-totali sarà 4
    nome-file-2:occorrenze-totali-per-tutte-le-parole
    …
    nome-file-n:occorrenze-totali-per-tutte-le-parole
    */
    msg_FP messaggioFP;
    int figliFiniti=0;
    int arrayOccorrenze[numFile];
    for (i = 0; i < numFile; i++)
    {
        arrayOccorrenze[i]=0;
    }
    while (1)
    {
        msgrcv(codaFP_ds,&messaggioFP,sizeof(msg_FP),0,0);
        if (messaggioFP.finito==FINITO)
        {
            figliFiniti++;
            if (figliFiniti==numFile)
            {
                break;
            }
            else
            {
                continue;
            }
        }
        else
        {
            printf("%s@%s:%d:%s", messaggioFP.parolaTrovata , argv[messaggioFP.tipo + numParole +1] , messaggioFP.numRiga , messaggioFP.riga );
            arrayOccorrenze[messaggioFP.tipo - 1]++; //controllare se è giusto quel -1, in teoria comunque i figli hanno id da 1 a N
        }
    }

    //Sono finit tutti i file
    //visualizziamo le occ. totali
    printf("\nSTAMPA OCCORRENZE TOTALI\n");
    for ( i = 0; i < numFile; i++)
    {
        printf("%s-%d:%d\n", argv[i + 1 + numParole + 1] , i+1 , arrayOccorrenze[i]);
    }
    msgctl(codaFP_ds,IPC_RMID, NULL);
    msgctl(codaPF_ds,IPC_RMID, NULL);
}



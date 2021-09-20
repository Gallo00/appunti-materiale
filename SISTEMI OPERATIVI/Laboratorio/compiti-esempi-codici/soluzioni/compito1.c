#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>

//struttura messaggio

#define TEXT_DIM 900
#define BUFSIZE 4096
#define DEST_PADRE 1000

typedef enum{
    CMD_LIST,
    CMD_SIZE,
    CMD_SEARCH,
    CMD_EXIT,
    REPLY_ERROR,
    REPLY_DATA,
    REPLY_DATA_STOP
}type_payload;

typedef struct
{
    long type;
    type_payload payload;
    char text[TEXT_DIM];
    long numero;
}msg;


//COSTRUIRE FUNZIONE FIGLIO
void figlio(int numfiglio,char* dir,int coda)
{
    msg messaggio;
    struct dirent * entry;
    DIR* dp;
    struct stat statbuf;
    FILE* file;
    char buffer[BUFSIZE];
    bool finito=false;
    if (chdir(dir)==-1)
    {
        perror("chdir");
        exit(1);
    }

    do
    {
        //riceve il messaggio(si mette in attesa) che contiene il tipo di comando
        if ((msgrcv(coda,&messaggio, sizeof(msg) - sizeof(long),numfiglio,0))==-1)
        {
            perror("msgrcv");
            exit(1);
        }

        switch (messaggio.payload)
        {
        case CMD_LIST:
            //visualizzare(mandare) lista dei nomi dei file regolari dentro questa cartella
            dp=opendir("."); //. perchè con chdir siamo già qui
            messaggio.type=DEST_PADRE; //mess da inviare al padre
            while ((entry=readdir(dp))!=NULL)
            {
                lstat(entry->d_name, &statbuf);
                if (S_ISREG(statbuf.st_mode))
                {
                    //dentro entry ci sarà d_name da inviare al padre
                    messaggio.payload=REPLY_DATA;
                    strncpy(messaggio.text,entry->d_name,TEXT_DIM);
                    msgsnd(coda,&messaggio,sizeof(msg) - sizeof(long),0);
                }
            }
              //segnaliamo al padre che abbiamo finito i messaggi con un reply data stop
            messaggio.payload=REPLY_DATA_STOP;
            msgsnd(coda,&messaggio,sizeof(msg) - sizeof(long),0);
            closedir(dp);
            break;

        case CMD_SIZE:
            messaggio.type = DEST_PADRE;
            if (lstat(messaggio.text,&statbuf)==-1)
            {
                printf("%s \n",messaggio.text);
                messaggio.payload=REPLY_ERROR;
                msgsnd(coda,&messaggio,sizeof(msg) - sizeof(long),0);
                break;
            }

            if (!S_ISREG(statbuf.st_mode))
            {
                printf("file non regolare \n");
                messaggio.payload=REPLY_ERROR;
                msgsnd(coda,&messaggio,sizeof(msg) - sizeof(long),0);
                break;
            }
            
            
            messaggio.payload=REPLY_DATA;
            messaggio.numero=statbuf.st_size;
            msgsnd(coda,&messaggio,sizeof(msg) - sizeof(long),0);
            break;

        case CMD_SEARCH:
            //arrivano 2 messaggi, nome file e stringa
            if ( (lstat(messaggio.text,&statbuf)==-1) || (!S_ISREG(statbuf.st_mode)) || ((file=fopen(messaggio.text,"r"))==NULL))
            {
                messaggio.numero=DEST_PADRE;
                messaggio.payload=REPLY_ERROR;
                msgsnd(coda,&messaggio,sizeof(msg) - sizeof(long),0);
                msgrcv(coda,&messaggio, sizeof(msg) - sizeof(long),numfiglio,0);
                break;
            }
            
            msgrcv(coda,&messaggio, sizeof(msg) - sizeof(long),numfiglio,0); //lettura stringa-key

            int occorrenze=0;
            while (fgets(buffer,BUFSIZE,file))
            {
                if (strstr(buffer,messaggio.text))
                {
                    occorrenze++;
                }
                
            }
            
            //preparare il messaggio
            messaggio.type=DEST_PADRE;
            messaggio.numero=occorrenze;
            messaggio.payload=REPLY_DATA;

            msgsnd(coda,&messaggio,sizeof(msg) - sizeof(long),0);
            break;

        case CMD_EXIT:
            finito=true;
            break;
        }
        
    } while (!finito);
    
    //il figlio sta per morire, lo terminiamo altrimenti continua a svolgere istruzioni nel main che spettano solo al padre
    exit(1);
}



int main(int argc,char* argv[])
{
    //padre
    char buffer[BUFSIZE];
    msg messaggio;
    struct stat statbuf;
    int figli=0;

    if (argc<=1)
    {
        perror("errore nei parametri");
        exit(1);
    }

    //creo coda
    int coda;
    if ((coda=msgget(IPC_PRIVATE, IPC_CREAT | 0600))==-1)
    {
        perror("msgget");
        exit(1);
    }
    
    
    //crare processo dedicato a ogni cartella 

    
    for (int i = 1; i < argc; i++)
    {
        //controlliamo se è effettivamente una cartella
        if (((stat(argv[i], &statbuf))==-1) || (!S_ISDIR(statbuf.st_mode)))
        {
            perror(argv[i]); //problema con questo parametro, lo ignoro
            continue;
        }
        
        figli++;
        if(fork()==0)
        {
            figlio(i,argv[i],coda);
        }
        
    }
    
    if (figli==0)
    {
        //figli insufficienti, esco
        printf("qui\n");
        exit(1);
    }
    
    
    //adesso inizia il vero e proprio processo padre, meglio una sleep prima di farlo cominciare
    sleep(1);
    bool finito=false;
    do
    {
        //codice padre
        printf("file-shell>");
        fgets(buffer,BUFSIZE,stdin);  //se scrivi ciao --> ciao\n , convertiamo in ciao\0 per renderla una stringa in C
        int len=strlen(buffer);
        if (buffer[len-1]=='\n')
        {
            buffer[len-1]='\0';
        }
        

        //estrapolare il comando inviato su shell
        //usiamo strtoken
        char* token;
        if (token=strtok(buffer," "))
        {
            /* estratto primo token ovvero il comando */
            //andiamo per 5 casi, list, size, search, exit e comando non valido
            if (strcmp(token,"list")==0)
            {
                /* va estratto il secondo token */
                if (token=strtok(NULL," "))
                {
                    /* estratto il numero del figlio a cui inviare LIST */
                    int numfiglio=atoi(token);
                    if (numfiglio>=1 && numfiglio <=figli)
                    {
                        /* figlio valido */
                        //deve inviare un CMD LIST al figlio numfiglio
                        messaggio.type=numfiglio;
                        messaggio.payload=CMD_LIST;
                        msgsnd(coda,&messaggio,sizeof(msg) - sizeof(long),0);

                        while (1)
                        {
                            msgrcv(coda,&messaggio, sizeof(msg) - sizeof(long), DEST_PADRE,0);
                            //il ciclo finisce se riceve un REPLY ERROR o un REPLY DATA STOP
                            if (messaggio.payload== REPLY_ERROR)
                            {
                                printf("errore dal figlio \n");
                                break;
                            }
                            if (messaggio.payload== REPLY_DATA_STOP)
                            {
                                //fine messaggi
                                break;
                            }
                            printf("%s\n" ,messaggio.text );
                            
                        }
                        
                    }
                    
                }
            }
            else if (strcmp(token,"size")==0)
            {
                /* va estratto il secondo token */
                if (token=strtok(NULL," "))
                {
                    /* estratto il numero del figlio a cui inviare SIZE*/
                    int numfiglio=atoi(token);
                    if (numfiglio>=1 && numfiglio <=figli)
                    {
                        /* figlio valido */
                        //deve inviare un CMD SIZE al figlio numfiglio
                        if (token=strtok(NULL," "))
                        {
                            //estratto il terzo token ovvero il nome del file di cui vogliamo size
                            messaggio.type=numfiglio;
                            messaggio.payload=CMD_SIZE;

                            //preparazione messaggio.text
                            strncpy(messaggio.text,token,TEXT_DIM);
                            /*
                            strncpy(messaggio.text,"./",TEXT_DIM);
                            strcat(messaggio.text,token);
                            strcat(messaggio.text,"\0");
                            */

                            //printf(messaggio.text);

                            msgsnd(coda,&messaggio,sizeof(msg) - sizeof(long),0);

                            //non serve ricevere tanti messaggi
                            msgrcv(coda, &messaggio, sizeof(msg) - sizeof(long), DEST_PADRE, 0);
                            if (messaggio.payload==REPLY_ERROR)
                            {
                                printf("errore dal figlio \n");
                            }
                            else
                            {
                                printf("size: %ld\n" , messaggio.numero);
                            }
                            

                        }
                        
                    }
                    
                }

            }
            else if (strcmp(token,"search")==0)
            {
                /* va estratto il secondo token */
                if (token=strtok(NULL," "))
                {
                    /* estratto il numero del figlio a cui inviare Search*/
                    int numfiglio=atoi(token);
                    if (numfiglio>=1 && numfiglio <=figli)
                    {
                        /* figlio valido */
                        //deve inviare un CMD SEARCH al figlio numfiglio
                        if (token=strtok(NULL," "))
                        {
                            //estratto il terzo token ovvero il nome del file
                            messaggio.type=numfiglio;
                            messaggio.payload=CMD_SEARCH;
                            strncpy(messaggio.text,token,TEXT_DIM);
                            // msgsnd(coda,&messaggio,sizeof(msg) - sizeof(long),0);
                            //Così abbiamo inviato il nome del file, ora estraiamo il quarto token ovvero la stringa e inviamola
                            if (token=strtok(NULL, " "))
                            {
                                msgsnd(coda,&messaggio,sizeof(msg) - sizeof(long),0);
                                //Adesso inviare la stringa
                                messaggio.type=numfiglio;
                                messaggio.payload=CMD_SEARCH;
                                strncpy(messaggio.text,token,TEXT_DIM);
                                msgsnd(coda,&messaggio,sizeof(msg) - sizeof(long),0);

                                //adesso aspettiamo la risposta
                                msgrcv(coda, &messaggio, sizeof(msg) - sizeof(long), DEST_PADRE, 0);
                                if (messaggio.payload==REPLY_ERROR)
                                {
                                    printf("errore dal figlio \n");
                                }
                                else
                                {
                                    printf("occorrenze: %ld\n" , messaggio.numero);
                                }
                            }
                            
                        }
                        
                    }
                    
                }
            }
            else if (strcmp(token,"exit")==0)
            {
                finito=true;
            }
            else
            {
                printf("comando inserito non valido \n");
            }
        }
    } while (!finito);
 
    for (int i = 1; i <= figli; i++)
    {
        //inviare CMD_EXIT a ognuno dei figli 
        messaggio.payload=CMD_EXIT;
        messaggio.type=i;

        if ((msgsnd(coda,&messaggio,sizeof(msg) - sizeof(long),0))==-1)
        {
            printf("msgsnd \n");
        }
    }

    for (int i = 1; i <= figli; i++)
        wait(NULL);

    msgctl(coda,IPC_RMID,NULL);
}
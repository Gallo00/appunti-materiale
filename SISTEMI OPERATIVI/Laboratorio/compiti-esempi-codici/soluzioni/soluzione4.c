/*
    Homework n.4

    Estendere l'esercizio 'homework n.1' affinche' operi correttamente
    anche nel caso in cui tra le sorgenti e' indicata una directory, copiandone
    il contenuto ricorsivamente. Eventuali link simbolici incontrati dovranno
    essere replicati come tali (dovrà essere creato un link e si dovranno
    preservare tutti permessi di accesso originali dei file e directory).

    Una ipotetica invocazione potrebbe essere la seguente:
     $ homework-4 directory-di-esempio file-semplice.txt path/altra-dir/ "nome con spazi.pdf" directory-destinazione
*/

/*
    Homework n.1

    Scrivere un programma in linguaggio C che permetta di copiare un numero
    arbitrario di file regolari su una directory di destinazione preesistente.

    Il programma dovra' accettare una sintassi del tipo:
     $ homework-1 file1.txt path/file2.txt "nome con spazi.pdf" directory-destinazione
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <libgen.h>
#include <dirent.h>
#include <errno.h>

#define BUFSIZE 2048

// for che scansiona fino a argc-1 -> preso il pathname prenderne le info ->
// se è link copiarlo così com'è, se è file reg fare copia incolla tramite fd, open, read e write col loop
// se è dir prima con mkdir ne creiamo una(quella dest) poi la apriamo e inizia un ciclo per scansionare elementi della cartella
//si fa con readdir, si fa ricorsione, dopo il ciclo chiudere cartella

void copiaElementi(char* pathname, char* dest, int depth)
{
    //preparare in un buffer(nomeFileDest) il nome del file di destinazione(deve stare dentro dest)
    char nomeFileDest[BUFSIZE];
    strncpy(nomeFileDest,dest,BUFSIZE);
    strncat(nomeFileDest,"/",BUFSIZE - strlen(nomeFileDest));
    //abbiamo fatto path/ ci manca il nome che è basename(pathname) però sfruttiamo un buffer ausiliario
    //poichè basename potrebbe avere come effetto collaterale di modificare la variabile
    char bufferAux[BUFSIZE];
    strncpy(bufferAux,basename(pathname),BUFSIZE);
    strncat(nomeFileDest,bufferAux,BUFSIZE - strlen(nomeFileDest));


    //raccogliamo le informazioni sul file/cartella
    struct stat statbuf;
    if (lstat(pathname, &statbuf)==-1)
    {
        perror(pathname);
        exit(1);
    }

    //si apre il ramo condizionale
    switch (statbuf.st_mode & S_IFMT)
    {
        case S_IFLNK:
        {
            //è un link simbolico, copiamolo così com'è
            int size;
            strncpy(bufferAux,"\0",BUFSIZE);
            if ((size=readlink(pathname,bufferAux,BUFSIZE ))==-1)
            {
                perror(pathname);
                exit(1);
            }
            bufferAux[size]='\0';
            printf("%*s%s (l)--> %s [=> %s]\n", depth, "  ", pathname, nomeFileDest, bufferAux);

            if (symlink(bufferAux, nomeFileDest)==-1)
            {
                perror(nomeFileDest);
                exit(1);
            }
            
            break;
        }
        case S_IFREG:
        {
            //è file regolare, facciamo classico copia e incolla
            printf("%*s%s (f)--> %s\n", depth, "  ", pathname, nomeFileDest);
            int src_fd;
            int dst_fd;

            if ((src_fd=open(pathname,O_RDONLY))==-1)
            {
                perror(pathname);
                exit(1);
            }

            if ((dst_fd=open(nomeFileDest, O_RDWR|O_TRUNC|O_CREAT,(statbuf.st_mode & 0777)))==-1)
            {
                perror(nomeFileDest);
                exit(1);
            }

            //copia e incolla col ciclo
            int size=BUFSIZE;
            while(size!=0)
            {
                strncpy(bufferAux,"\0",BUFSIZE);
                if ((size=read(src_fd,bufferAux,BUFSIZE))==-1)
                {
                    perror("read nel while");
                    exit(1);
                }

                if ((write(dst_fd,bufferAux,size))==-1)
                {
                    perror("write nel while");
                    exit(1);
                }
            }

            close(src_fd);
            close(dst_fd);
            break;
        }

        case S_IFDIR:
        {
            printf("%*s%s/ (d)--> %s/\n", depth, "  ", pathname, nomeFileDest);

            if ((mkdir(nomeFileDest,statbuf.st_mode & 0777))==-1)
            {
                printf("1\n");
                perror(nomeFileDest);
                exit(1);
            }
            DIR * directory;
            if ((directory=opendir(pathname))==NULL)
            {
                perror(pathname);
                if (errno != EEXIST) exit(1);
            }
            
            struct dirent* entry;
            
            while ((entry=readdir(directory))!=NULL)
            {
                strncpy(bufferAux,"\0",BUFSIZE);
                if (strcmp(entry->d_name,".")==0 || strcmp(entry->d_name,"..")==0)
                {
                    continue;
                }
                
                //dentro bufferAux mettiamo il percorso che dovrebbe essere pathname/entry->d_name
                strncpy(bufferAux,pathname,BUFSIZE);
                strncat(bufferAux,"/",BUFSIZE - strlen(bufferAux));
                strncat(bufferAux,entry->d_name,BUFSIZE - strlen(bufferAux));

                copiaElementi(bufferAux,nomeFileDest,depth+1);
            }

            closedir(directory);
            break;
        }
        default:
        {
            printf("oggetto non compatibile\n");
            exit(1);
            break;
        }
    }
    


}

int main(int argc,char* argv[])
{
    for(int i=1; i< argc-1 ; i++)
    {
        copiaElementi(argv[i],argv[argc-1], 0);
    }
}
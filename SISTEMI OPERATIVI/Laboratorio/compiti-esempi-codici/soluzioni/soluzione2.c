/*
    Homework n.2

    Estendere l'esempio 'move.c' visto a lezione per supportare i 2 casi speciali:
    - spostamento cross-filesystem: individuato tale caso, il file deve essere
      spostato utilizzando la strategia "copia & cancella";
    - spostamento di un link simbolico: individuato tale caso, il link simbolico
      deve essere ricreato a destinazione con lo stesso contenuto (ovvero il percorso
      che denota l'oggetto referenziato); notate come tale spostamento potrebbe
      rendere il nuovo link simbolico non effettivamente valido.

    La sintassi da supportare e' la seguente:
     $ homework-2 <pathname sorgente> <pathname destinazione>
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <libgen.h>
#include <unistd.h>

#define BUFSIZE 2048

int main(int argc, char* argv[])
{
    struct stat statbuf, dst_statbuf;
    int src_d, dst_d, size;
    char buffer[BUFSIZE];
    char *dst_dir;


    if(argc!=3)
    {
        perror("metti file sorgente e file destinazione\n");
        exit(1);
    }

    if(lstat(argv[1],&statbuf)==-1)
    {
        printf("1\n");
        perror(argv[1]);
        exit(1);
    }

    switch (statbuf.st_mode & S_IFMT)
    {
    case S_IFLNK:
        if((size=readlink(argv[1],buffer,BUFSIZE))==-1)
        {
            printf("2\n");
            perror(argv[1]);
            exit(1);
        }
        buffer[size]='\0';

        if ((symlink(buffer,argv[2]))==-1)
        {
            printf("3\n");
            perror(argv[2]);
            exit(1);
        }
        break;

    case S_IFREG:
        strncpy(buffer,argv[2],BUFSIZE);
        dst_dir=dirname(buffer);

        if((stat(dst_dir,&dst_statbuf))==-1)
        {
            printf("4\n");
            perror(dst_dir);
            exit(1);
        }

        //CONTROLLIAMO SE E' UNA DIRECTORY
        if (!S_ISDIR(dst_statbuf.st_mode))
        {
            perror("NON E' UNA CARTELLA");
            exit(1);
        }

        // 2 vie: stesso FL o meno

        if (dst_statbuf.st_dev==statbuf.st_dev)
        {
            //stesso file system, creo hardlink
            if(link(argv[1],argv[2])==-1)
            {
                printf("5\n");
                perror(argv[2]);
                exit(1);
            }
        }
        else
        {
            //diversi FS, facciamo copia e incolla(e cancella il src)
            if((src_d=open(argv[1],O_RDONLY))==-1)
            {
                printf("6\n");
                perror(argv[1]);
                exit(1);
            }
            if((dst_d=open(argv[2],O_RDWR|O_TRUNC|O_CREAT, (statbuf.st_mode & 0777) ))==-1)
            {
                 printf("7\n");
                perror(argv[1]);
                exit(1);
            }

            size=1;
            char buffer_copia[BUFSIZE];
            while(size!=0)
            {
                //leggere
                if((size=read(src_d,buffer_copia,BUFSIZE))==-1)
                {
                    char* str;
                    sprintf(str, "%d", src_d);
                    perror(str);
                    exit(1);
                }

                //scrivere
                if((write(dst_d,buffer_copia,size))==-1)
                {
                    char* str;
                    sprintf(str, "%d", dst_d);
                    perror(str);
                    exit(1);
                }
            }
            close(src_d);
            close(dst_d);
        }

        
        break;
    default:
        fprintf(stderr, "tipo di oggetto non supportato!\n");
        exit(1);
        break;
    }

    //cancelliamo il src
    if(unlink(argv[1])==-1)
    {
        perror(argv[1]);
        exit(1);
    }

}
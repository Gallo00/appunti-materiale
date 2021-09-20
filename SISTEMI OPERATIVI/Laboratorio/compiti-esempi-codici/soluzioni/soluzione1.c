
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
#include <unistd.h>
#include <libgen.h>


#define BUFSIZE 4096
#define MODE 0660


int main(int argc,char* argv[])
{
    int size_letta;
    if(argc<3)
    {
        perror("devi usare almeno 2 parametri cioò file e poi directory");
        exit(1);
    }

    char buffer_lettura[BUFSIZE];
    char destinazione[BUFSIZE];

    for(int i=1; i<argc-1;i++)
    {
        //reset buffer_lettura
        strncpy(buffer_lettura,"\0",BUFSIZE);
        strncpy(destinazione,"\0",BUFSIZE);

        //aprire file di turno
        printf("file %d %s \n" , i , argv[i]);
        int file_descriptor;
        if((file_descriptor=open(argv[i],O_RDONLY))==-1)
        {
            perror(argv[i]);
            exit(1);
        }

        /* prepara il percorso destinazione  ovvero directory-destinazione/nome_file */
        strncpy(destinazione,argv[argc-1],BUFSIZE);
        strcat(destinazione ,"/");
        strcat(destinazione,basename(argv[i]));
        
        printf("buffer: %s\n",destinazione);
        int file_descriptor_dest;
        if((file_descriptor_dest=open(destinazione, O_WRONLY|O_TRUNC|O_CREAT,0600))==-1)
        {
            perror(argv[i]);
            exit(1);
        }
        size_letta=1;
        while(size_letta!=0)
        {
            
            if((size_letta=read(file_descriptor,buffer_lettura,BUFSIZE))==-1)
            {
                perror(argv[i]);
                exit(1);
            }
           
            if((write(file_descriptor_dest,buffer_lettura,size_letta))==-1)
            {
                perror(argv[i]);
                exit(1);
            }
            
        }
        
        close(file_descriptor);
        close(file_descriptor_dest);
    }


}
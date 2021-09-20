/*
    Homework n.3

    Usando la possibilita' di mappare file in memoria, creare un programma che
    possa manipolare un file arbitrariamente grande costituito da una sequenza
    di record lunghi N byte.
    La manipolazione consiste nel riordinare, tramite un algoritmo di ordinamento
    a scelta, i record considerando il contenuto dello stesso come chiave:
    ovvero, supponendo N=5, il record [4a a4 91 f0 01] precede [4a ff 10 01 a3].
    La sintassi da supportare e' la seguente:
     $ homework-3 <N> <pathname del file>

    E' possibile testare il programma sul file 'esempio.txt' prodotto dal seguente
    comando, utilizzando il parametro N=33:
     $ ( for I in `seq 1000`; do echo $I | md5sum | cut -d' ' -f1 ; done ) > esempio.txt

    Su tale file, l'output atteso e' il seguente:
     $ homework-3 33 esempio.txt
     $ head -n5 esempio.txt
        000b64c5d808b7ae98718d6a191325b7
        0116a06b764c420b8464f2068f2441c8
        015b269d0f41db606bd2c724fb66545a
        01b2f7c1a89cfe5fe8c89fa0771f0fde
        01cdb6561bfb2fa34e4f870c90589125

     $ tail -n5 esempio.txt
        ff7345a22bc3605271ba122677d31cae
        ff7f2c85af133d62c53b36a83edf0fd5
        ffbee273c7bb76bb2d279aa9f36a43c5
        ffbfc1313c9c855a32f98d7c4374aabd
        ffd7e3b3836978b43da5378055843c67
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 2048

void scambia(char* x , char* y,int size)
{
    char swapbuffer[size];
    memcpy(swapbuffer,x,size);
    memcpy(x,y,size);
    memcpy(y,swapbuffer,size);
}

void bubblesort(char* map, int records ,int size)
{
    int i, j;
    for(i = 0; i < records - 1; i++)  
    {
        for (j = 0; j < records -1; j++) 
        {
            if (memcmp(map + size*j, map+ size*(j+1),size)>0) 
            {
                scambia(map + size*j,map + size*(j+1),size);
            }
        }
    }
}


int main(int argc,char* argv[])
{
    if(argc!=3)
    {
        perror("2 parametri servono");
        exit(1);
    }

    //aprire il file -> controllo se è file regolare -> controllo su N
    // ->mappare il file aperto ->riordinamento ->chiudere e dismappare

    int src_fd;
    if ((src_fd=open(argv[2],O_RDWR))==-1)
    {
        perror(argv[1]);
        exit(1);
    }
    struct stat buf;
    if (fstat(src_fd,&buf)==-1)
    {
        perror(argv[2]);
        exit(1);
    }

    //è regolare?
    if(!S_ISREG(buf.st_mode))
    {
        fprintf(stderr, "%s non è un file\n", argv[1]);
        exit(1);
    }

    //controllo su N
    int size=atoi(argv[1]);
    if (size<=0 || (buf.st_size % size)!=0)
    {
        perror("N non valido o dim non congruente");
        exit(1);
    }

    char* map;
    if ((map=mmap(NULL,buf.st_size, PROT_READ | PROT_WRITE,MAP_SHARED, src_fd, 0))==MAP_FAILED)
    {
        perror(map);
        exit(1);
    }

    //mappatura del file fatto, dobbiamo ora ordinare 

    int records=buf.st_size/size;
    bubblesort(map,records,size);

    if (close(src_fd)==-1)
    {
        perror("close");
        exit(1);
    }

    if (munmap(map,buf.st_size))
    {
        perror("munmap");
        exit(1);
    }
    
}

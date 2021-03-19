#include <iostream>
#include <stdlib.h>   // stdlib.h e time.h servono per la funzione rand
#include <time.h>
using namespace std;

int main()
{
	int somma=0;
	int A[5][10];
	int B[5];
	int i=0;
	int j=0;
	while(i<5)           //riempiamo la matrice in modo casuale
	{
		j=0;
		while(j<10)
		{
		A[i][j]=rand()%5;
	    j=j+1;
	}
	i=i+1;
}
	
i=0;
j=0;
    while(i<5)
    {
    	j=0;
    	somma=0;
    	while(j<10)
    	{
    		somma=somma+A[i][j];
    		j=j+1;	
		}
		B[i]=somma;
		cout <<B[i] <<endl;
		i=i+1;
	}
	for(int R=0;R<5;R++)             //stampare in maniera grafica la matrice
	{
		for(int c=0;c<10;c++)
		{
			cout<<A[R][c]<<"  ";
		}
		cout<< endl;
	}
	
	
	return 0;
	
	
}

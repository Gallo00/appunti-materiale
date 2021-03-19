#include <iostream>
#include <stdlib.h>   // stdlib.h e time.h servono per la funzione rand
#include <time.h>
using namespace std;

int main()
{
	int A[30];
	int i=0;
	while(i<30)           //riempiamo l'array in modo casuale
	{
		A[i]=rand()%5;
		i=i+1;
	}
	
	
	i=0;
	int x=0;
	int y=0;
	int z=0;
	while(i<30)     //somma degli elementi con indice pari
	{
	 x=x+A[i];
	 i=i+2;			
	}
	cout<<x <<endl;
	i=1;
	while(i<30)      //somma degli elementi con indici dispari
	 {
		y=y+A[i];
		i=i+2;
		
	 }
	 cout<<y <<endl;
	 i=0;
	 while(i<30)     //somma di tutti gli elementi
	 {
	 	z=z+A[i];
	 	i=i+1;
	 	
	 	
	 }
	 cout<<z <<endl;
	 
	if((x+y)==z)                              //controllo delle somme
	{
		cout<<"esercizio fatto correttamente";
	}
	
	
	
	return 0;
}

#include <iostream>
#include <stdlib.h>   // stdlib.h e time.h servono per la funzione rand
#include <time.h>
using namespace std;

int main()
{
	int mat[3][3];
	int i=0;
	int j;
	srand(time(NULL));  //inizializza il seme,serve per avere numeri causali ogni volta che avvio il programma
while(i<3)
	{
	j=0;
	while(j<3)
	{
		mat[i][j]=rand()%10;
		j=j+1;
	}
/*	while(i<3)
	{
	j=0;
	while(j<3)
	{
		cout<<"inserisci il valore " <<endl;
		cin>>mat[i][j];
		j=j+1;
	}
	*/	
	i=i+1;	
	}
	for(int i=0;i<3;i++)             //stampare in maniera grafica la matrice
	{
	for( j=0;j<3;j++)
		{
			cout<<mat[i][j]<<"  ";
		}
		cout <<endl;
}
	
	
	int A[3];
	int B[3];
	int x;
	int y;

	int somma_righe;
	int somma_colonne;
	int somma_diagpr=0;
	int somma_diagse=0;
	i=0;
	cout<<endl;
	while(i<3)
	{
	j=0;
	somma_righe=0;
	
	while(j<3)
	{
		somma_righe=somma_righe+mat[i][j];
		j=j+1;
		
		}	
		A[i]=somma_righe;
		cout<<A[i]<<" ";
		i=i+1;
			
	}
	j=0;
	cout<<endl;
	cout<<endl;
	while(j<3)
	{
		i=0;
		somma_colonne=0;
		while(i<3)
		{
		
		somma_colonne=somma_colonne+mat[i][j];
		i=i+1;
	}
	B[j]=somma_colonne;
	cout<<B[j] <<endl;
	j=j+1;
		
	}
	i=0;
	j=0;
	cout<<endl;
	while(i<3)
	{
		somma_diagpr=somma_diagpr+mat[i][j];
		i=i+1;
		j=j+1;
	}
	x=somma_diagpr;
	i=0;
	j=2;
	while(i<3)
	{
	somma_diagse=somma_diagse+mat[i][j];
	i=i+1;
	j=j-1;
	
	}
	y=somma_diagse;
	cout<<x <<endl;
	cout<<y <<endl;

	return 0;
}

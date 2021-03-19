/* 
Corso di Programmazione II (A-L), Prof. Dario Catalano 

Esercizi su ordinamento e ricerca

Esercizio 5: Merge Sort.
*/
#include<iostream>
using namespace std;
#define DIM 20 
 
 
void merge(int a[], int left, int center, int right)
{
	int i=left, j=center+1, k=left; 
	int b[DIM];
	
	while((i<=center) && (j<=right)) 
	{
		if (a[i] <= a[j])
		{
			b[k]=a[i];             // in questo WHILE le celle di b assumeranno valore delle celle del sotto_array di sinistra o destra 
			i++;                   // a seconda che l'elemento del primo sia più piccolo o maggiore/uguale dell'elemento del secondo
		}                          // Uno dei due sottoarray verrà a completarsi per primo e come conseguenza il secondo verrà 
		                           // completato da un successivo WHILE
		else
		{
			b[k]=a[j]; 
			j++;
		}
		k++;
	}
	
	
    while(i<=center)  //completamento nel caso il sotto_array di sinistra non sia stato "completato"
	{
		b[k]=a[i]; 
		i++;
		k++;
	}
	
	
    while(j<=right)    //completamento nel caso il sotto_array di destra non sia stato "completato"
	{
		b[k]=a[j]; 
		j++;
		k++;
	}
	
	
    for(k=left;k<=right;k++)   //viene riordinato l'array(usando le celle ordinate di b
    	a[k]=b[k];
}
    
void mergesort(int a[], int left, int right)
{
	if (left< right) 
	{
		int center=(left+right)/2;
		mergesort(a,left,center);
		mergesort(a,center+1,right);
		merge(a,left,center,right); 
	}
} 
    
//Ordiniamo in senso non decrescente 

void Stampa (int a[], int n) 
{
	for (int i=0; i<n;i++) 	
		cout << a[i] << " ";
	cout << endl;  
}

int main()
{
int vettore[DIM]={12,3,6,5,131,7,43,89,54,34,11,21,13,4,90,15,16,71,19,31};

int i; 
cout << "Vettore iniziale \n"; 
Stampa(vettore,DIM);
mergesort(vettore,0,DIM-1); 
cout << endl << "Vettore ordinato " << endl; 
Stampa(vettore,DIM); 
}
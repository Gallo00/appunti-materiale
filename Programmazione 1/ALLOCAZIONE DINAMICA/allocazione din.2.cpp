#include <iostream>
using namespace std;

int *funzione(int lunghezza)                     //int * segnala che la funzione ritornerà un PUNTATORE A INTERI
{
	
	int *arr=new int[lunghezza];       //creiamo un arra e lo allochiamo in maniera dinamica
	int i=0;
	while(i<lunghezza)
	{
	   arr[i]=i*2;
	   cout<<arr[i]<<" ";
	   i++;	
	}	
	
}


int main()
{
	int num;
	cout<<" inserisci lunghezza array"<<endl;
	cin>>num;
	int *array=funzione(num);                     //esegue le istruzioni di FUNZIONE(riga 4-riga16) usando però "num" come parametro
}

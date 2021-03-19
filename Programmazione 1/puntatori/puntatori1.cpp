#include <iostream>
using namespace std;

//PUNTATORI
int main()
{
	int numero=10;
	int *p;            //dichiaro un puntatore p,che punta a interi(char*p avrebbe puntato a caratteri)
	
	
	p=&numero;         //così p punterà alla casella contenente "numero"
	
	//posso modificare numero usando direttamente il puntatore
	
	*p=15;
	
	cout<<numero<<endl;
	
	//in questo momento numero è diventato 15 senza aver fatto operazioni direttamente su di lui
	
	//fare attenzione a quando si stampa *p o p poichè il primo indica il valore della cella,il secondo il suo indirizzo
	
	cout<<"valore="<<*p<<",indirizzo="<<p<<endl;
	
	
	//p è una variabile e potrebbe essere costante ma in questi esempi non lo è perciò il suo valore può cambiare


int num = 25;
int num2=100;
int *k;                     //   queste due righe possono essere compattate in    int*k=&num;
k=&num;                     //  
cout<< k << endl;                    //indirizzo
cout<< *k <<endl<<endl;             //valore puntato

*k=40;     //ho modificato nume
cout<<num<<endl;

//ora cambio la cella puntata da k
k=&num2;  //ora se stampo *k dovrebbe venire infatti 100(non abbiamo modificato il valore,abbiamo cambiato la cella puntata)

cout<<*k;
	
	
	
	
	
	
	
	
	
}

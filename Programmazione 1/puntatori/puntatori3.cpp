#include <iostream>
using namespace std;

int main()
{
	int num=5;
	const int *p=&num;
	cout<<*p<<endl;
    //*p=10;  questa cosa non si può fare,abbiamo un puntatore a costante,esso tratta num come costante quindi non possiamo modificarne 
    //           il valore tramite *p
	
	num=10;
	cout<<*p<<endl;   //tramite num possiamo modificare il valore e verrà aggiornato ovviamente *p dato che corrispondono.
	
	//possiamo anche cambiare l'indirizzo per fare un "aggiornamento"
	int num2=30;
	p=&num2;
	cout<<*p<<endl;
	
	
	int d=50;
	int *const  ptr_d=&d;        //abbiamo creato un puntatore costante
	
	//in questo caso posso aggiornare il valore tramite *ptr_d
	*ptr_d=60;
	cout<<*ptr_d<<endl;
	
	//non potrò invece cambiare l'indirizzo di ptr_d
	//int i=20;
	//ptr_d=&i;            //se si prova ad eseguire queste due righe per un puntatore costante ci sarà errore di compilazione
	
	
	
	//si può  creare una ibrida tra puntatore a costante e puntatore costante,ovvero
	// creeremo un "puntatore costante a costante"
	
	int u=25;
	const int * const o=&u;
	
//	*o=20;
//	int k=40;             //queste operazioni non sono possibili per gli stessi motivi per cui non abbiamo potuto prima.
//	o=&k;
	
	
	
	
}

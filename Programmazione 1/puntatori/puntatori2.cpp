#include <iostream>

using namespace std;   

//puntatori

int main()
{
	
	
	//quando dichiariamo un array,stiamo implicitamente dichiarando un puntatore alla sua prima casella
	
	int v[]={2,5,8,1,5};
	
	//infatti facendo cout<<v uscirà un indirizzo, facendo cout<<*v verrà 2
	
	cout<<"indirizzo="<<v<<", valore="<<*v<<endl;
	
	//per stampare gli altri valori posso fare la seguente         //
	cout<<v[1]<<endl;                                              //
	cout<<v[2]<<endl;                                              //
	                                                               //         v[2],*(ptr+2),*(v+2),ptr[2] esprimono la stessa cosa.
	//oppure posso fare così                                       //
	int *ptr=v;                                                    //
	cout<<*(ptr+1)<<endl;                                          //
	cout<<*(ptr+2)<<endl;                                          //
	                                                               //
	//oppure                                                       //
	cout<<*(v+1)<<endl<<endl<<endl<<endl;                                           
	
	cout<<"               -----------------------------------------------"<<endl;
	
	
	//operazioni sui puntatori                 //qua necessario usare un puntatore ausiliario(ptr2)
	int u[]={2,4,6,8,10};
	int *ptr2=u;
	cout<<*(++ptr2)<<endl;                      //preincremento;prima incrementiamo ptr2 di 1 e poi stampiamo la casella a cui fa riferimento
	cout<<*(--ptr2)<<endl;
	cout<<*(ptr2++)<<endl; 
	cout<<*ptr2<<endl;
	cout<<*(ptr2--)<<endl;
	cout<<*ptr2<<endl;
	
	
	cout<<"     ----------------------------------------------------------------"<<endl;
	
	//possiamo anche effettuare dei controlli sui puntatori,per controllare se due puntatori puntano una casella con medesimo indirizzo
	// o per vedere se due puntatori che puntano due caselle distinte puntano lo stesso VALORE(non stessa casella)
	
	int x=50;
	int y=50;
	int *ptr_a=&x;              //ricordarsi & quando inizializzo un puntatore
	int *ptr_b=&y;
	
	cout<<"indirizzo a="<<ptr_a<<",indirizzo b="<<ptr_b<<endl;
	//verranno stampati 2 indirizzi diversi,nonostante puntino a 2 valori uguali
	
	
	if(ptr_a==ptr_b)
	{
		cout<<"indirizzi uguali";               //if che controlla due indirizzi
		
	}
	
	
	//if che controlla 2 valori puntati da puntatori diversi
	if(*ptr_a==*ptr_b)
	{
		cout<<"i due valori puntati da ptr_a e ptr_b sono uguali ed essi sono "<<*ptr_a;
	}
	
	//esiste anche il puntatore nullo
	//int *ptr_null=NULL                 //oppure int *ptr_null=nullptr;
	
	
	
	
	//*(v+1)+j=&v[i][j]        forme equivalenti
	
	//v[i][j]=*(*(v+1)+j)      forme equivalenti
	//_______=*(v[i]+j)
	
	
	
	
	
}

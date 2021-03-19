#include <iostream>
using namespace std;


//implementare una coda tramite array

const int Max=15;

class Coda{
	
	private:
	    int vettore[Max];
		int testa;
		int fine;
		
	public:
        Coda();
		void enqueue(int dato_nuovo); //inserimento nuovo elemento
		int dequeue();  //estrazione elemento
		int dato_testa(); //simile a dequeue, però non modifica la struttura
		
		bool coda_piena();  
		bool coda_vuota();
		
		void stampa();
	
};


Coda::Coda()
{
	testa=-1;
	fine=-1;
}

void Coda::enqueue(int dato_nuovo)
{
	if(coda_piena())
	{
		cout<<"coda piena"<<endl;
	}
	else
	{
		fine=(fine+1)% Max;  //è un array "circolare", devo perciò sfruttare l'aritmetica modulare
		vettore[fine]=dato_nuovo;
		
		if(testa=-1) testa++;
	}
}

int Coda::dequeue()
{
	if(coda_vuota())
	{
		cout<<"coda vuota"<<endl;
		return -1; //errore
	}
	else
	{
		int x=vettore[testa];
		testa=(testa+1)% Max;
		
		//se per caso testa supera fine la coda è stata svuotata
		if((testa-1)% Max == fine)
		{
			testa=-1;   //forziamo la condizione di "coda vuota"
		    fine=-1;  
	    }
		
		return x;
	}
}

int Coda::dato_testa()
{
	if(coda_vuota())
	{
		cout<<"coda vuota"<<endl;
		return -1;  //errore
	}
	else
	{
		return vettore[testa];
	}
}

bool Coda::coda_vuota()
{
	if(testa==-1)
		return true;
	else
		return false;
}

bool Coda::coda_piena()
{
	if((fine+1)% Max == testa)
		return true;
	else 
		return false;
}

void Coda::stampa()
{
	if(coda_vuota())
	{
		cout<<"coda vuota"<<endl;
	}
	else
	{
	    int i=testa;
	    while(i!=fine)
	    {
		    cout<<vettore[i]<<" ";
	  	    i=(i+1)%Max;
	    }
	    cout<< vettore[i]<<endl;
    }
}

int main()
{
	Coda coda;
	
	int x=coda.dequeue(); 
	for (int i=0; i<Max; i++) 
		coda.enqueue((i+1)*10); 
	coda.stampa();
	coda.enqueue(4); 
	cout <<endl;
	for (int i=0; i<Max-1; i++) 
		x=coda.dequeue();  
	coda.stampa();
	cout<<endl;
	for (int i=0; i<Max-1; i++)
		coda.enqueue((i+1)*4);
	cout<<endl;	
	coda.stampa();
	return 0;	
	
}










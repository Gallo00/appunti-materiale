#include <iostream>
using namespace std;

//creare lista doppia circolare

struct Nodo
{
	int valore;
	Nodo* succ;
	Nodo* prec;
};

class ldc
{
	private:
	    Nodo* testa;
		
	public:
	    ldc()  {testa=NULL;} //inizializzazione della lista (vuota) con testa=NULL
		~ldc(); //distruzione lista
		
		void inserisci(int dato_nuovo); //immette un nuovo elemento (in questo es. lo mettiamo tra testa e il succ di testa)
		Nodo* ritorna_testa() { return testa;}
		
		void stampa();
};

ldc::~ldc()
{
	Nodo* iter;  //definiamo un iter che ci servirà per i nostri calcoli
	
	//caso 1 lista vuota(ovvero testa==NULL) si finisce la funzione subito
	/*caso 2 lista con almeno un elemento, si setta iter a succ di testa,definiamo una 
	  variabile temporanea Nodo* che deve essere uguale a succ di iter, si fa delete su iter
	  così deallochiamo quel nodo, poi iter diventa quella variabile temporanea, il tutto
	  ciò in un ciclo che va avanti finchè iter non è testa(ovvero ha finito il "giro") 
      Alla fine del ciclo si dealloca pure testa	  */
	  
	if(testa==NULL)
	{
		return;
	}
	else
	{
		iter=testa->succ;
		
		while(iter!=testa)
		{
			Nodo* temp=iter->succ;
			delete iter;
			iter=temp;
		}
		delete testa;
	}    		
}

void ldc::inserisci(int dato_nuovo)
{
	//caso 1 lista vuota(testa==NULL), il dato inserito diventa testa
	//caso 2 lista con almeno un elemento,esso viene messo dopo la testa(in questo particolare esercizio)
	
	Nodo* nuovo=new Nodo;
	nuovo->valore=dato_nuovo;
	
	if(testa==NULL)
	{
		nuovo->succ=nuovo;  /* nuovo diventa testa, deve puntare (sia in modo precedente che successivo) a se stesso */
		nuovo->prec=nuovo;
		testa=nuovo;
	}
	else
	{
		nuovo->succ=testa->succ;
		testa->succ=nuovo;
		nuovo->prec=testa;
		nuovo->succ->prec=nuovo;
	}
}

void ldc::stampa()
{
//	Nodo* iter;
	
	if(testa==NULL)
	{
		cout<<"lista vuot"<<endl;
	}
	else 
	{
		if(testa->succ==testa)
	    {
		    cout<<"unico elemento="<<testa->valore<<endl;
		}
		else
		{
			cout<<"più elementi"<<endl;
			Nodo* iter;
			iter=testa;
			
			do
			{
				cout<<iter->valore<<endl;
				iter=iter->succ;
			} while(iter!=testa);
		}
	}
			
}


int main()
{
	ldc lista;
	for(int i=15;i>0;i--) 
		lista.inserisci(i*10); 
	lista.stampa();
	
	Nodo* primo=lista.ritorna_testa();
	cout<<"la testa e' "<<(*primo).valore<<endl;
	return 0;
}
















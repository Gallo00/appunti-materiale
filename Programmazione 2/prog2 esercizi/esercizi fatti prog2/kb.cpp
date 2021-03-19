#include <iostream>
#include <fstream>
using namespace std;


template <class H> struct Nodo_lista
{
	H val;
	Nodo_lista<H>* succ;
};

template <class H> class Lista //lista ordinata con inserimento e canc
{
	public:
	
	    Nodo_lista<H>* testa;
		int elementi;  //variabile che tiene conto di quanti nodi ci sono
		
		Lista() {testa=NULL; elementi=0;}
		
		void insert(H x)
		{
			Nodo_lista<H>* nuovo=new Nodo_lista<H>;
			nuovo->val=x;
			
			if(testa==NULL) //lista vuota, x diventa testa
			{
				testa=nuovo;
				nuovo->succ=NULL;
			}
			else if(x <=testa->val) //la lista non è vuota ma x è minore di testa, x diventa testa e il suo succ è la vecchia testa
			{
				nuovo->succ=testa;
				testa=nuovo;
			}
			else //caso più generale
			{
				Nodo_lista<H>* iter=testa;
				while(iter->succ!=NULL && !(x>iter->val && x<=iter->succ->val)) //cerchiamo 2 nodi tra cui metterlo
					iter=iter->succ;
				
				if(iter->succ==NULL) //inserimento in coda, x è il maggiore di tutti
				{
					iter->succ=nuovo;
					nuovo->succ=NULL;
				}
				else //inserimento tra iter e iter->succ
				{
					nuovo->succ=iter->succ;
					iter->succ=nuovo;
				}
			}
			
			elementi++; //incremento elementi
		}
		
		void cancella(H x)  //verrà fatta solo se la lista non è vuota e se l'elemento c'è effettivamente
		{
			if(testa->val==x)  //se l'elemento è testa, la testa diventa testa->succ, deallochiamo la vecchia testa
			{
				Nodo_lista<H>* tmp=testa;
				testa=testa->succ;
				delete tmp;
				elementi--; //decremento elementi
			}
			else
			{
				Nodo_lista<H>* iter=testa; 
				Nodo_lista<H>* pre_iter=NULL;
				while(iter!=NULL&&iter->val!=x)  //iter terrà il puntatore del nodo con x, pre iter il precedente
				{
					pre_iter=iter;
					iter=iter->succ;
				}
				
				if(iter!=NULL)
				{
					pre_iter->succ=iter->succ;  //pre iter ->succ sarà ora il succ di iter 
					delete iter; //deallochiamo iter
					
					elementi--; //decremento elementi
				}
			}
			
		}
		
		void stampa(ofstream & f)
		{
			Nodo_lista<H>* iter=testa;
			while(iter!=NULL)
			{
				f<<iter->val<<" ";
				iter=iter->succ;
			}
		}
		
		Nodo_lista<H>* ricerca(H x) //semplice ricerca del nodo in cui c'è x
		{
			Nodo_lista<H>* iter=testa;
			while(iter!=NULL)
			{
				if(iter->val==x) return iter;
				iter=iter->succ;
			}
			return NULL;
		}
};

template <class H> struct Nodo_kb   //Nodo per la KB, conterrà una lista ordinata, un succ e un prec
{
	Lista<H>* lista;
	Nodo_kb<H>* succ;
	Nodo_kb<H>* prec;
};


template <class H> class KB
{
	public:
	    
		Nodo_kb<H>* testa;
		int limite; //valore massimo di nodi che può avere una lista
		
		KB(int n) {testa=NULL; limite=n;} //il limite è passato in input dal main
		
		void insert(H x)
		{
			if(testa==NULL || testa->lista->elementi==limite)  //caso in cui la lista-testa è vuota oppure ha raggiunto il limite
			{
			    Nodo_kb<H>* nuovo=new Nodo_kb<H>; //allocazione dinamica sia del nodo sia della lista dentro al nodo
				nuovo->lista=new Lista<H>;
				
				nuovo->lista->insert(x);  //insert di x in nuovo nodo
				nuovo->prec=NULL; //dato che sarà testa il prec va messo a NULL
				nuovo->succ=testa; //il suo succ sarà la precedente testa (se la precedente testa era NULL non causa problemi)
				
				if(testa!=NULL) testa->prec=nuovo; //se la testa non era NULL possiamo impostare il suo prec a nuovo(la nuova testa)
				
				testa=nuovo; //la testa diventa nuovo
			}
			else 
			{
				testa->lista->insert(x); //caso in cui la testa c'è  e non è piena, semplice insert di x
			}
		}
		
		void cancella(H x) //x : chiave da cancellare in ogni lista di KB
		{
			Nodo_kb<H>* iter=testa; //iter che parte da testa( di KB)
			while(iter!=NULL) //controlliamo ogni Nodo di KB
			{
				Nodo_kb<H>* post_iter=iter->succ; //teniamo il valore del succ
				Nodo_lista<H>* nodo=iter->lista->ricerca(x); //prendiamo il puntatore al nodo che contiene x nella lista del nodo iter
				
				if(nodo!=NULL) //se il nodo è NULL significa che x non è presente nella lista di iter, dunque non facciamo la procedura
				{
					iter->lista->cancella(x); //canc di x nella lista di iter
					if(iter->lista->elementi==0) // se la lista dopo la canc si svuota va riorganizzata la lista KB
					{
						if(iter==testa) testa=testa->succ; //se iter era la testa, la nuova testa diventa testa->succ;
						
						if(iter->prec!=NULL) iter->prec->succ=iter->succ; // se esiste il prec di iter, il suo nuovo succ sarà il succ di iter
						
						if(iter->succ!=NULL) iter->succ->prec=iter->prec;  //se esiste il succ di iter, il suo nuovo prec sarà il prec di iter
						
						delete iter->lista; //deallochiamo la lista in iter e iter
						delete iter;
					}
				}
				iter=post_iter;  //"incremento" per far andare avanti il ciclo, è come fare iter=iter->succ; ma quest
			}                      // istruzione non si può fare se per caso iter è diventata NULL dunque sarebbe errore a run time
		}
		
		void stampa(ofstream & f) //stampa di KB consiste nella stampa di ogni lista di KB
		{
			Nodo_kb<H>* iter=testa;
			while(iter!=NULL)
			{
				iter->lista->stampa(f);
				iter=iter->succ;
			}
			f<<endl;
		}
	
};


int main()
{
	ifstream miofile("input.txt");
	ofstream outfile("output.txt");
	
	for(int riga=0; riga<100; riga++)
	{
		string tipo;
		miofile>>tipo;
		
		int limite;
		miofile>>limite;
		
		if(tipo=="int")
		{
			KB<int>* kb=new KB<int>(limite);
			bool trovato=false;
			
			while(!trovato)
			{
				string op;
				miofile>>op;
				
				if(op=="#")
				{
					trovato=true;
				}
				else
				{
					if(op[0]=='i')
					{
						int dato;
						miofile>>dato;
						kb->insert(dato);
					}
					else 
					{
						int dato;
						miofile>>dato;
						kb->cancella(dato);
					}
				}
			}
			
			kb->stampa(outfile);
		}
		
		if(tipo=="double")
		{
			KB<double>* kb=new KB<double>(limite);
			bool trovato=false;
			
			while(!trovato)
			{
				string op;
				miofile>>op;
				
				if(op=="#")
				{
					trovato=true;
				}
				else
				{
					if(op[0]=='i')
					{
						double dato;
						miofile>>dato;
						kb->insert(dato);
					}
					else 
					{
						double dato;
						miofile>>dato;
						kb->cancella(dato);
					}
				}
			}
			
			kb->stampa(outfile);
		}
	}
	
	
	return 0;
}






































#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;


template <class H> struct Nodo
{
	
	H val;
	Nodo<H>* succ;	
};


template <class H> class Pila //classica pila implementata con i nodi
{
	private:
	    Nodo<H>* cima;
		
	public:
	    Pila() {cima=NULL;}
		
		H get_cima() {return cima->val;}
		
		void push(H x)
		{
			Nodo<H>* nuovo=new Nodo<H>;
			nuovo->val=x;
			
			nuovo->succ=cima;
			cima=nuovo;
		}
		
		H pop()
		{
			if(!pila_vuota())
			{
				H e=cima->val;
				Nodo<H>* tmp=cima->succ;
				delete cima;
				
				cima=tmp;
				return e;
			}
			return -1;
		}
		
		bool pila_vuota(){return cima==NULL;}
		
		void stampa(ofstream & f)
		{
			Nodo<H>* iter=cima;
			while(iter!=NULL)
			{
				f<<iter->val<<" ";
				iter=iter->succ;
			}
		}
};

template <class H> struct Nodo_multistack  //nodo contenente una pila e puntatori ad altri nodi (sono succ e prec)
{
	
	Pila<H>* stack;
	Nodo_multistack<H>* succ;
	Nodo_multistack<H>* prec;
};

template <class H> class Multistack
{
	private:
	    Nodo_multistack<H>* testa;
	
	public:
	    
		Nodo_multistack<H>* get_head() {return testa;}
		
		//inserimento nella prima pila
		void push(H x)
		{
			testa->stack->push(x); //x diventa la nuova cima della prima pila
			
			if(testa->succ!=NULL && x>=testa->succ->stack->get_cima())
				riordina(x); //se x è maggiore della cima del succ va riordinata la struttura
		}
		
		H pop() //estrazione cima della prima pila
		{
			H e=testa->stack->pop();
			
			if(testa->stack->pila_vuota()) //se la testa è diventata vuota
			{
				Nodo_multistack<H>* x=testa;
				testa=testa->succ;
				
				if(testa) testa->prec=NULL;  //il valore di testa va controllato dopo testa=testa->succ perchè il succ sarebbe potuto essere NULL
				
				delete x->stack; //dealloco la pila nel nodo e poi il nodo stesso
				delete x;
			}
			else if(testa->succ!=NULL && testa->stack->get_cima() >= testa->succ->stack->get_cima())
				riordina(testa->stack->get_cima()); //se la nuova cima della testa è >= della cima del succ la struttura va riordinata
			
			return e;
		}
		
		void riordina(H x) //siamo arrivati qua se la cima è cambiata e va eseguito un riordino
		{
			Nodo_multistack<H>* vecchia_testa=testa; //teniamo il valore di testa , il nodo in cui c'è x come cima
			testa=testa->succ;
			testa->prec=NULL;
			
			//dobbiamo trovare una nuova posizione per "vecchia testa"
			Nodo_multistack<H>* iter=testa;
			while(iter->succ!=NULL && !(x>=iter->stack->get_cima() && x<iter->succ->stack->get_cima()))
				iter=iter->succ;
			
			if(iter->succ==NULL) //caso in cui iter->succ è null dunque, dobbiamo inserire vecchia_testa in coda
			{
				iter->succ=vecchia_testa;
				vecchia_testa->prec=iter;
				vecchia_testa->succ=NULL;
			}
			else   //caso in cui ho trovato due cime consecutive  y,w  tali che   y<=x<w
			{
				vecchia_testa->succ=iter->succ; //impostiamo i due puntatori del nodo vecchia testa
				vecchia_testa->prec=iter;
				
				iter->succ->prec=vecchia_testa; //il prec del succ di iter diventa vecchia_testa
				iter->succ=vecchia_testa;  //il succ di iter diventa vecchia_testa
			}
		}
		
		
		void newPush(H x)   //crea nuovo stack con x come primo elemento e lo mette in Multistack
		{
			Nodo_multistack<H>* nuovo=new Nodo_multistack<H>; //alloco il nodo
			nuovo->stack=new Pila<H>;  //alloco la pila del nodo
			nuovo->stack->push(x); //metto x nella pila
			
			
			//adesso va inserito nella corretta posizione
			
			if(testa==NULL) //caso in cui multistack è vuoto
			{
				nuovo->succ=NULL;
				nuovo->prec=NULL;
				testa=nuovo;
			}
			else if(x<testa->stack->get_cima()) //caso in cui c'è almeno un elemento, ma x è minore della cima di questo elemento
			{
				nuovo->succ=testa;
				testa->prec=nuovo;
				nuovo->prec=NULL;
				testa=nuovo;
			}
			else //va eseguito un riordino ma non usiamo la suddetta funzione, quella funziona solo in seguito a un cambio di cima 
			{
				Nodo_multistack<H>* iter=testa;
				while(iter->succ!=NULL && !(x>=iter->stack->get_cima() && x<iter->succ->stack->get_cima()))
					iter=iter->succ;
				
				if(iter->succ==NULL) //inserimento in coda
				{
					iter->succ=nuovo;
					nuovo->prec=iter;
					nuovo->succ=NULL;
				}
				else //inserimento tra iter e iter->succ
				{
					nuovo->succ=iter->succ;
					nuovo->prec=iter;
					
					iter->succ->prec=nuovo;
					iter->succ=nuovo;
				}
			}
		}
		
		void stampa(ofstream & f)   //stampa da testa fino a coda tutti gli stack
		{
			Nodo_multistack<H>* iter=testa;
			while(iter!=NULL)
			{
				iter->stack->stampa(f);
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
		
		int n;
		miofile>>n;
		
		if(tipo=="int")
		{
			Multistack<int>* Ms=new Multistack<int>();
			for(int i=0; i<n;i++)
			{
				string op;
				miofile>>op;
				
				if(op=="pop" && Ms->get_head())
				{
					Ms->pop();
				}
				else if(op[0]=='p')
				{
					stringstream ss;
					ss<<op.substr(2,op.length()-1);
					int dato;
					ss>>dato;
					
					Ms->push(dato);
				}
				else //newPush
				{
					stringstream ss;
					ss<<op.substr(2,op.length()-1);
					int dato;
					ss>>dato;
					
					Ms->newPush(dato);
				}
			}
			Ms->stampa(outfile);
		}
		
		if(tipo=="double")
		{
			Multistack<double>* Ms=new Multistack<double>();
			for(int i=0; i<n;i++)
			{
				string op;
				miofile>>op;
				
				if(op=="pop" && Ms->get_head())
				{
					Ms->pop();
				}
				else if(op[0]=='p')
				{
					stringstream ss;
					ss<<op.substr(2,op.length()-1);
					double dato;
					ss>>dato;
					
					Ms->push(dato);
				}
				else //newPush
				{
					stringstream ss;
					ss<<op.substr(2,op.length()-1);
					double dato;
					ss>>dato;
					
					Ms->newPush(dato);
				}
			}
			Ms->stampa(outfile);
		}
	}
	return 0;
}


















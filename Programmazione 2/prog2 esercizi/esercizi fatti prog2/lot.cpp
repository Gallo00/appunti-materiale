#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


template <class H> struct Nodo_albero
{
	H val;
	Nodo_albero<H>* padre;
	Nodo_albero<H>* sx;
	Nodo_albero<H>* dx;
};

template <class H> class Albero  //classico albero in cui aggiungiamo una variabile che tiene conto di quanti nodi ci sono
{
	private:
	    Nodo_albero<H>* radice;
		int num_elementi; 
		
	public:
	    Albero() {radice=NULL; num_elementi=0;}
		
		int get_elements() {return num_elementi;}
		
		void insert(H x)
		{
			Nodo_albero<H>* nuovo=new Nodo_albero<H>;
			nuovo->val=x;
			nuovo->sx=nuovo->dx=NULL;
			
			Nodo_albero<H>* iter=radice;
			Nodo_albero<H>* pre_iter=NULL;
			
			while(iter!=NULL)
			{
				pre_iter=iter;
				
				if(x<=iter->val) iter=iter->sx;
				else iter=iter->dx;
			}
			
			nuovo->padre=pre_iter;
			if(pre_iter==NULL) radice=nuovo;
			else if(x<=pre_iter->val)pre_iter->sx=nuovo;
			else pre_iter->dx=nuovo;
			
			num_elementi++;
		}
		
		Nodo_albero<H>* ricerca(H x)
		{
			Nodo_albero<H>* iter=radice;
			while(iter!=NULL && iter->val!=x)
			{
				if(x<=iter->val) iter=iter->sx;
				else iter=iter->dx;
			}
			return iter;
		}
		
		Nodo_albero<H>* minimo(Nodo_albero<H>* z)
		{
			Nodo_albero<H>* min=z;
			while(min->sx!=NULL)
				min=min->sx;
			return min;
		}
		
		void trapianta(Nodo_albero<H>* x,Nodo_albero<H>* y)
		{
			if(x->padre==NULL) radice=y;
			else if(x->padre->sx==x) x->padre->sx=y;
			else x->padre->dx=y;
			
			if(y!=NULL) y->padre=x->padre;
		}
		
		void cancella(H x)
		{
			Nodo_albero<H>* k=ricerca(x);
			
			if(k->sx==NULL) trapianta(k,k->dx);
			else if(k->dx==NULL) trapianta(k,k->sx);
			else
			{
				Nodo_albero<H>* y=minimo(k->dx);
				if(y->padre!=k)
				{
					trapianta(y,y->dx);
					y->dx=k->dx;
					y->dx->padre=y;
				}
				
				trapianta(k,y);
				y->sx=k->sx;
				y->sx->padre=y;
			}
			delete k;
			num_elementi--;
		}
		
		void stampa(ofstream & f)
		{
			preorder(f,radice);
		}
		
		void preorder(ofstream & f,Nodo_albero<H>* sotto_rad)
		{
			if(sotto_rad!=NULL)
			{
				f<<sotto_rad->val<<" ";
				preorder(f,sotto_rad->sx);
				preorder(f,sotto_rad->dx);
			}
		}
	
};



template <class H> struct Nodo_lot{
	
	Albero<H>* tree;
	Nodo_lot<H>* succ;
	Nodo_lot<H>* prec;
};


template <class H> class lot
{
	
	private:
	    Nodo_lot<H>* testa;
		int limite;
		
	public:
	    lot(int n) {testa=NULL; limite=n;}
		
		void inserimento(H x) //in testa
		{
			if(testa==NULL || testa->tree->get_elements()==limite) //se non c'è testa o ha raggiunto il limite
			{
				Nodo_lot<H>* nuovo=new Nodo_lot<H>;
				nuovo->tree=new Albero<H>;
				
				nuovo->succ=testa;
				if(testa!=NULL) testa->prec=nuovo;
				
				nuovo->prec=NULL;
				nuovo->tree->insert(x);
				testa=nuovo;
			}
			else 
			{
				testa->tree->insert(x);
			}
		}
		
		void cancella(H x)
		{
			Nodo_lot<H>* iter=testa;
			while(iter!=NULL)
			{
				Nodo_lot<H>* post_iter=iter->succ;
				Nodo_albero<H>* nodo=iter->tree->ricerca(x); //vediamo se nell'albero in iter c'è x, in caso lo cancelliamo
				
				if(nodo!=NULL)
				{
					iter->tree->cancella(x);
					if(iter->tree->get_elements()==0) //se un albero si svuota va buttato fuori dalla lista
					{
						if(iter==testa) testa=testa->succ; //se è testa, la testa diventa succ
						
						if(iter->prec!=NULL) iter->prec->succ=iter->succ; //se il prec esiste adesso deve avere come succ il succ di iter
						
						if(iter->succ!=NULL) iter->succ->prec=iter->prec; //se il succ esiste adesso deve avere come prec il prec di iter
						
						delete iter->tree; //deallochiamo l'albero e il nodo iter
						delete iter;
					}
				}
				iter=post_iter; // "incremento" per far andare avanti il ciclo
			}
		}
		
		void stampa(ofstream & f)
		{
			Nodo_lot<H>* iter=testa;
			while(iter!=NULL)
			{
				iter->tree->stampa(f);
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
			lot<int>* lista=new lot<int>(limite);
			bool trovato=false;
			while(!trovato)
		    {
				string op;
			    miofile>>op;
				
			    if(op!="#")//fine ciclo
				{
				    int elemento;
				    miofile>>elemento;
				
				    if(op[0]=='i')
				    {
					    lista->inserimento(elemento);
				    }
				    else 
				    {
					    lista->cancella(elemento);
				    }
				}
				else trovato=true;
		    }
			lista->stampa(outfile);
		}
		
		if(tipo=="double")     
		{
			lot<double>* lista=new lot<double>(limite);
			while(1)
		    {
				string op;
			    miofile>>op;
			    if(op=="#") break; //fine ciclo
				
				double elemento;
				miofile>>elemento;
				
				if(op[0]=='i')
				{
					lista->inserimento(elemento);
				}
				else 
				{
					lista->cancella(elemento);
				}
		    }
			lista->stampa(outfile);
		}
	}
	
	return 0;
}





















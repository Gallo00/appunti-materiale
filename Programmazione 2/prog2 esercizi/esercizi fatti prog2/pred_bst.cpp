#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;


template <class H> struct Nodo
{
	public:
	    H val;
		Nodo<H>* padre;
		Nodo<H>* sx;
		Nodo<H>* dx;
};


template <class H> class Albero
{
	public:
	    Nodo<H>* radice;
		
		Albero() {radice=NULL;}
		
		
		Nodo<H>* ricerca(H x)
		{
			Nodo<H>* iter=radice;
			while(iter->val != x)
			{
				if(x <= iter->val)
				{
					iter=iter->sx;
				}
				else 
				{
					iter=iter->dx;
				}
			}
			return iter;
		}
		
		void insert(H x)
		{
			Nodo<H>* nuovo=new Nodo<H>;
			nuovo->val=x;
			nuovo->sx=nuovo->dx=NULL;
			
			Nodo<H>* iter=radice;
			Nodo<H>* pre_iter=NULL;
			
			while(iter!=NULL)
			{
				pre_iter=iter;
				if(nuovo->val <= iter->val)
				{
					iter=iter->sx;
				}
				else
				{
					iter=iter->dx;
				}
			}
			nuovo->padre=pre_iter;
			if(pre_iter==NULL) radice=nuovo;
			else if(nuovo->val <= pre_iter->val) pre_iter->sx=nuovo;
			else pre_iter->dx=nuovo;
		}
		
		Nodo<H>* Minimo(Nodo<H>* y)
		{
			Nodo<H>* min=y;
			while(min->sx != NULL) 
				min=min->sx;
			return min;
		}
		void trapianta(Nodo<H>* x, Nodo<H>* y)
		{
			if(x->padre==NULL) radice=y;
			else if(x->padre->sx == x) x->padre->sx=y;
			else x->padre->dx=y;
			
			if(y!=NULL)
				y->padre=x->padre;
		}
		
		void canc(H x)
		{
			Nodo<H>* k=ricerca(x);
			
			if(k->sx==NULL) trapianta(k,k->dx);
			else if(k->dx==NULL) trapianta (k,k->sx);
			else
			{
				Nodo<H>* y=Minimo(k->dx);
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
		}
		
		Nodo<H>* pred(H x)
		{
			Nodo<H>* k=ricerca(x);
		    Nodo<H>* iter=new Nodo<H>;
			iter=NULL;
			if(k->sx!=NULL)
			{
				iter=k->sx;
				while(iter->dx != NULL)
					iter=iter->dx;
				return iter;
			}
			else
			{
				if(k==radice) return NULL;
				else if(k==k->padre->dx) return k->padre;
				else 
				{
					iter=k->padre;
					bool trovato=false;
					while(iter->padre!=NULL && !trovato)
					{
						if(iter==iter->padre->dx)
						{
							trovato=true;
						}
						iter=iter->padre;
					}
					if(trovato) return iter;
					else return NULL;
				}
			}
			
		}
		
	
};

int main()
{
	fstream miofile("input.txt",fstream::in);
	ofstream outfile("output.txt");
	
	for(int riga=0; riga<100; riga++)
	{
		string tipo;
		miofile>>tipo;
		
		int operazioni;
		miofile>>operazioni;
		
		int dati_pred;
		miofile>>dati_pred;
		
		
		if(tipo=="int")
		{
			Albero<int> bst;
			for(int i=0; i<operazioni;i++)
			{
				string op;
			    miofile>>op;
			
			    if(op[0]=='i')  //inserimento
			    {
				    string a=op.substr(4,op.length()-1);
				    stringstream ss;
				    ss<<a;
				    int dato_nuovo;
				    ss>>dato_nuovo;
				
			     	bst.insert(dato_nuovo);
			    }
				
				if(op[0]=='c')  //canc
				{
					string a=op.substr(5,op.length()-1);
				    stringstream ss;
				    ss<<a;
				    int dato_da_cancellare;
				    ss>>dato_da_cancellare;
				
			     	bst.canc(dato_da_cancellare);
				}
			}
			
			for(int i=0; i<dati_pred;i++)
			{
				int dato;
				miofile>>dato;
				Nodo<int>* k = bst.pred(dato);
				if(k) outfile<<k->val<<" ";
				else outfile<<"-1 ";
			}
			outfile<<endl;
		}
		
		if(tipo=="double")
		{
			Albero<double> bst;
			for(int i=0; i<operazioni;i++)
			{
				string op;
			    miofile>>op;
			
			    if(op[0]=='i')  //inserimento
			    {
				    string a=op.substr(4,op.length()-1);
				    stringstream ss;
				    ss<<a;
				    double dato_nuovo;
				    ss>>dato_nuovo;
				
			     	bst.insert(dato_nuovo);
			    }
				
				if(op[0]=='c')  //canc
				{
					string a=op.substr(5,op.length()-1);
				    stringstream ss;
				    ss<<a;
				    double dato_da_cancellare;
				    ss>>dato_da_cancellare;
				
			     	bst.canc(dato_da_cancellare);
				}
			}
			
			for(int i=0; i<dati_pred;i++)
			{
				double dato;
				miofile>>dato;
				Nodo<double>* k = bst.pred(dato);
				if(k) outfile<<k->val<<" ";
				else outfile<<"-1 ";
			}
			outfile<<endl;
		}
	}
	
}









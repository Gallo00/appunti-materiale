#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

template <class H>struct Nodo
{
	public:
	H val;
	Nodo* sx;
	Nodo* dx;
	Nodo* padre;
};


template <class H> class Albero
{
	public:
	    Nodo<H>* radice;
		
		Nodo<H>* ricerca(H x)
		{
			Nodo<H>* iter=radice;
			while(iter->val!=x)
			{
				if(x<=iter->val)
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
		
		Albero()  {radice=NULL;}
		void inserimento(H x)
		{
			Nodo<H>* nuovo=new Nodo<H>;
			nuovo->val=x;
			nuovo->sx=nuovo->dx=NULL;
			
			Nodo<H>* iter=radice;
			Nodo<H>* pre_iter=NULL;
			
			while(iter!=NULL)
			{
				pre_iter=iter;
				if(nuovo->val<=iter->val)
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
			else if(nuovo->val<=pre_iter->val) pre_iter->sx=nuovo;
			else pre_iter->dx=nuovo;
		}
		
		void trapianta(Nodo<H>* x, Nodo<H>* y)
		{
			if(x->padre==NULL) radice=y;
			else if(x->padre->sx==x) x->padre->sx=y;
			else x->padre->dx=y;
			
			if(y!=NULL) y->padre=x->padre;
		}
		
		Nodo<H>* Minimo(Nodo<H>* p)
		{
			Nodo<H>* min=p;
			while(min->sx!=NULL)
				min=min->sx;
			return min;
		}
		
		void canc(H x)
		{
			Nodo<H>* k=ricerca(x);
			
			if(k->sx==NULL) trapianta(k,k->dx);
			else if(k->dx==NULL) trapianta(k,k->sx);
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
		
		H successore(H k)
		{
			Nodo<H>* x=ricerca(k);
			H valore=x->val;
			if(x->dx!=NULL) return (Minimo(x->dx))->val;
			else if(x==radice) return -1;
			else
			{
				Nodo<H>* iter=x->padre;
				while(iter->padre!=NULL && x==iter->dx)
				{
					x=iter;
					iter=iter->padre;
				}
				if(iter->val < valore) return -1;
				else return iter->val;
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
		
		int dati_succ;
		miofile>>dati_succ;
		
		
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
				
			     	bst.inserimento(dato_nuovo);
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
			
			for(int i=0; i<dati_succ;i++)
			{
				int dato;
				miofile>>dato;
				int k = bst.successore(dato);
				outfile<<k<<" ";
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
				
			     	bst.inserimento(dato_nuovo);
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
			
			for(int i=0; i<dati_succ;i++)
			{
				double dato;
				miofile>>dato;
				double k = bst.successore(dato);
				outfile<<k<<" ";
			}
			outfile<<endl;
		}
	}
	
	
	
}







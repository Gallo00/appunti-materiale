#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;


template <class H> struct Nodo
{
	H val;
	Nodo<H>* padre;
	Nodo<H>* sx;
	Nodo<H>* dx;
};


template <class H> class Albero
{
	public:
	Nodo<H>* radice;
	int altezza(Nodo<H>* t)
    {
	    if(t==NULL) return 0;  //siamo abituati con -1, ma faro vuole che sia 0 :D
	
	    int sin=altezza(t->sx);
	    int des=altezza(t->dx);
	    int max;
	
	    if(sin<des) max=des;
	    else max=sin;
	    return 1 + max;
    }
	
	int calcolo_altezza()  { return altezza(radice); }
	
	Albero() {radice=NULL;}
	
	Nodo<H>* ricerca(H x)
	{
		Nodo<H>* iter=radice;
		
		while(x!=iter->val)
		{
			if(x<=iter->val)
				iter=iter->sx;
			else 
				iter=iter->dx;
		}
		return iter;
	}
	void insert(H x);
	
	void canc(H x);
	void trapianta(Nodo<H>* x, Nodo<H>* y)
	{
		if(x==radice) radice=y;
		else if(x==NULL) radice=y;
		else if(x==x->padre->sx) x->padre->sx=y;
		else x->padre->dx=y;
		
		if(y!=NULL)
			y->padre=x->padre;
	}
	
	Nodo<H>* Minimo(Nodo<H>* x)
	{
		Nodo<H>* min=x;
		while(min->sx != NULL)
			min=min->sx;
		return min;
	}
	
	void print(ofstream & f);
};

template <class H> void Albero<H>::insert(H x)
{
	Nodo<H>* nuovo=new Nodo<H>;
	nuovo->val=x;
	nuovo->sx=NULL;
	nuovo->dx=NULL;
	
	Nodo<H>* iter=radice;
	Nodo<H>* pre_iter=NULL;
	
	while(iter!=NULL)
	{
		pre_iter=iter;
		if(x<=iter->val)
		{
			iter=iter->sx;
		}
		else
		{
			iter=iter->dx;
		}
	}
	nuovo->padre=pre_iter;
	if(pre_iter==NULL)
	{
		radice=nuovo;
	}
	else if(x<=pre_iter->val)
	{
		pre_iter->sx=nuovo;
	}
	else 
	{
		pre_iter->dx=nuovo;
	}
}

template <class H> void Albero<H>::canc(H x)
{
	Nodo<H>* iter=ricerca(x);
	if(iter->sx==NULL) trapianta(iter,iter->dx);
	else if(iter->dx==NULL) trapianta (iter,iter->sx);
	else
	{
		Nodo<H>* y=Minimo(iter->dx);
		if(y->padre!=iter)
		{
			trapianta(y, y->dx);
			y->dx=iter->dx;
			y->dx->padre=y;
		}
		trapianta(iter,y);
		y->sx=iter->sx;
		y->sx->padre=y;
	}
	delete iter;
}

template <class H> void Albero<H>::print(ofstream & f)
{
	int alt=calcolo_altezza();
	f<<alt<<endl;
}




int main()
{
	fstream miofile("input_alt.txt",fstream::in);
	ofstream outfile("output.txt");
	
	for(int riga=0; riga<100; riga++)
	{
		string tipo;
		miofile>>tipo;
		int operazioni;
		miofile>>operazioni;
		
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
			bst.print(outfile);
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
			bst.print(outfile);
		}
		
	}
}




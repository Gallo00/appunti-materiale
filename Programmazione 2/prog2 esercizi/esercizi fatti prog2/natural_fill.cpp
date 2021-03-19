#include <iostream>
#include <fstream>
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
	Albero() {radice=NULL; indice_nat=0;}
	int indice_nat;
	void insert(H x);
	
	void natural_fill(H * arr_valori_nuovi , Nodo<H>* p)
	{
		if(p!=NULL)
		{
		    natural_fill(arr_valori_nuovi,p->sx);
		    p->val=arr_valori_nuovi[indice_nat];
		    indice_nat++;
		    natural_fill(arr_valori_nuovi,p->dx);
		}
	}
	
	void post_order(ofstream & f,Nodo<H>* p)
	{
		if(p!=NULL)
		{
			post_order(f,p->sx);
			post_order(f,p->dx);
			f<<p->val <<" ";
		}
	}
	
	void print(ofstream & f)
	{
		post_order(f,radice);
		f<<endl;
	}
	
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

int main()
{
	fstream miofile("input_natural.txt",fstream::in);
	ofstream outfile("output.txt");
	
	for(int riga=0; riga<100; riga++)
	{
		string tipo;
		miofile>>tipo;
		int inserimenti;
		miofile>>inserimenti;
		
		if(tipo=="int")
		{
			Albero<int> bst;
			for(int i=0; i<inserimenti;i++)
			{
				int dato;
				miofile>>dato;
				bst.insert(dato);
			}
			
			int * array_natural_fill=new int[inserimenti];
			for(int i=0; i<inserimenti;i++)
			{
				int dato;
				miofile>>dato;
				array_natural_fill[i]=dato;
			}
			bst.natural_fill(array_natural_fill,bst.radice);
			bst.print(outfile);
		}
		
		if(tipo=="double")
		{
			Albero<double> bst;
			for(int i=0; i<inserimenti;i++)
			{
				double dato;
				miofile>>dato;
				bst.insert(dato);
			}
			
			double * array_natural_fill=new double[inserimenti];
			for(int i=0; i<inserimenti;i++)
			{
				double dato;
				miofile>>dato;
				array_natural_fill[i]=dato;
			}
			bst.natural_fill(array_natural_fill,bst.radice);
			bst.print(outfile);
		}
		
	}
}



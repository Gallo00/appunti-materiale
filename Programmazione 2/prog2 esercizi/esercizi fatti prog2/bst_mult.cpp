#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


template <class H> struct Nodo
{
	H val;
	int mult;
	
	Nodo<H>* padre;
	Nodo<H>* sx;
	Nodo<H>* dx;
};


template <class H> class Albero
{
	private:
	    Nodo<H>* radice;
		
	public:
	    Albero() {radice=NULL;}
		
		void insert(H x)
		{
			Nodo<H>* nuovo=new Nodo<H>;
			nuovo->val=x;
			nuovo->mult=1;
			
			nuovo->sx=nuovo->dx=NULL;
			
			Nodo<H>* iter=radice;
			Nodo<H>* pre_iter=NULL;
			
			while(iter!=NULL && iter->val!=x)
			{
				pre_iter=iter;
				if(x<=iter->val)iter=iter->sx;
				else iter=iter->dx;
			}
			
			if(iter!=NULL)
			{
				(iter->mult)++;
			}
			else
			{
				nuovo->padre=pre_iter;
				if(pre_iter==NULL) radice=nuovo;
				else if (x<=pre_iter->val) pre_iter->sx=nuovo;
				else pre_iter->dx=nuovo;
			}
		}
		
		Nodo<H>* ricerca(H x)
		{
			Nodo<H>* iter=radice;
			
			while(iter->val!=x)
			{
				if(x<=iter->val) iter=iter->sx;
				else iter=iter->dx;
			}
			return iter;
		}
		
		
		void trapianta(Nodo<H>* x, Nodo<H>* y)
		{
			if(x->padre==NULL) radice=y;
			else if(x->padre->sx==x) x->padre->sx=y;
			else x->padre->dx=y;
			
			if(y!=NULL) y->padre=x->padre;
		}
		
		Nodo<H>* minimo(Nodo<H>* x)
		{
			Nodo<H>* min=x;
			
			while(min->sx!=NULL)
				min=min->sx;
			
			return min;
		}
		
		void canc(H x)
		{
			Nodo<H>* k=ricerca(x);
			
			if(k->mult > 1) k->mult--;
			else
			{
				if(k->sx==NULL) trapianta(k,k->dx);
				else if(k->dx==NULL) trapianta(k,k->sx);
			    else
				{
					Nodo<H>* y=minimo(k->dx);
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
		}
		
		void _inorder(ofstream & f,Nodo<H>* sotto_rad)
		{
			if(sotto_rad!=NULL)
			{
				_inorder(f,sotto_rad->sx);
				
				for(int i=0; i<sotto_rad->mult;i++)
				{
					f<<sotto_rad->val<<" ";
				}
				
				_inorder(f,sotto_rad->dx);
			}
		}
		
		void _preorder(ofstream & f,Nodo<H>* sotto_rad)
		{
			if(sotto_rad!=NULL)
			{			
				for(int i=0; i<sotto_rad->mult;i++)
				{
					f<<sotto_rad->val<<" ";
				}
				_preorder(f,sotto_rad->sx);			
				_preorder(f,sotto_rad->dx);
			}
		}
		
		void _postorder(ofstream & f,Nodo<H>* sotto_rad)
		{
			if(sotto_rad!=NULL)
			{
				_postorder(f,sotto_rad->sx);
				_postorder(f,sotto_rad->dx);	
				for(int i=0; i<sotto_rad->mult;i++)
				{
					f<<sotto_rad->val<<" ";
				}
			}
		}
		
		
		void stampa(ofstream & f,int ord)
		{
			if(ord==0) _preorder(f,radice);
			else if(ord==1) _inorder(f,radice);
			else _postorder(f,radice);
			
			f<<endl;
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
		string ord;
		miofile>>ord;
		
		int state;
		
		if(ord=="preorder") state=0;
		else if(ord=="inorder") state=1;
		else state=2;
		
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
			
			bst.stampa(outfile,state);
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
			
			bst.stampa(outfile,state);
		}
		
	}
	
	return 0;
}














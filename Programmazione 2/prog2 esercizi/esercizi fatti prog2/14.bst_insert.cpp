#include <iostream>
#include <fstream>
using namespace std;


template <class H>
struct Nodo{
	H val;
	Nodo<H>* padre;
	Nodo<H>* sx;
	Nodo<H>* dx;
};


template <class H>
class BST
{
	private:
	    Nodo<H>* radice;
		
	public:
	    BST()  {radice=NULL;}
		
		void insert(H dato)
		{
			Nodo<H>* nuovo_nodo=new Nodo<H>;
			nuovo_nodo->val=dato;
			nuovo_nodo->sx =nuovo_nodo->dx= NULL;
			
			Nodo<H>* x=radice;
			Nodo<H>* y=NULL;
			
			while(x!=NULL)
			{
				y=x;
				
				if(dato<=x->val)
				{
					x=x->sx;
				}
				else
				{
					x=x->dx;
				}
				
			}
			
			nuovo_nodo->padre=y;
			if(y==NULL)
			{
				radice=nuovo_nodo;
			}
			else if(dato<=y->val)
			{
				y->sx=nuovo_nodo;
			}
			else
			{
				y->dx=nuovo_nodo;
			}
		}
		
		
		void inorder(Nodo<H>* p,ofstream & f)
		{
			if(p!=NULL)
			{
			    inorder(p->sx,f);
			    f<<p->val<<" ";
			    inorder(p->dx,f);
			}
		}
		void preorder(Nodo<H>* p,ofstream & f)
		{
			if(p!=NULL)
			{
			f<<p->val<<" ";
			preorder(p->sx,f);
			preorder(p->dx,f);
			}
		}
		void postorder(Nodo<H>* p,ofstream & f)
		{
			if(p!=NULL)
			{
			postorder(p->sx,f);
			postorder(p->dx,f);
			f<<p->val<<" ";
			}
		}
		
		void stampa_file(ofstream& f , int p)
		{
			Nodo<H>* iter=radice;
			if(p==0)
				preorder(iter,f);
			if(p==1)
				inorder(iter,f);
			if(p==2)
				postorder(iter,f);
			
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
		
		bool tipo_int=false;
		if(tipo=="int")
			tipo_int=true;
		
		bool tipo_double=false;
		if(tipo=="double")
			tipo_double=true;
		
		bool tipo_char=false;
		if(tipo=="char")
			tipo_char=true;
		
		bool tipo_bool=false;
		if(tipo=="bool")
			tipo_bool=true;
		
		int lung;
		miofile>>lung;
		
		int var;
		string ord;
		miofile>>ord;
		
		if(ord=="preorder")
			var=0;
		if(ord=="inorder")
			var=1;
		if(ord=="postorder")
			var=2;
		
		if(tipo_int)
		{
			BST<int> albero;
			for(int i=0; i<lung; i++)
			{
				int a;
				miofile>>a;
				albero.insert(a);
			}
			albero.stampa_file(outfile,var);
		}
		
		if(tipo_double)
		{
			BST<double> albero;
			for(int i=0; i<lung; i++)
			{
				double a;
				miofile>>a;
				albero.insert(a);
			}
			albero.stampa_file(outfile,var);
		}
		
		if(tipo_bool)
		{
			BST<bool> albero;
			for(int i=0; i<lung; i++)
			{
				bool a;
				miofile>>a;
				albero.insert(a);
			}
			albero.stampa_file(outfile,var);
		}
		
		if(tipo_char)
		{
			BST<char> albero;
			for(int i=0; i<lung; i++)
			{
			    char a;
				miofile>>a;
				albero.insert(a);
			}
			albero.stampa_file(outfile,var);
		}
	}
	
	miofile.close();
	outfile.close();
	return 0;
}




















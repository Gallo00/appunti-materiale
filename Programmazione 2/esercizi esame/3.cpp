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
	
	void print(int tipo_ord,ofstream & f);
	
	void insert(H x);
	
	void pre_order(ofstream & f,Nodo<H>* p)
	{
		if(p!=NULL)
		{
		    f<<p->val<<" ";
		    pre_order(f,p->sx);
		    pre_order(f,p->dx);
	    }
	}
	void in_order(ofstream & f,Nodo<H>* p)
	{
		if(p!=NULL)
		{
		    in_order(f,p->sx);
			f<<p->val<<" ";
		    in_order(f,p->dx);
	    }
	}
	void post_order(ofstream & f,Nodo<H>* p)
	{
		if(p!=NULL)
		{
		    post_order(f,p->sx);
		    post_order(f,p->dx);
			f<<p->val<<" ";
	    }
	}
	
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
	
	Nodo<H>* common_ancestor(H val_1,H val_2,Nodo<H>* sotto_rad)
	{
		cout<<"91"<<endl;
		if(val_1 < sotto_rad->val && val_2 < sotto_rad->val)
			return common_ancestor(val_1,val_2,sotto_rad->sx);
		
		else if(val_1 > sotto_rad->val && val_2 > sotto_rad->val)
			return common_ancestor(val_1,val_2,sotto_rad->dx);
		
		
		else {cout<<"98"<<endl; return sotto_rad;}
	}
	
	Nodo<H>* common_ancestor(H val_1,H val_2)
	{
		cout<<"104"<<endl;
		return common_ancestor(val_1,val_2,radice);
		cout<<"106"<<endl;
	}
	
	int ricerca_livello(Nodo<H>* x,int h)
	{
		cout<<"107"<<endl;
		Nodo<H>* it=ricerca(h);
		Nodo<H>* iter=new Nodo<H>;
		iter=x;
		int livello=0;
		
		while(it->val!=iter->val && iter!=NULL)
		{
			if(h<=iter->val)
				iter=iter->sx;
			else 
				iter=iter->dx;
			
			livello++;
		}
		return livello;
		cout<<"123"<<endl;
	}
	
	int distanza(int h,int k)
	{
		cout<<"126"<<endl;
		Nodo<H>* it=common_ancestor(h,k);
		int i=ricerca_livello(it,h);
		int j=ricerca_livello(it,k);
		
		cout<<"130"<<endl;
		return i+j;
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
			int h,k;
			miofile>>h;
			miofile>>k;
			outfile<<bst.distanza(h,k);
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
			double h,k;
			miofile>>h;
			miofile>>k;
			outfile<<bst.distanza(h,k);
			outfile<<endl;
		}
		
	}
}



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


template <class H> class albero
{
	public:
	
	Nodo<H>* radice;
	albero() {radice=NULL;}
	
	void insert(H x)
	{
		Nodo<H>* nuovo= new Nodo<H>;
		nuovo->val=x;
		nuovo->sx=nuovo->dx=NULL;
		
		Nodo<H>* iter=radice;
		Nodo<H>* pre_iter=NULL;
		
		while(iter!=NULL)
		{
			pre_iter=iter;
			if(nuovo->val <= iter->val) iter=iter->sx;
			else iter=iter->dx;	
		}
		
		nuovo->padre=pre_iter;
		if(pre_iter==NULL) radice=nuovo;
		else if(nuovo->val <= pre_iter->val) pre_iter->sx=nuovo;
		else pre_iter->dx=nuovo;	
	}
	
	Nodo<H>* ricerca(H x)
	{
		Nodo<H>* iter=radice;
		while(iter!=NULL && iter->val !=x)
		{
			if(x <= iter->val) iter=iter->sx;
			else iter=iter->dx;
		}
		return iter;
	}
	
	Nodo<H>* minimo(Nodo<H>* sotto_rad)
	{
		Nodo<H>* min=sotto_rad;
		while(min->sx!=NULL)
			min=min->sx;
		return min;
	}
	
	void trapianta(Nodo<H>* x,Nodo<H>* y)
	{
		if(x->padre==NULL) radice=y;
		else if(x->padre->sx==x) x->padre->sx=y;
		else x->padre->dx=y;
		
		if(y!=NULL) y->padre=x->padre;
	}
	
	void canc(H x)
	{
		Nodo<H>* k=ricerca(x);
		
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
	
	H common_ancestor(H val_1,H val_2,Nodo<H>* sotto_rad)
	{
		if(val_1 < sotto_rad->val && val_2 < sotto_rad->val)
			return common_ancestor(val_1,val_2,sotto_rad->sx);
		
		else if(val_1 > sotto_rad->val && val_2 > sotto_rad->val)
			return common_ancestor(val_1,val_2,sotto_rad->dx);
		
		else return sotto_rad->val;
	}
	
	H common_ancestor(H val_1,H val_2)
	{
		return common_ancestor(val_1,val_2,radice);
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
		
		if(tipo=="int")
		{
			albero<int> bst;
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
			int val_1;
			miofile>>val_1;
			int val_2;
			miofile>>val_2;
			
			int common=bst.common_ancestor(val_1,val_2);
			outfile<<common<<endl;
		}
		
		if(tipo=="double")
		{
			albero<double> bst;
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
			double val_1;
			miofile>>val_1;
			double val_2;
			miofile>>val_2;
			double common=bst.common_ancestor(val_1,val_2);
			outfile<<common<<endl;
		}
		
	}
}









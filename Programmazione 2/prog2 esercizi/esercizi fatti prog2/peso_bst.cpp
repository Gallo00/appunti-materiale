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

template <class H> struct Albero
{
	
	public:
	    Nodo<H>* radice;
		
		Albero() {radice=NULL;}
		
		void insert(H x)
		{
		//	cout<<"inserisco "<<x<<endl;
			Nodo<H>* nuovo=new Nodo<H>;
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
			while(iter!=NULL && iter->val!=x)
			{
				if(x <=iter->val) iter=iter->sx;
				else iter=iter->dx;
			}
			return iter;
		}
		
		void trapianta(Nodo<H>* x,Nodo<H>* y)
		{
			if(x->padre==NULL) radice=y;
			else if(x==x->padre->sx) x->padre->sx=y;
			else x->padre->dx=y;
			
			if(y!=NULL) y->padre=x->padre;
		}
		
		Nodo<H>* minimo(Nodo<H>* sotto_rad)
		{
			Nodo<H>* min=sotto_rad;
			while(min->sx!=NULL)
				min=min->sx;
			return min;
		}
		
		void canc(H x)
		{
		//	cout<<"cancello "<<x<<endl;
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
		
		void peso(Nodo<H>* sotto_rad,H& somma)
		{
			if(sotto_rad==NULL) return;
			
			somma=somma+sotto_rad->val;
			peso(sotto_rad->sx,somma);
			peso(sotto_rad->dx,somma);
			
		}
		
		H peso_tot(H chiave)
		{
			Nodo<H>* k=ricerca(chiave);
			H p=chiave;
			
			peso(k->sx,p);
			peso(k->dx,p);
			
			return p;
		}
};


int main()
{
	fstream miofile("input.txt",fstream::in);
	ofstream outfile("output.txt");
	
	for(int riga=0; riga<100; riga++)
	{
	//	cout<<"*******************RIGA: "<<riga<<"********************************"<<endl;
		string tipo;
		miofile>>tipo;
		
		int operazioni;
		miofile>>operazioni;
		
	//	cout<<riga<<" "<<tipo<<" "<<operazioni<<endl;
        

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
			int chiave;
			miofile>>chiave;
			int peso=bst.peso_tot(chiave);
			outfile<<peso<<endl;
			
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
            double chiave;
			miofile>>chiave;
			double peso=bst.peso_tot(chiave);
			outfile<<peso<<endl;		
		}
	}
	
}













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
	private:
	    Nodo<H>* radice;
	
	public:
	    Albero() {radice=NULL;}
		
		void insert(H x)
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
				if(x <= iter->val)iter=iter->sx;
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
			while(iter->val!=x && iter!=NULL)
			{
				if(iter->val >= x) iter=iter->sx;
				else iter=iter->dx;
			}
			return iter;
		}
		
		Nodo<H>* minimo(Nodo<H>* rad_sotto_albero)
		{
			Nodo<H>* min=rad_sotto_albero;
			while(min->sx!=NULL)
			min=min->sx; 
			return min;
		}
		
		void trapianta(Nodo<H>* x, Nodo<H>* y)
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
		
		//dato un nodo trovare la differenza in valore assoluto dei nodi nel suo sottoalbero destro
		// e dei nodi nel suo sottoalbero sinistro
		
		void somma(Nodo<H>* rad,int& counter)
		{
			if(rad==NULL) return;
			
			counter++;
			somma(rad->sx,counter);
			somma(rad->dx,counter);
		}
		
		int differenza(H x)
		{
			Nodo<H>* rad=ricerca(x);
			int differenza;
			int somma_sx=0;
			int somma_dx=0;
			
			somma(rad->sx,somma_sx);
			somma(rad->dx,somma_dx);
			
			differenza=somma_dx - somma_sx;
			if(differenza<0) differenza=differenza*(-1);
			
			return differenza;
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
			int bilanciamento=bst.differenza(chiave);
			outfile<<bilanciamento<<endl;   
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
			int bilanciamento=bst.differenza(chiave);
			outfile<<bilanciamento<<endl;  
		}
	}
	
}












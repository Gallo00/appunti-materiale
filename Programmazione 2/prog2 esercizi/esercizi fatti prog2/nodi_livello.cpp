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
	Albero() {radice=NULL; iCurrentHeight=0; iMaxHeight=0; pArray=new H[100]; for(int i=0; i<100;i++)pArray[i]=0;}
	
	int iCurrentHeight;
	int iMaxHeight;
	H* pArray;
	
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
	
	void _altezza(Nodo<H> *pLastRoot){  //plastroot all'inizio sarà radice

        if(pLastRoot == NULL)
            return;

        pArray[iCurrentHeight]++;    //siamo al livello corrente dunque c'è un nodo, si incrementa
        iCurrentHeight++;               //incrementiamo h
        if(iCurrentHeight > iMaxHeight)
            iMaxHeight = iCurrentHeight;

        _altezza(pLastRoot->sx);     //richiamo ricorsivo sui due sottoalberi
        _altezza(pLastRoot->dx);

       iCurrentHeight--;           //alla fine della procedura dobbiamo "tornare indietro" 
 
    }
	
	void stampa_alt(ofstream & f)
	{
		_altezza(radice);
		
		f<<iMaxHeight -1<<" ";
		
		for(int i=0; i<iMaxHeight;i++)
			f<<pArray[i]<<" ";
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
			
			bst.stampa_alt(outfile);
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
			bst.stampa_alt(outfile);
		}
		
	}
}

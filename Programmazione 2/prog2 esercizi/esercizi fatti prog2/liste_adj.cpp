#include <iostream>
#include <fstream>
#include <typeinfo>
#include <sstream>
using namespace std;


template <class H> struct Nodo
{
	H val;
	Nodo* succ;
};

template <class H> class Lista
{
	public:
	    Nodo<H>* testa;
		
		Lista() {testa=NULL;}
		void insert(H x);
		Nodo<H>* ricerca(H x);
		Nodo<H>* rivela_testa() {return testa;}
};

template <class H> void Lista<H>::insert(H x)
{
	Nodo<H>* nuovo=new Nodo<H>;
	nuovo->val=x;
	nuovo->succ=testa;
	testa=nuovo;
}

template <class H> Nodo<H>* Lista<H>::ricerca(H x)
{
	Nodo<H>* iter=testa;
	while(iter!=NULL)
	{
		if(iter->val==x)
			return iter;
		iter=iter->succ;
	}
	return NULL;
}

template <class H>  class Lgrafo
{
	public:
	    int len, n , m;
		H** K;
		Lista<int>** Adj;
		
		int trova_index(H x)
		{
			for(int i=0; i<n;i++)
				if(*K[i]==x) return i;
			
			return -1;
		}
		
		Lgrafo(int lung)
		{
			len=lung;
			n=m=0;
			K=new H*[len];
			for(int i=0; i<len;i++) K[i]=NULL;
			
			Adj=new Lista<int>*[len];
			for(int i=0; i<len;i++) Adj[i]=new Lista<int>();
			
		}
		
		void addNode(H x)
		{
			K[n]=new H(x);
			n++;
			ordinamento_scambio_punt(K,n);
		}
		
		void addEdge(H x , H y)
		{
			int i=trova_index(x);
			int j=trova_index(y);
			if(i<0 || j<0) return;
			else if(!Adj[i]->ricerca(j))
			{
				Adj[i]->insert(j);
				m++;
			}
			return;
		}
		
		void scambia(H &a, H &b)
		{
			H var=a;
			a=b;
			b=var;
		}
		void ordinamento_scambio_punt(H* a[],int lung)
		{
			for(int i=0; i<lung-1;i++)
			{
				for(int j=i+1; j<lung;j++)
				{
					if(*a[i]>*a[j]) scambia(*a[i],*a[j]);
				}
			}
		}
		void ordinamento_scambio(H a[],int ind)
		{
	        for(int i=0;i<ind+1-1; i++)
			{
		        for(int j=i+1; j<ind+1;j++)
				{
			        if(a[i]>a[j]) scambia(a[i],a[j]);
                }
			}
	    }
		void print(ofstream & f)
		{
			bool caratteri=false;
			if(typeid(H)==typeid(char))
				caratteri=true;
			
			
			for(int i=0; i<len; i++)
			{
				if(!caratteri)
				    f<<"("<<*K[i];
				else 
				{
					f<<"(";
				    string a="a";
					a[0]=*K[i];
					f<<a;
				}
				H arr[len];
				int l=-1;
				Nodo<int>* iter=Adj[i]->rivela_testa();
				while(iter!=NULL)
				{
					l++;
					arr[l]= *K[iter->val];
					iter=iter->succ;
				}
				if(l==-1) f<<") ";
				else
				{
					f<<" ";
				    ordinamento_scambio(arr,l);
				    for(int j=0; j<l;j++)
				    {
						if(!caratteri)
					        f<<arr[j]<<" ";
						else 
						{
							string a="a";
							a[0]=arr[j];
							f<<a;
							f<<" ";
						}
				    }
					if(!caratteri)
				        f<<arr[l]<<") ";
					else 
					{
						string a="a";
						a[0]=arr[l];
						f<<a;
						f<<") ";
					}
				}
			}
			f<<endl;
		}
	
};


int main()
{
	fstream miofile("input_list.txt",fstream::in);
	ofstream outfile("output.txt");
	for(int riga=0;riga<100;riga++)
	{
		int nodi;
		miofile>>nodi;
		
		int archi;
		miofile>>archi;
		
		string tipo;
		miofile>>tipo;
		
		
		if(tipo=="int")
		{
			Lgrafo<int> gr(nodi);
			for(int i=0; i<nodi; i++)
			{
				int dato;
				miofile>>dato;
				gr.addNode(dato);
			}
			
			for(int i=0; i<archi;i++)
			{
				string prima_parte_arco;
				miofile>>prima_parte_arco;
				stringstream primo_val;
				int j;
				for(j=1; prima_parte_arco[j]!=' '; j++)
				{
					primo_val<<prima_parte_arco[j];
				}
				int val1;
				primo_val>>val1;
				
				string sec_parte_arco;
				miofile>>sec_parte_arco;
				stringstream sec_val;
				for(j=0;sec_parte_arco[j]!=')';j++)
				{
					sec_val<<sec_parte_arco[j];
				}
				int val2;
				sec_val>>val2;
				
				gr.addEdge(val1,val2);
			}
			gr.print(outfile);
		}
		
		if(tipo=="double")
		{
			Lgrafo<double> gr(nodi);
			for(int i=0; i<nodi; i++)
			{
				double dato;
				miofile>>dato;
				gr.addNode(dato);
			}
			
			for(int i=0; i<archi;i++)
			{
				string prima_parte_arco;
				miofile>>prima_parte_arco;
				stringstream primo_val;
				int j;
				for(j=1; prima_parte_arco[j]!=' '; j++)
				{
					primo_val<<prima_parte_arco[j];
				}
				double val1;
				primo_val>>val1;
				
				string sec_parte_arco;
				miofile>>sec_parte_arco;
				stringstream sec_val;
				for(j=0;sec_parte_arco[j]!=')';j++)
				{
					sec_val<<sec_parte_arco[j];
				}
				double val2;
				sec_val>>val2;
				
				gr.addEdge(val1,val2);
			}
			gr.print(outfile);
		}
		
		
		
		if(tipo=="char")
		{
			Lgrafo<char> gr(nodi);
			for(int i=0; i<nodi; i++)
			{
				char dato;
				miofile>>dato;
				gr.addNode(dato);
			}
			for(int i=0; i<archi;i++)
			{
				string arco;
				miofile>>arco;
				stringstream primo_val;
				
				primo_val<<arco[1];
				char val1;
				primo_val>>val1;
				
				stringstream sec_val;
				string arco2;
				miofile>>arco2;
				sec_val<<arco2[0];
			
				char val2;
				sec_val>>val2;
				
				gr.addEdge(val1,val2);
			}
			gr.print(outfile);
		}
		
	}
	return 0;
}











#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <typeinfo>
using namespace std;


template <class H>
class Mgrafo
{
	public:
	    int len;
		int n;
		
		H** K;
		bool **M;
		
		int trova_indice(H x) //trovare indice di x(se c'è)
		{
			for(int i=0; i<len ; i++)
			{
				if(*K[i]==x) return i;
			}
			return -1;
		}
		
		Mgrafo(int lung)  //costruttore
		{
			len=lung;
			n=0;
			K=new H*[len];
			for(int i=0; i<len;i++) K[i]=NULL;
			
			M=new bool*[len];
			for(int i=0; i<len; i++)
			{
				M[i]=new bool[len];
				for(int j=0; j<len;j++)
				{
					M[i][j]=false;
				}
			}
		}
		void addNode(H x)
		{
			K[n]=new H(x);
			n++;
			
			ordinamento_scambio_punt(K,n);
		}
		
		void addEdge(H x, H y)
		{
			int i=trova_indice(x);
			int j=trova_indice(y);
			M[i][j]=true;
		}
		
		
		void scambia(H &a, H &b)
		{
	        H var=a;
	        a=b;
	        b=var;
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
		
		void ordinamento_scambio_punt(H* a[],int n)
		{
	        for(int i=0;i<n-1; i++)
			{
		        for(int j=i+1; j<n;j++)
				{
			        if(*a[i]>*a[j]) scambia(*a[i],*a[j]);
                }
			}
	    }
        

		
		
		void print(ofstream & f)
		{
			bool caratteri=false;
			if(typeid(H)==typeid(char))
				caratteri=true;
			
			for(int i=0; i<len;i++)
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
				for(int j=0; j<len;j++)
				{
					if(M[i][j])
					{
						l++;
						arr[l]=*K[j];
					}
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
	fstream miofile("inputmatriciad.txt",fstream::in);
	ofstream outfile("output.txt");
	

	for(int riga=0; riga<100; riga++)
	{
		int nodi;
		miofile>>nodi;
		
		int archi;
		miofile>>archi;
		
		string tipo;
		miofile>>tipo;
		
	//	cout<<nodi<<" "<<archi<<" "<<tipo<<endl;
		
		if(tipo=="int")
		{
			Mgrafo<int> gr(nodi);
			for(int i=0; i<nodi; i++)
			{
				int dato;
				miofile>>dato;
				gr.addNode(dato);
			//	cout<<"fatta addnode"<<endl;
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
			//	cout<<"fatta addedge"<<endl;
			}
			gr.print(outfile);
		}
		
		if(tipo=="double")
		{
			Mgrafo<double> gr(nodi);
			for(int i=0; i<nodi; i++)
			{
				double dato;
				miofile>>dato;
				gr.addNode(dato);
			}
			for(int i=0; i<archi;i++)
			{
				string arco;
				miofile>>arco;
				stringstream primo_val;
				int j;
				for(j=1; arco[j]!=' '; j++)
				{
					primo_val<<arco[j];
				}
				double val1;
				primo_val>>val1;
				
				stringstream sec_val;
				string arco2;
				miofile>>arco2;
				for(j=0;arco2[j]!=')';j++)
				{
					sec_val<<arco2[j];
				}
				double val2;
				sec_val>>val2;
				
				gr.addEdge(val1,val2);
			}
			gr.print(outfile);
		}
		
		if(tipo=="char")
		{
			Mgrafo<char> gr(nodi);
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



#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


template <class H> class Mgrafo
{
	private:
	    int len,n,m;
		
		bool** M;
		H** K;
		
		bool** tM;
		
		int* colori;
		int* marche_entrate;
		int* marche_uscite;
		int t;
		
		
	public:
	    
		Mgrafo(int len)
		{
			this->len=len;
			n=m=0;
			
			M=new bool*[len];
			tM=new bool*[len];
			for(int i=0; i<len; i++)
			{
				M[i]=new bool[len];
				tM[i]=new bool[len];
				for(int j=0; j<len;j++)
				{
					M[i][j]=false;
					tM[i][j]=false;
				}
			}
			
			K=new H*[len];
			for(int i=0; i<len;i++) K[i]=NULL;
			
			colori=new int[len];
			t=0;
			marche_entrate=new int[len];
			marche_uscite=new int[len];
		}
		
		int find_index(H x)
		{
			for(int i=0; i<n;i++)
			{
				if(*K[i]==x) return i;
			}
			return -1;
		}
		
		void addNode(H x)
		{
			if(n==len) return;
			if(find_index(x)>=0) return;
			K[n]=new H(x);
			n++;
		}
		
		void addEdge(H x, H y)
		{
			int i=find_index(x);
			int j=find_index(y);
			
			if(i<0 || j<0) return;
			if(!M[i][j])
			{
				M[i][j]=true;
				m++;
			}
		}
		
		
		int DFSvisit(int s)
		{
			int W=0;
			int G=1;
			int B=2;
			
			int cycle=0;
			colori[s]=G;
			marche_entrate[s]=t;
			t++;
			
			for(int i=0; i<n;i++)
			{
				if(M[s][i])
				{
					if(colori[i]==W)
					{
						cycle|=DFSvisit(i);
					}
					if(colori[u]==G) cycle = 1;
				}
			}
			colori[s]=B;
			marche_uscite[s]=t;
			t++;
			return cycle;
		}
		
		int DFS()
		{
			t=0;
			int W=0;
			int cycle=0;
			for(int i=0; i<n;i++)
			{
				colori[i]=W;
			}
			
			for(int i=0; i<n;i++)
			{
				if(colori[i]==W)
				{
					cycle|=DFSvisit(i);
				}
			}
			return cycle;
		}
		
		void sort(int* a,int n,int* f)
		{
			for(int i=0; i<n;i++)
			{
				int j=i-1;
				while(j>=0 && f[a[j+1]]>f[a[j]])
				{
					int tmp=a[j+1];
					a[j+1]=a[j];
					a[j]=tmp;
					j--;
				}
			}
		}
		
		void topsort(ofstream & outfile)
		{
			int cycle=DFS();
			if(cycle) return;
			
			int* indici=new int[len];
			for(int i=0; i<n;i++)
				indici[i]=i;
			
			sort(indici,n,marche_uscite);
			for(int i=0; i<n;i++)
			{
				outfile<<*K[indici[i]]<<" ";
			}
			outfile<<endl;
		}
	
};


int main()
{
	fstream miofile("input.txt",fstream::in);
	ofstream outfile("output.txt");
	
for(int riga=0; riga<100;riga++)
{
	int nodi;
	miofile>>nodi;
		
	int archi;
	miofile>>archi;
		
	string tipo;
	miofile>>tipo;
		
	
	if(tipo=="int")
	{
		Mgrafo<int> gr(nodi);
		for(int i=0; i<nodi; i++)
		{
		    int dato;
			miofile>>dato;
			gr.addNode(dato);
		}
		for(int i=0; i<archi;i++)
		{
			string parte1;
			miofile>>parte1;
			string dato_stringa=parte1.substr(1,parte1.length()-1);
			int dato;
			stringstream ss;
			ss<<dato_stringa;
			ss>>dato;
				
			string parte2;
			miofile>>parte2;
			string dato_stringa2=parte2.substr(0,parte2.length()-1);
			int dato2;
			stringstream s;
			s<<dato_stringa2;
			s>>dato2;
			gr.addEdge(dato,dato2);
		}
		gr.topsort(outfile);
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
			string parte1;
			miofile>>parte1;
			string dato_stringa=parte1.substr(1,parte1.length()-1);
			char dato;
			stringstream ss;
			ss<<dato_stringa;
			ss>>dato;
				
			string parte2;
			miofile>>parte2;
			string dato_stringa2=parte2.substr(0,parte2.length()-1);
			char dato2;
			stringstream s;
			s<<dato_stringa2;
			s>>dato2;
			gr.addEdge(dato,dato2);
		}
		gr.topsort(outfile);
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
			string parte1;
			miofile>>parte1;
			string dato_stringa=parte1.substr(1,parte1.length()-1);
			double dato;
			stringstream ss;
			ss<<dato_stringa;
			ss>>dato;
				
			string parte2;
			miofile>>parte2;
			string dato_stringa2=parte2.substr(0,parte2.length()-1);
			double dato2;
			stringstream s;
			s<<dato_stringa2;
			s>>dato2;
			gr.addEdge(dato,dato2);
		}
		gr.topsort(outfile);
	}
		
}
	return 0;

}







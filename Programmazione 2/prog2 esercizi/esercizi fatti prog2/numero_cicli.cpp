#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

template <class H> class Mgrafo{
	
	private:
	int len;
	int n;
	int m;
	
	bool** M;
	H** K;
	
	int* colori;
	int contatore_cicli;
	
	public:
	    Mgrafo(int lung)
	    {
			len=lung;
			n=m=0;
			
			M=new bool*[len];
		    for(int i=0; i<len;i++)
			{
				M[i]=new bool[len];
			    for(int j=0; j<len;j++)
				{
					M[i][j]=false;
				}
			}
			
			K=new H*[len];
			for(int i=0; i<len; i++) K[i]=NULL;
			
			colori=new int[len];
			for(int i=0; i<len;i++) colori[i]=0;  //white
			
			contatore_cicli=0;
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
		
		void DFS_visit(int s)
		{
			int W=0;
			int G=1;
			int B=2;
			
			colori[s]=G;
			
			for(int i=0; i<n;i++)
			{
				if(M[s][i])
				{
					if(colori[i]==W)
					{
						DFS_visit(i);
					}
					
					if(colori[i]==G)
					{
						contatore_cicli++;
					}
				}
			}
			
			colori[s]=B;
		}
		
		
		void DFS()
		{
			int W=0;
			for(int i=0; i<n;i++)
				colori[i]=W;
			
			for(int i=0; i<n;i++)
			{
				if(colori[i]==W)
				{
					DFS_visit(i);
				}
			}
		}
		
		int return_cicli()
		{
			return contatore_cicli;
		}
	
};


int main()
{
	fstream miofile("input.txt",fstream::in);
	ofstream outfile("output.txt",fstream::out);
	for(int riga=0; riga<100; riga++)
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
			gr.DFS();
			int cicli=gr.return_cicli();
			outfile<<cicli<<endl;
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
			gr.DFS();
			int cicli=gr.return_cicli();
			outfile<<cicli<<endl;
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
				char dato=parte1[1];
				
				string parte2;
				miofile>>parte2;
				char dato2=parte2[0];
				gr.addEdge(dato,dato2);
			}
			gr.DFS();
			int cicli=gr.return_cicli();
			outfile<<cicli<<endl;
		}
	}
	
	return 0;
}






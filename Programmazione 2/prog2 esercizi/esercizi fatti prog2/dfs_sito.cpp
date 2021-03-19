#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;


template <class H> class Mgrafo
{
	private:
	    
		int len;
		int n;
		int m;
		
		bool** M;
		H** K;
		
		int t;
		int* marche_entrate;
		int* marche_uscite;
		int* colori;
		
		int* radici;
		int current_root;
		
		int* pred;
	public:	
	
	    int return_entrata(int s)
		{
			return marche_entrate[s];
		}
		int return_uscita(int s)
		{
			return marche_uscite[s];
		}
		Mgrafo(int len)
		{
			this->len=len;
			n=m=0;
			
			M=new bool*[len];
			for(int i=0; i<len;i++) {
				M[i]=new bool[len];
				for(int j=0; j<len;j++){
					M[i][j]=false;
				}
			}
			
			K=new H*[len];
			for(int i=0; i<len;i++) K[i]=NULL;
			
			marche_entrate=new int[len];
			marche_uscite=new int[len];
			colori=new int[len];
			radici=new int[len];
			pred=new int[len];
		}
		
		int find_index(H x) //trovare indice di x(se c'è)
		{
			for(int i=0; i<n ; i++)
			{
				if(*K[i]==x) return i;
			}
			return -1;
		}
		
		void addNode(H x)
		{
			int i=find_index(x);
			if(n==len) return;
			if(i>=0) return;
			K[n]=new H(x);
			n++;
		}
		
		void addEdge(H x,H y)
		{
			int i=find_index(x);
			int j=find_index(y);
			
			if(i<0 || j<0) return;
			if(!M[i][j])
			{
				M[i][j]=true;
				m++;
			}
			return;
		}
		
		void DFSvisit(int s)
		{
			int W=0;
			int G=1;
			int B=2;
			colori[s]=G;
			radici[s]=current_root;
			
			marche_entrate[s]=t++;
			
			for(int i=0; i<n;i++)
			{
				if(M[s][i])
				{
					if(colori[i]==W)
					{
						pred[i]=s;
						DFSvisit(i);
					}
				}
			}
			
			marche_uscite[s]=t++;
			colori[s]=B;
		}
		
		void DFS()
		{
			t=0;
			int W=0;
			for(int i=0; i<n;i++)
			{
				colori[i]=W;
				pred[i]=-1;
			}
			
			for(int i=0; i<n;i++)
			{
				if(colori[i]==W)
				{
					current_root=i;
					DFSvisit(i);
				}
			}
		}
		
		void print(ofstream & outfile)
		{
			DFS();
			for(int i=0; i<n;i++)
			{
				H e=*K[i];
				outfile<<"(" <<e<<" "<<marche_entrate[i]<<" "<<marche_uscite[i]<<") ";
			}
			outfile<<endl;
		}
		
		void print_mat()
		{
			for(int i=0; i<len;i++)
			{
				for(int j=0; j<len;j++)
					cout<<M[i][j]<<" ";
				cout<<endl;
			}
		}
	
};





int main()
{
	fstream miofile("input.txt",fstream::in);
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
		//	gr.print_mat();
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
		//	gr.print_mat();
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
			gr.print(outfile);
		}
		
	
	}
	return 0;
}




















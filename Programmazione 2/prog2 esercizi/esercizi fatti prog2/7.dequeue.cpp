#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

template<class H> class Coda
{
	private:
	    H* vettore;
		int fine;
		int testa;
		int lung;
		
	public:
	    Coda(int dim)  {lung=dim; fine=-1; testa=-1; vettore=new H[lung];}
		
		void enqueue(H dato)
		{
			fine=(fine+1)%lung;
			vettore[fine]=dato;
			
			if(testa==-1)
			{
				testa++;
			}
		}
		
		H dequeue()
		{
			H dato_uscita=vettore[testa];
			testa=(testa+1)%lung;
			
			if((testa-1)%lung==fine)
			{
				testa=-1;
				fine=-1;
			}
			
			return dato_uscita;
		}
		
		void stampa(ofstream & f)  //ricordarsi & con ofstream
		{
			int i=testa;
			while(i!=fine)
			{
				H dato=vettore[i];
				i=(i+1)%lung;
				f<<dato<<" ";
			}
			f<<vettore[i]<<endl;
		}
	
};



int main()
{
	fstream miofile("input.txt" , fstream::in);
	ofstream outfile("output.txt");
	
	for(int riga=0; riga<100; riga++)
	{
		string tipo;
		miofile>>tipo;
		
		bool tipo_int=false;
		if(tipo=="int")
			tipo_int=true;
		
		bool tipo_double=false;
		if(tipo=="double")
			tipo_double=true;
		
		bool tipo_bool=false;
		if(tipo=="bool")
			tipo_bool=true;
		
		bool tipo_char=false;
		if(tipo=="char")
			tipo_char=true;
		
		int dim;
		miofile>>dim;
		
		if(tipo_int)
		{
			Coda<int> stack(dim);
			int i=0;
			for(int i=0; i<dim ; i++)
			{
				string op;
				miofile>>op;
				
				if(op[0]=='i')
				{
					string x=op.substr(1,op.length()-1);
					int dat_n;
					stringstream ss;
					ss<<x;
					ss>>dat_n;
					stack.enqueue(dat_n);
				}
				else
				{
					stack.dequeue();
				}
			}
			
			stack.stampa(outfile);
		}
		
		if(tipo_double)
		{
			Coda<double> stack(dim);
			int i=0;
			for(int i=0; i<dim ; i++)
			{
				string op;
				miofile>>op;
				
				if(op[0]=='i')
				{
					string x=op.substr(1,op.length()-1);
					double dat_n;
					stringstream ss;
					ss<<x;
					ss>>dat_n;
					stack.enqueue(dat_n);
				}
				else
				{
					stack.dequeue();
				}
			}
			
			stack.stampa(outfile);
		}
		
		if(tipo_char)
		{
			Coda<char> stack(dim);
			int i=0;
			for(int i=0; i<dim ; i++)
			{
				string op;
				miofile>>op;
				
				if(op[0]=='i')
				{
					string x=op.substr(1,op.length()-1);
					char dat_n;
					stringstream ss;
					ss<<x;
					ss>>dat_n;
					stack.enqueue(dat_n);
				}
				else
				{
					stack.dequeue();
				}
			}
			
			stack.stampa(outfile);
		}
		
		if(tipo_bool)
		{
			Coda<bool> stack(dim);
			int i=0;
			for(int i=0; i<dim ; i++)
			{
				string op;
				miofile>>op;
				
				if(op[0]=='i')
				{
					string x=op.substr(1,op.length()-1);
					bool dat_n;
					stringstream ss;
					ss<<x;
					ss>>dat_n;
					stack.enqueue(dat_n);
				}
				else
				{
					stack.dequeue();
				}
			}
			
			stack.stampa(outfile);
		}
		
	}
	miofile.close();
	outfile.close();
	return 0;
}
	
	

















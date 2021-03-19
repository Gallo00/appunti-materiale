#include <iostream>
#include <fstream>
using namespace std;


template <class H>
class Coda
{
	private:
	    int lung;
	    H* vettore;
	    int testa;
	    int fine;
		
	public:
	    Coda(int dim)  {lung=dim ; vettore=new H[lung]; testa=-1; fine=-1; }
		
		void enqueue(H dato)
		{
			if(!((fine+1)%lung==testa))
			{
			fine=(fine+1) % lung;   //array "circolare"
			vettore[fine]=dato;
			if(testa==-1) testa++;
			}
		}
		
		void stampa(ofstream & f)
		{
			if(!((testa+1)%lung==fine))
			{
			int i=testa;
			while(i!=fine)
			{
				f<<vettore[i]<<" ";
				i=(i+1)%lung;
			}
			f<<vettore[i]<<endl;
			}
			
		}

};



int main()
{
	fstream miofile("input.txt" , fstream::in);
	ofstream outfile("output.txt");
	
	for(int riga=0; riga<3; riga++)
	{
		string tipo;
		miofile>>tipo;
		
		bool tipo_int=false;
		if(tipo=="int")
			tipo_int=true;
		
		bool tipo_double=false;
		if(tipo=="double")
			tipo_double=true;
		
		bool tipo_char=false;
		if(tipo=="char")
			tipo_char=true;
		
		bool tipo_bool=false;
		if(tipo=="bool")
			tipo_bool=true;
		
		int dati;
		miofile>>dati;
		
		if(tipo_int)
		{
			Coda<int> stack(dati);
			
			for(int i=0; i<dati ; i++)
			{
				int dat_n;
				miofile>>dat_n;
				stack.enqueue(dat_n);
			}
			
			stack.stampa(outfile);
        }
		
		if(tipo_double)
		{
			Coda<double> stack(dati);
			
			for(int i=0; i<dati ; i++)
			{
				double dat_n;
				miofile>>dat_n;
				stack.enqueue(dat_n);
			}
			
			stack.stampa(outfile);
        }


        if(tipo_char)
		{
			Coda<char> stack(dati);
			
			for(int i=0; i<dati ; i++)
			{
				char dat_n;
				miofile>>dat_n;
				stack.enqueue(dat_n);
			}
			
			stack.stampa(outfile);
        }

        if(tipo_bool)
		{
			Coda<bool> stack(dati);
			
			for(int i=0; i<dati ; i++)
			{
				bool dat_n;
				miofile>>dat_n;
				stack.enqueue(dat_n);
			}
			
			stack.stampa(outfile);
        }
	}
	
	miofile.close();
	outfile.close();
}

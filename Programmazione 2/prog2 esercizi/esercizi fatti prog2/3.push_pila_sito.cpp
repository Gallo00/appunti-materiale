#include <iostream>
#include <fstream>
using namespace std;



template<class H> class Pila
{
	public:
	H* tabella;
	int lunghezza;
	int cima;
	
	
	Pila(int lung)
	{
		lunghezza=lung;
		tabella=new H[lunghezza];
		cima=-1;
	}
	
	void push(H dato_nuovo)
	{
		cima++;
		tabella[cima]=dato_nuovo;
	}
	
	int ritorna_cima()
	{
		return cima;
	}
};

int main()
{
	fstream miofile("input.txt" ,fstream::in);
	fstream outfile("output.txt" , fstream::out);
	
	for(int riga=0; riga<100 ; riga++)
	{
		string tipo;
		miofile>>tipo;
		
		bool tipo_int= (tipo=="int");
		bool tipo_bool= (tipo=="bool");
		bool tipo_double=(tipo=="double");
		bool tipo_char= (tipo=="char");
		
		int lung;
		miofile>>lung;
		
		if(tipo_int)
		{
			Pila<int> stack(lung);
			for(int i=0; i<lung; i++)
			{
				int k;
				miofile>>k;
				stack.push(k);
			}
			
			int c=stack.ritorna_cima();
			
			for(c;c>=0;c--)
			{
				int k=stack.tabella[c];
				outfile<<k<<" ";
			}
			outfile<<endl;
		}
		
		if(tipo_bool)
		{
			Pila<bool> stack(lung);
			for(int i=0; i<lung; i++)
			{
				bool k;
				miofile>>k;
				stack.push(k);
			}
			
			int c=stack.ritorna_cima();
			
			for(c;c>=0;c--)
			{
				bool k=stack.tabella[c];
				outfile<<k<<" ";
			}
			outfile<<endl;
		}
		
		if(tipo_double)
		{
			Pila<double> stack(lung);
			for(int i=0; i<lung; i++)
			{
				double k;
				miofile>>k;
				stack.push(k);
			}
			
			int c=stack.ritorna_cima();
			
			for(c;c>=0;c--)
			{
				double k=stack.tabella[c];
				outfile<<k<<" ";
			}
			outfile<<endl;
		}
		
		if(tipo_char)
		{
			Pila<char> stack(lung);
			for(int i=0; i<lung; i++)
			{
				char k;
				miofile>>k;
				stack.push(k);
			}
			
			int c=stack.ritorna_cima();
			
			for(c;c>=0;c--)
			{
				char k=stack.tabella[c];
				outfile<<k<<" ";
			}
			outfile<<endl;
		}
		
		
		
	}
	
	
}








#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;


template<class T>
class Pila
{   
private:
    int lunghezza;
    T* tabella;
    int cima;

public:
    Pila(int lungh );
    ~Pila() {delete [] tabella;}
    void Push(T);
    T Pop();
    int num_elementi();
    void visualizza();
    int leggi_lunghezza() {return lunghezza;}


};

template<class T>
Pila<T>::Pila(int lungh)
{
    lunghezza = lungh;
    tabella = new T[lunghezza];
    cima = -1;
}

template<class T>
void Pila<T>::Push(T x)
{
    if (cima<lunghezza-1)
    {
		cima++;
        tabella[cima] = x;
    }
    else
    {
        cout << "Pila Piena!\n";
    }
}

template<class T>
T Pila<T>::Pop()
{
    T elem = 0;
    if (cima>=0)
    {
        elem = tabella[cima--];
    }
    else
    {
        cout << "Pila vuota!\n";
    }
    return elem;
}

template<class T>
void Pila<T>::visualizza()
{
    for (int i = cima; i >= 0; i--)
    {
        cout << "[" << tabella[i] << "]" << endl; 
    }
} 

template<class T>
int Pila<T>::num_elementi()
{
    return (cima+1);
}


int main()
{
	
	fstream miofile("input.txt",fstream::in);
	fstream outfile("output.txt",fstream::out);
	
	
	for(int riga=0; riga<100; riga++)
	{
	string tipo;
	miofile>>tipo;
	bool tipo_bool=false;
	if(tipo=="bool")
		tipo_bool=true;
	
	bool tipo_int=false;
	if(tipo=="int")
		tipo_int=true;
	
	bool tipo_char=false;
	if(tipo=="char")
		tipo_char=true;
	
	bool tipo_double=false;
	if(tipo=="double")
		tipo_double=true;
	int x;
	miofile>>x;
	
	if(tipo_bool)
	{
		Pila<bool> stack_b(x);
	    for(int i=0; i<x; i++)
	    {
		    string op;
		    miofile>>op;
		
		    if(op[0]=='i')
		    {
			    string dat= op.substr(1,op.length()-1);
			    bool b;
			    stringstream ss;
			    ss<<dat;
			    ss>>b;
			    stack_b.Push(b);
		    }
			else
			{
				stack_b.Pop();
			}
	    }
		
		int lung=stack_b.num_elementi();
		for(int i=0; i<lung;i++)
		{
			bool k=stack_b.Pop();
			outfile<<k<<" ";
		}
		outfile<<endl;
		
	}
	
	if(tipo_int)
	{
		Pila<int> stack_b(x);
	    for(int i=0; i<x; i++)
	    {
		    string op;
		    miofile>>op;
		
		    if(op[0]=='i')
		    {
			    string dat= op.substr(1,op.length()-1);
			    int b;
			    stringstream ss;
			    ss<<dat;
			    ss>>b;
			    stack_b.Push(b);
		    }
			else
			{
				stack_b.Pop();
			}
	    }
		
		int lung=stack_b.num_elementi();
		for(int i=0; i<lung;i++)
		{
			int k=stack_b.Pop();
			outfile<<k<<" ";
		}
		outfile<<endl;
		
	}
	
	if(tipo_char)
	{
		Pila<char> stack_b(x);
	    for(int i=0; i<x; i++)
	    {
		    string op;
		    miofile>>op;
		
		    if(op[0]=='i')
		    {
			    string dat= op.substr(1,op.length()-1);
			    char b;
			    stringstream ss;
			    ss<<dat;
			    ss>>b;
			    stack_b.Push(b);
		    }
			else
			{
				stack_b.Pop();
			}
	    }
		
		int lung=stack_b.num_elementi();
		for(int i=0; i<lung;i++)
		{
			char k=stack_b.Pop();
			outfile<<k<<" ";
		}
		outfile<<endl;
		
	}
	
	if(tipo_double)
	{
		Pila<double> stack_b(x);
	    for(int i=0; i<x; i++)
	    {
		    string op;
		    miofile>>op;
		
		    if(op[0]=='i')
		    {
			    string dat= op.substr(1,op.length()-1);
			    double b;
			    stringstream ss;
			    ss<<dat;
			    ss>>b;
			    stack_b.Push(b);
		    }
			else
			{
				stack_b.Pop();
			}
	    }
		
		int lung=stack_b.num_elementi();
		for(int i=0; i<lung;i++)
		{
			double k=stack_b.Pop();
			outfile<<k<<" ";
		}
		outfile<<endl;
		
	}
	}
	return 0;
}
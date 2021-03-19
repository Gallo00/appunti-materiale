#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

template <class H> class Nodo  //lista per lo stack
{
	public:
	H val;
	Nodo<H>* succ;  
	
	Nodo(H x) {val=x; succ=NULL;}
	void assegna_successivo(H x)
	{
		Nodo<H>* nuovo=new Nodo<H>(x);
		succ=nuovo;
	}
};

template <class H> class Stack
{
	public:
	    Nodo<H>* cima;
		
		Stack(){cima=NULL;}
		
		void push(H x)
		{
			Nodo<H>* nuova_cima=new Nodo<H>(x);
			if(cima==NULL) cima=nuova_cima;
			else
			{
			    nuova_cima->succ=cima;
			    cima=nuova_cima;
			}
	    }
		H pop()
		{
			H var=cima->val;
			cima=cima->succ;
			return var;
		}
		bool stack_vuota() { return (cima==NULL); }
};

template <class H> class Coda  //array circolari
{
	public: 
	    H* arr;
		int fine;
		int inizio;
		int dim;
	
	    Coda(int dimensione)
		{
			dim=dimensione;
			arr=new H[dim];
			fine=inizio=-1;
		}
		
		void enqueue(H x)
		{
			fine=(fine+1)%dim;
			arr[fine]=x;
			if(inizio==-1) inizio++;
		}
		
		H dequeue()
		{
			H e=arr[inizio];
			inizio=(inizio+1)%dim;
			if((inizio-1)%dim==fine) {inizio=fine=-1;}
			return e;
		}
		
		void travasa(Stack<H>* st)
		{
			while(!(st->stack_vuota()))
			{
				H var=st->pop();
				enqueue(var);
			}
		}
		
		void print(ofstream & f)
		{
			int i=inizio;
			while(i!=fine)
			{
				f<<arr[i]<<" ";
				i=(i+1)%dim;
			}
			f<<arr[i]<<endl;
		}
};

int main()
{
	fstream miofile("input_travasa.txt",fstream::in);
	ofstream outfile("output.txt");
	
	for(int riga=0; riga<100; riga++)
	{
		string tipo;
		miofile>>tipo;
		
		int operazioni;
		miofile>>operazioni;
		
		if(tipo=="int")
		{
		    Stack<int>* St=new Stack<int>;
		    Coda<int> Q(operazioni);
		    for(int i=0; i<operazioni;i++)
		    {
			    string op;
			    miofile>>op;
			    if(op[0]=='p' && op[1]==':') //push
			    {
				    string a;
					a=op.substr(2,op.length()-1);
					int dato;
					stringstream ss;
					ss<<a;
					ss>>dato;
					St->push(dato);
			    }
				if(op[0]=='e')  //enqueue
				{
					string a;
					a=op.substr(2,op.length()-1);
					int dato;
					stringstream ss;
					ss<<a;
					ss>>dato;
					Q.enqueue(dato);
				}
				if(op=="dequeue")  //dequeue
				{
					Q.dequeue();
				}
				if(op=="pop")      //pop
				{ 
					St->pop();
				}
				if(op=="travasa")
				{
					Q.travasa(St);
				}
		    }
			Q.print(outfile);
		}
		
		if(tipo=="bool")
		{
		    Stack<bool>* St=new Stack<bool>;
		    Coda<bool> Q(operazioni);
		    for(int i=0; i<operazioni;i++)
		    {
			    string op;
			    miofile>>op;
			    if(op[0]=='p' && op[1]==':') //push
			    {
				    string a;
					a=op.substr(2,op.length()-1);
					bool dato;
					stringstream ss;
					ss<<a;
					ss>>dato;
					St->push(dato);
			    }
				if(op[0]=='e')  //enqueue
				{
					string a;
					a=op.substr(2,op.length()-1);
					bool dato;
					stringstream ss;
					ss<<a;
					ss>>dato;
					Q.enqueue(dato);
				}
				if(op=="dequeue")  //dequeue
				{
					Q.dequeue();
				}
				if(op=="pop")      //pop
				{ 
					St->pop();
				}
				if(op=="travasa")
				{
					Q.travasa(St);
				}
		    }
			Q.print(outfile);
		}
		
		if(tipo=="double")
		{
		    Stack<double>* St=new Stack<double>;
		    Coda<double> Q(operazioni);
		    for(int i=0; i<operazioni;i++)
		    {
			    string op;
			    miofile>>op;
			    if(op[0]=='p' && op[1]==':') //push
			    {
				    string a;
					a=op.substr(2,op.length()-1);
					double dato;
					stringstream ss;
					ss<<a;
					ss>>dato;
					St->push(dato);
			    }
				if(op[0]=='e')  //enqueue
				{
					string a;
					a=op.substr(2,op.length()-1);
					double dato;
					stringstream ss;
					ss<<a;
					ss>>dato;
					Q.enqueue(dato);
				}
				if(op=="dequeue")  //dequeue
				{
					Q.dequeue();
				}
				if(op=="pop")      //pop
				{ 
					St->pop();
				}
				if(op=="travasa")
				{
					Q.travasa(St);
				}
		    }
			Q.print(outfile);
		}
		
		if(tipo=="char")
		{
		    Stack<char>* St=new Stack<char>;
		    Coda<char> Q(operazioni);
		    for(int i=0; i<operazioni;i++)
		    {
			    string op;
			    miofile>>op;
			    if(op[0]=='p' && op[1]==':') //push
			    {
				    string a;
					a=op.substr(2,op.length()-1);
					char dato;
					stringstream ss;
					ss<<a;
					ss>>dato;
					St->push(dato);
			    }
				if(op[0]=='e')  //enqueue
				{
					string a;
					a=op.substr(2,op.length()-1);
					char dato;
					stringstream ss;
					ss<<a;
					ss>>dato;
					Q.enqueue(dato);
				}
				if(op=="dequeue")  //dequeue
				{
					Q.dequeue();
				}
				if(op=="pop")      //pop
				{ 
					St->pop();
				}
				if(op=="travasa")
				{
					Q.travasa(St);
				}
		    }
			Q.print(outfile);
		}
	}
	miofile.close();
	outfile.close();
	return 0;
}


















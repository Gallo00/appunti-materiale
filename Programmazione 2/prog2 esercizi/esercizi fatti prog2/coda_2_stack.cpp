#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;


template <class H> class Nodo
{
	public:
	H val;
	Nodo<H>* succ;
	
	Nodo(H x)       {val=x; succ=NULL;}
	void set_x(H x) {val=x;}
	Nodo<H>* return_succ()  {return succ;}
	void set_next(Nodo<H>* nuovo_succ)  {succ=nuovo_succ;}
};

template <class H> class pila
{
	
	public:
	    Nodo<H>* fine;
		
		pila() {fine=NULL;}
		H primo_elemento(){return fine->val;}
		void push(H x)
		{
			Nodo<H>* nuovo=new Nodo<H>(x);
			if(fine)
			{
				nuovo->set_next(fine);
			}
			fine=nuovo;
		}
		
		H pop()
		{
			H e=primo_elemento();
			cancella_nodo();
			return e;
		}
		
		void cancella_nodo()
		{
			if(fine)
			{
				Nodo<H>* vecchia_fine;
				vecchia_fine=fine;
				fine=fine->succ;
				delete vecchia_fine;
			}
		}
		
		bool vuota()
		{
			if(fine==NULL) return true;
			else return false;
		}
		
		void print(ofstream & f)
		{
			Nodo<H>* iter=fine;
			while(iter!=NULL)
			{
				f<<iter->val <<" ";
				iter=iter->succ;
			}
		}
	
};


template <class H> class Coda
{
	public:
	    pila<H>* stack_1;
		pila<H>* stack_2;
		
		Coda()  { stack_1=new pila<H>; stack_2=new pila<H>; }
		
		void enqueue(H x)
		{
			stack_1->push(x);
		}
		
		void dequeue()
		{
			while(!(stack_1->vuota()))
			{
				H tmp=stack_1->pop();
				stack_2->push(tmp);
			}
			
			H element=stack_2->pop();  //elemento che volevamo estrarre
			
			while(!(stack_2->vuota()))
			{
				H tmp=stack_2->pop();
				stack_1->push(tmp);
			}
		}
		
		void print(ofstream & f)
		{
			//conviene spostare elementi su stack_2 e fare la print di esso (in stile pila)
			while(!(stack_1->vuota()))
			{
				H tmp=stack_1->pop();
				stack_2->push(tmp);
			}
			stack_2->print(f);
			f<<endl;
		}
};

int main()
{
	fstream miofile("input_2stack.txt",fstream::in);
	ofstream outfile("output.txt");
	
	for(int riga=0; riga<100; riga++)
	{
		string tipo;
		miofile>>tipo;
		
		int operazioni;
		miofile>>operazioni;
		
		if(tipo=="int")
		{
			Coda<int> Q;
			for(int i=0; i<operazioni;i++)
			{
				string op;
				miofile>>op;
				if(op[0]=='i')
				{
					stringstream ss;
					string a=op.substr(1,op.length());
					ss<<a;
					int dato;
					ss>>dato;
					Q.enqueue(dato);
				}
				if(op[0]=='d')
				{
					Q.dequeue();
				}
			}
			Q.print(outfile);
		}
		
		if(tipo=="double")
		{
			Coda<double> Q;
			for(int i=0; i<operazioni;i++)
			{
				string op;
				miofile>>op;
				if(op[0]=='i')
				{
					stringstream ss;
					string a=op.substr(1,op.length());
					ss<<a;
					double dato;
					ss>>dato;
					Q.enqueue(dato);
				}
				if(op[0]=='d')
				{
					Q.dequeue();
				}
			}
			Q.print(outfile);
		}
		
		if(tipo=="bool")
		{
			Coda<bool> Q;
			for(int i=0; i<operazioni;i++)
			{
				string op;
				miofile>>op;
				if(op[0]=='i')
				{
					stringstream ss;
					string a=op.substr(1,op.length());
					ss<<a;
					bool dato;
					ss>>dato;
					Q.enqueue(dato);
				}
				if(op[0]=='d')
				{
					Q.dequeue();
				}
			}
			Q.print(outfile);
		}
		
		if(tipo=="char")
		{
			Coda<char> Q;
			for(int i=0; i<operazioni;i++)
			{
				string op;
				miofile>>op;
				if(op[0]=='i')
				{
					stringstream ss;
					string a=op.substr(1,op.length());
					ss<<a;
					char dato;
					ss>>dato;
					Q.enqueue(dato);
				}
				if(op[0]=='d')
				{
					Q.dequeue();
				}
			}
			Q.print(outfile);
		}
	}
	return 0;
}















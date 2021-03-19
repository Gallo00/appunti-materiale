

//creare una pila per mezzo di una lista semplice

#include <iostream>
using namespace std;

class Nodo
{
	/*
	private:
	    int valore;
		Nodo* succ;
	*/	
	public:
	
	    int valore;
		Nodo* succ;
		
	    Nodo(int x) {valore=x; succ=NULL;}
		~Nodo(){} // Distruttore
		void Assegna(int x) {valore=x;}
		Nodo* Successivo() {return succ;} 
		void AssegnaSuccessivo(Nodo* poi) {succ=poi;}
	
};

class Pila
{
/*	private:
	    Nodo* p;  */
	public:
	
	    Nodo* p;
		
	    Pila() {p=NULL;}
		int PrimoElemento() { if (p!=NULL) return p->valore;}
		void SvuotaPila() {p=NULL;}
	    bool PilaVuota() {return !p;}
	 	void CancellaNodo()
		{
			Nodo* pnodo;
			if(p)
			{
				pnodo=p;
				p=p->Successivo();
				delete pnodo;
			}
		}
		
		~Pila()
		{
			Nodo* pnodo;
			while(p!=NULL)
			{
				pnodo=p;
				p=p->Successivo();
				delete pnodo;
			}
		}
		
		void push(int dato)
		{
			Nodo* nuovo=new Nodo(dato);
			if(p)  //controlla che la lista non sia vuota
			{
				nuovo->AssegnaSuccessivo(p);
			}
			p=nuovo;
		}
		
		int pop()
		{
			int e=PrimoElemento();
			CancellaNodo();
			return e;
		}
		
		
		void StampaPila()
		{

	        Nodo* pnodo=p; 
	
	        if (pnodo==NULL) 
		        cout << "Lista vuota!" << endl;
	        while(pnodo!=NULL) 
			{
		        cout << pnodo->valore << endl; 
		        pnodo=pnodo->Successivo(); 
			}
		}
};


int main()
{
		Pila p; 

	p.push(5); 
	p.push(7);
	p.push(11); 
	p.StampaPila();
	cout<<endl<<endl<<endl;
	while (!p.PilaVuota())	{
		cout << p.PrimoElemento() << "\t"; 
		p.pop();
		}
	cout<<endl<<endl<<endl;
	p.push(13); 
	p.push(17); 
	p.StampaPila(); 
	p.~Pila(); 
	p.StampaPila();
	return 0;
}














#include <iostream>
using namespace std;


//lista semplice tramite template


template <class T> struct Nodo
{
	T valore;
	Nodo<T>* succ;
};


template <class T> class ls
{
	private:
	    Nodo<T>* testa;
		
	public:
	    ls()  {testa=NULL;}
		~ls();
		
		Nodo<T>* rivela_testa()  {return testa;}
		void inserimento_in_testa(T val);
		
		void stampa();
};

template <class T> ls<T>::~ls()
{
	Nodo<T>* iter=testa;
	
	while(iter!=NULL)
	{
		Nodo<T>* temp=iter->succ;
		delete iter;
		iter=temp;
	}
}


template <class T> void ls<T>::inserimento_in_testa(T val)  //creare nuova testa
{
	Nodo<T>* nuova_testa=new Nodo<T>;
	nuova_testa->valore=val;
	
	nuova_testa->succ=testa;
    testa=nuova_testa;	
}

template <class T> void ls<T>::stampa()
{
	Nodo<T>* iter=testa;
	
	while(iter!=NULL)
	{
		cout<<iter->valore<<" ";
		iter=iter->succ;
	}
	cout<<endl;
}
	
	int main()
{	
	ls<char> lista;

	lista.inserimento_in_testa(100);
	lista.inserimento_in_testa(99);
	lista.inserimento_in_testa(97);
	lista.stampa();
	cout <<endl;
	lista.inserimento_in_testa(98);
	lista.stampa();
	return 0;	
}
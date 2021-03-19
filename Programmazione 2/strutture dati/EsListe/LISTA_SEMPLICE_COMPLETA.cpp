/* 
Corso di Programmazione II (A-L), Prof. Dario Catalano 

*/
#include<iostream>
using namespace std;

struct Nodo
{
	int dato;
	Nodo* succ;
};

class Lista_semplice
{
private:
	Nodo* testa;
public:
    Lista_semplice()  { testa=NULL; }
	~Lista_semplice();
	void stampa();
	void inserisci_in_testa(int val);
	void inserisci_in_mezzo(Nodo* prec,Nodo* succ,int val);
	Nodo* ritorna_testa()  {return testa;}
	void inserimento_coda(int val);
	Nodo* ricerca(int ind);
	void rimuovi(int ind);
	
	void inserisci(int val,Nodo* prec,Nodo* succ);
};

Lista_semplice::~Lista_semplice()
{
	Nodo* oggetto=(*this).testa;
	while(oggetto=NULL)
	{
		Nodo* aux=(*oggetto).succ;
		delete oggetto;
		oggetto=aux;
	}
}

void Lista_semplice::stampa()
{
	Nodo* oggetto=(*this).testa;
	while(oggetto!=NULL)
	{
		cout<<(*oggetto).dato<<" ";
		oggetto=(*oggetto).succ;
	}
	cout<<endl;
}

void Lista_semplice::inserisci_in_testa(int val)
{
	Nodo* nuovo=new Nodo;   //creiamo nuovo elemento e lo allochiamo dinamicamente
	(*nuovo).dato=val;      // settiamo dato a val
	
	
	(*nuovo).succ=(*this).testa;   //il puntatore di nuovo dovrà puntare alla testa che c'era prima
	(*this).testa=nuovo;           //la testa deve cambiare valore(si intende l'indirizzo) e adesso punterà a nuovo 

}

void Lista_semplice::inserisci_in_mezzo(Nodo* prec,Nodo* seg,int val)
{
	Nodo* nuovo=new Nodo;  //creiamo nuovo elemento e lo allochiamo dinamicamente
	(*nuovo).dato=val;     // settiamo dato a val
	
	(*prec).succ=nuovo;    //facciamo puntare il puntatore di prec a nuovo
	(*nuovo).succ=seg;     //facciamo puntare il puntatore di nuovo a seg
	
}


void Lista_semplice::inserimento_coda(int val)
{
	Nodo* nuova_coda=new Nodo;
	Nodo* iter=testa;
	
	if(testa==NULL)
	{
		(*nuova_coda).dato=val;
		(*nuova_coda).succ=NULL;
		testa=nuova_coda;
    }
	else
	{
		while((*iter).succ!=NULL)
			iter=(*iter).succ;
		
		(*nuova_coda).dato=val;
		(*nuova_coda).succ=NULL;
		(*iter).succ=nuova_coda;
	}
	
}

Nodo* Lista_semplice::ricerca(int ind)
{
	Nodo* p;
	for(p=testa; p!=NULL ; p=(*p).succ)
	{
		if((*p).dato==ind)
		{
			return p;
		}
	}
	return NULL;
}

void Lista_semplice::rimuovi(int ind)
{
	if(testa==NULL)
		cout<<"lista vuota"<<endl;
    else
	{
		Nodo* prec;
		Nodo* current;
		
		if((*testa).dato==ind)
		{
			prec=testa;
			testa=(*testa).succ;
			delete prec;
		}
		else
		{
			prec=testa;   //lo uso per conservare il puntatore precedente all'eventuale current che troviamo
			current=(*testa).succ;
			
			while(current!=NULL && (*current).dato!=ind)
			{
				prec=(*prec).succ;
				current=(*current).succ;
			}
			
			if(current!=NULL)
			{
				(*prec).succ=(*current).succ;
				delete current;
			}
			else
			{
				cout<<"hai provato ad eliminare un elemento non presente"<<endl;
			}
		}
	}
}
	

void Lista_semplice::inserisci(int val,Nodo* prec,Nodo* succe)
{
	
    if(testa==NULL)
	{
		cout<<"inserimento in testa(lista vuota)"<<endl;
		Nodo* nuovo=new Nodo;
		(*nuovo).dato=val;
		(*nuovo).succ=NULL;
		testa=nuovo;
	}
	else 	
    {
		if(prec==NULL && succe==NULL)
			cout<<"errore, testa non è NULL e non hai segnalato dove inserire l'elemento"<<endl;
		else
	    {
		    if(succe==NULL)
		    {
			    cout<<"inserimento in coda"<<endl;
			    Nodo* nuovo=new Nodo;
			   (*nuovo).dato=val;
			   (*nuovo).succ=NULL;
			   (*prec).succ=nuovo;
		    }
		    else
		    {
		        if(prec==NULL)
		        {
			        cout<<"inserimento in testa con lista non vuota"<<endl;
			        Nodo* nuovo=new Nodo;
			        (*nuovo).dato=val;
			        (*nuovo).succ=(*this).testa;
			        (*this).testa=nuovo;
		        }
			    else
			    {
				    cout<<"inserimento in mezzo a due"<<endl;
				    Nodo* nuovo=new Nodo;
				    (*nuovo).dato=val;
				    (*prec).succ=nuovo;
				    (*nuovo).succ=succe;
			    }
		    }
	    }
	}

}

int main()
{
	
	Lista_semplice l;
	int i=0;
	while(i<10)
	{
	    l.inserisci_in_testa(i);
	    i++;
	}
	
	l.stampa();
	Nodo* p=l.ritorna_testa();
	cout<<"vogliamo ora porre un valore dopo il 5" <<endl;
	
	while((*p).dato!=5  &&  p!=NULL)
		p=(*p).succ;
	
	if(p!=NULL)
	{
		cout<<"digita il valore che vuoi inserire"<<endl;
		int a;
		cin>>a;
	    l.inserisci_in_mezzo(p,(*p).succ,a);
	}
	
	l.stampa();
	
	int a=20;
	l.inserimento_coda(a);
	l.stampa();
	
	int b;
	cout<<"inserisci chiave"<<endl;
	cin>>b;
	
	Nodo* ric_b=l.ricerca(b);
	cout<<(*ric_b).dato;
	
	int c;
	cout<<"cosa vuoi rimuovere?"<<endl;
	cin>>c;
	
	l.rimuovi(c);
	l.stampa();
	
	
	cout<<"reinseriamo "<<c<<" usando la funzione 'inserisci' completa,lo mettiamo tra "<<b <<" e il successivo di "<<b<<endl;
	l.inserisci(c,ric_b,(*ric_b).succ);  //inserimento in mezzo a 2
	l.stampa();
	
	
	Lista_semplice l_2;
	Nodo* k=l_2.ritorna_testa();
	l_2.inserisci(5,k,NULL);          //inserimento in testa con lista vuota
	l_2.stampa();
	
	k=l_2.ritorna_testa();
	l_2.inserisci(10,k,(*k).succ);    //inserimento in coda
	l_2.stampa();
	
	l_2.inserisci(8,NULL,k);      //inserimento testa lista non vuota
	l_2.stampa();
	
	l_2.inserisci(99,NULL,NULL);  //errore
	l_2.stampa();
	
	
	
	
}








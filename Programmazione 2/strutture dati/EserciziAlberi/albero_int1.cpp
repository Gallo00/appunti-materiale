#include <iostream>
using namespace std;



struct Nodo
{
	int val;
	Nodo* padre;
	Nodo* sx;
	Nodo* dx;
};


class Albero
{
	private:
	    Nodo* radice;
		int altezza(Nodo* t);
	public:
	    Albero()  {radice=NULL;}
		void inserimento(int dato);
		void pre_order(Nodo* p);
		void in_order(Nodo* p);
		void post_order(Nodo* p);
		
		void inorder_iterativa();
		
		
		Nodo* ricerca(int x);
		Nodo* Minimo(Nodo* p); //trova il minimo nel sottoalbero con radice p
		Nodo* successore(Nodo* p);
	    int calcolo_altezza() {return altezza(radice);}
		
		void cancella(Nodo* z);
		void trapianta(Nodo* u, Nodo* v);
		
		
		void stampa();
	
};


//per poter implementare la inorder_iterativa ci serve una struttura dati di supporto, la pila
/*************************************************   PILA   **************************************************************/
struct Nodo_pila
{
	Nodo* item;  //il nodo della pila contiene il puntatore a un nodo dell'albero
	Nodo_pila* succ;  //contiene il puntatore all'elemento successivo 
};

class Pila
{
	private:
	    Nodo_pila* p;
	
	public:
	    Pila() {p=NULL;}
		bool pila_vuota() {return !p;}
		Nodo* PrimoElemento() { if (p!=NULL) return p->item;}
		void CancellaNodo()
        {	
		    Nodo_pila* pnodo; 
 	        if (p) 
	        {
 		        pnodo=p; 
 		        p=p->succ; 
 		        delete pnodo; 
 	        }
        }
		void push(Nodo* x)
		{
			Nodo_pila* aux=new Nodo_pila;
			aux->item=x;
			
			if(p) aux->succ=p;
			else aux->succ=NULL;
			
			p=aux;
		}
		
		Nodo* pop()
		{
			Nodo* e;
			e=PrimoElemento();
			CancellaNodo();
			return e;
		}
		
		~Pila() 
		{
	        Nodo_pila* pnodo; 
	
	        while(p!=0)	
		    {
		        pnodo=p; 
		        p=p->succ;
		        delete pnodo; 
		    }
        }

};

/*************************************************   PILA   **************************************************************/


void Albero::inserimento(int dato)
{
	Nodo* nuovo=new Nodo;
	nuovo->val=dato;
	nuovo->sx = nuovo->dx = NULL;
	
	Nodo* x=radice;  //è un iter
	Nodo* y=NULL;   //y serve per tenere il valore di x
	
	while(x!=NULL)
	{
		y=x;
		if(dato<x->val)
		{
			x=x->sx;
		}
		else
		{
			x=x->dx;
		}
	}
	
	nuovo->padre=y;
	if(y==NULL)
	{
		radice=nuovo;
	}
	else if(dato<y->val)
	{
		y->sx=nuovo;
	}
	else
	{
		y->dx=nuovo;
	}
}


void Albero::pre_order(Nodo* p)
{
	if(p!=NULL)
	{
		cout<<p->val<<" ";
		pre_order(p->sx);
		pre_order(p->dx);
	//	cout<<endl;
	}
}

void Albero::in_order(Nodo* p)
{
	if(p!=NULL)
	{
		in_order(p->sx);
		cout<<p->val<<" ";
		in_order(p->dx);
	//	cout<<endl;
	}
}

void Albero::post_order(Nodo* p)
{
	if(p!=NULL)
	{
		post_order(p->sx);
		post_order(p->dx);
		cout<<p->val<<" ";
	//	cout<<endl;
	}
}

//INORDER ITERATIVA, SFRUTTA SIA L'ALBERO CHE LA PILA *****************************************************/
void Albero::inorder_iterativa()
{
	cout<<"visita inorder_iterativa"<<endl;
	Pila stack;
	Nodo* corrente=radice;
	bool done=false; //flag
	
	while(!done)
	{
		if(corrente)
		{
			stack.push(corrente);    //se corrente non è null lo metto nello stack e itero facendo diventare corrente il suo sx
			corrente=corrente->sx;
		}
		else if(stack.pila_vuota())
		{
			done=true;               //se arrivo a un punto in cui lo stack è vuoto ho finito(non succederà alla prima iterazione, dato che scatterà il then                         // scatterà il than
		}
		else
		{
			corrente=stack.pop();    // se la pila non è vuota e sono arrivato iterando a sinistra un corrente null allora faccio pop e mi butto a destra
			cout<<corrente->val<<" ";    // questo significa che ho finito di salvare in pila il ramo sinistro quindi faccio cout  
			corrente=corrente->dx;   //passo al "parente" destro più vicino
		}		
	}
	cout<<endl;
}

//INORDER ITERATIVA **************************************************************/





void Albero::stampa()
{
	cout << "Vista Preorder: "<<endl;
	pre_order(radice); 
	cout << endl; 
	cout << "Vista Inorder: "<<endl;
	in_order(radice); 
	cout << endl; 
	cout << "Vista Postorder: "<<endl;
	post_order(radice); 
	cout << endl;
	
}

Nodo* Albero::ricerca(int x)
{
	Nodo* iter=radice;
	while((iter!=NULL) && (x!=iter->val))
	{
		if(x < iter->val) iter=iter->sx;
		else iter=iter->dx;
	}
	return iter;
}

Nodo* Albero::Minimo(Nodo* p)
{
	Nodo* min=p;
	while(min->sx != NULL)
		min=min->sx;
	
	return min;
}

void Albero::trapianta(Nodo* u,Nodo* v)
{
	if(u->padre==NULL) radice=v;
	else if(u==u->padre->sx) u->padre->sx=v;
	else u->padre->dx=v;
	
	if(v!=NULL)
		v->padre=u->padre;
}

void Albero::cancella(Nodo* z)
{
	Nodo* y;
	
	if(z->sx==NULL) trapianta(z,z->dx);
	else if(z->dx==NULL) trapianta (z,z->sx);
	else
	{
		y=Minimo(z->dx);
		if(y->padre!=z)
		{
			trapianta(y,y->dx);
			y->dx=z->dx;
			y->dx->padre=y;
		}
		trapianta(z,y);
		y->sx=z->sx;
		y->sx->padre=y;
	}
	delete z;
}

Nodo* Albero:: successore(Nodo* p)
{
	if(p->dx!=NULL) return Minimo(p->dx);
	else
	{
		Nodo* y=p->padre;
		while((y!=NULL) && (p==y->dx))
		{
			p=y;
			y=y->padre;
		}
		return y;
	}
}

int Albero::altezza(Nodo* t)
{
	if(t==NULL) return -1;
	
	int sin=altezza(t->sx);
	int des=altezza(t->dx);
	int max;
	
	if(sin<des) max=des;
	else max=sin;
	return 1 + max;
}

int main()
{
	
	Albero a;
	
	a.inserimento(3);
	a.inserimento(6);
	a.inserimento(12);
	a.inserimento(1);
	a.inserimento(4);
	a.inserimento(50);
	a.inserimento(7);
	a.stampa();
	cout<<endl;
	cout<<"altezza="<<a.calcolo_altezza()<<endl;
	Nodo* p=a.ricerca(12);
	Nodo* succ_p=a.successore(p);
	cout<<"succ di p="<<succ_p->val<<endl;
	a.cancella(p);
	cout<<"altezza="<<a.calcolo_altezza()<<endl;
	a.stampa();
	cout<<endl;
	
	a.inorder_iterativa();
	cout<<endl;
	
	
	return 0;

}



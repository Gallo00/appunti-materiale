#include <iostream>
using namespace std;


class elemento{
	
public:
    int dato;
	elemento* succ;   /*le informazioni contenute in un elemento devono essere il dato, e un 
	                    puntatore che ci consente di 
	                    prendere l'elemento successivo  */
					  
	elemento(elemento* n,int d) : succ(n),dato(d)  {}
};



void stampa(elemento* p)
{
	while(p!=NULL)
	{
		cout<<(*p).dato<<" ";
		p=(*p).succ;
	}
	cout<<endl;
}

int main()
{
	elemento* a=NULL;
	a=new elemento(a,1);
	a=new elemento(a,2);
	a=new elemento(a,5);
	a=new elemento(a,3);
	
	stampa(a);
	return 0;
	
}
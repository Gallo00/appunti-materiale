#include <iostream>
#include <cstdlib>
#include <typeinfo>   //TYPEID
#define DIM 50
using namespace std;


class A
{
	
	short len;     //attributi PRIVATE
	int * arr;
	
	public:
		A(short m, int a, int b);       //costruttore
		virtual double func() const =0;                //funzione virtuale pura,nessuna definizione in A
		
		short getLen() const;           //permette di "acchiappare" len, dichiarare const dato che non deve modificare nulla
		int & operator[](const int);   //simile a get(short i) però questo permette di modificare il numero


	    
	protected:
	
		double get(short i) const;   //get(i)   dichiarare const dato che non deve modificare nulla

};


A::A(short m,int a,int b)
{
	len=m;
	arr=new int[len];
	for(int i=0;i<len;i++)
	{
		arr[i]=rand()%(b-a+1)+a;  //numero da "a" a "b"
	}
}


double  A::get(short i) const
{
	return arr[i % len];   //?
}


short A::getLen() const
{
	return len;
}


int & A::operator [] (const int indice){

       if(indice<0 || indice > getLen())
        {
            return arr[indice % getLen()];
        }
        else
        {
        	return arr[indice];
		}
 }







//end class A


//start class B
class B : public A  //B eredita i metodi di A così come sono
{
	double p;
	
	public:
	
		B(short m , int y, int z , double x);
		double func() const;  //fare attenzione alle funzioni, se non modificano nulla meglio mettere const
		
	    friend  ostream & operator <<(ostream & o,const B& b);	//OSTREAM, solitamente questa funzione è opportuno dichiararla friend nella
//	                                                                       classe poicè sarà di solito necessario utilizzare un oggetto 
//                                                                         nella definizione (l'oggetto sarebbe b)
    
		
};



B::B(short m , int y , int z , double x): A(m,y,z) , p{x}  {}


double B::func() const
{
    	
    	
    double min=get(0);
    double max=get(0);
    for(int i=1; i<getLen();i++)
        {
        	if(min>get(i))
        	 {
        		min=get(i);
			 } 
			
			if(max<get(i))
			 {
				max=get(i);
			 }
		}
		
		if(min==0 && max==0)
		{
		return p;
	    }
	else{
	
		return ((min/max)+p);
	
        }
		
		
		
}
    
    ostream & operator << (ostream & o, const B&b){      //rivedere
    o << "1B, arr=[ ";
    for (int i=0; i < b.getLen(); i++){
        o << b.get(i) << " ";
    } 
    o << "], p=" << b.p << ", func()=" << b.func();
    return o;
}
//end class B




//start class C
class C : public A
{
	char t;
	
	public:
		C(short n,char c,int aa,int bb); //: A(n,aa,bb) , t{c} {}
		
		double func() const;
		string g(char c,short k);
		
		friend ostream & operator <<(ostream & o,const C&c);   //OSTREAM, stesso discorso per ostream di B
	
};


C::C(short n,char c ,int aa , int bb): A(n,aa,bb) , t{c} {}


double C::func() const  
{
	double somma=0;
	for(int j=0; j<getLen(); j++)
	{
		somma=somma+get(j);
	}
	return (somma/getLen());
}



string C::g(char c, short k)
{
	char stringa[2*k];
	int i=0;
	while(i<2*k)
	{
		stringa[i]=this->t;
		stringa[i+1]=c;
		i=i+2;
	}
	return stringa;
}



ostream& operator << (ostream & o, const C&c){
    o << "1C, arr=[ ";
    for (int i=0; i < c.getLen(); i++){
        o << c.get(i) << " ";
    } 
    o << "], t=" << c.t << ", func()=" << c.func();
    return o;
}

/***************************************************************************************************************/

//main


int main()
{
   
        

    A* vett[50];        //aggiunto io, non c'era nel codice
    srand(111222333);     


      for(int i=0; i<DIM; i++){
	short n=1+rand()%10;
	if(rand()%2==0)
	  vett[i]= new B(n, rand()%5+1, rand()%11+10, (double) rand()/(RAND_MAX));
	else
	  vett[i]= new C(n, (char) (rand()%('z' - 'a' + 1) + 'a'), rand()%5+1, rand()%11+10);
      }
 
      
    
/***************************************************************************************************************/
    
    B* ptr_b;                         //verifica operatore <<
    C* ptr_c;
   
    for(int i=0; i<DIM; i++)
	{
        cout << i+1 << ") ";
        ptr_b = dynamic_cast<B*>(vett[i]);   //necessario fare un downcasting,poichè il tipo è A*, noi abbiamo i metodi operator <<
        if    (ptr_b)                        //    per le classi B e C che possono però essere ottenute tramite questo strumento
		{
		cout << *ptr_b << endl;
	    }
        else{
            ptr_c = dynamic_cast<C*>(vett[i]);
            if    (ptr_c){
			
			 cout << *ptr_c << endl;
		}
        }
    }
    
    
    
/***************************************************************************************************************/    
    
    
    cout<<endl;                    
    double somma=0;                       //calcolare la media di func() di ogni oggetto,nulla di ficcile func() è una virtuale(pura) in A
//                                               e definita in B e C sue sottoclassi      
	for(int i=0; i<DIM;i++)
      {
      	
      	somma=somma+((*vett[i]).func());   
 //     	cout<<somma<<endl;
	  }
   
    double media=somma/50;
    cout<<media<<endl;
      
      
      
      
/***************************************************************************************************************/      
      
      
      
      
    C* ptr_2c;                                 //calcolo stringhe elevate a k   
    int c=0;
    for(int i=0; i<DIM && c<3 ; i++)
	{
    	
        ptr_2c = dynamic_cast<C*>(vett[i]);
        if(ptr_2c)
		{
			
            c++;
            cout <<ptr_2c->g('h', 2) << endl;
        
        }
    }
    
   
   
   
   
/***************************************************************************************************************/   
   
   
   
    
    cout<<(*vett[4])[2]<<endl;      //verifica operator []  (modifica di un elemento dell'oggetto)
    (*vett[4])[2]=5;
    cout<<(*vett[4])[2];
    
    
      
 /***************************************************************************************************************/ 
	

      
      
      
      
      
      
      
      
      
      
      
      
      
}





































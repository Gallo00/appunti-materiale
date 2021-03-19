#include <iostream>
#include <cstdlib>
#define DIM 50
#include <typeinfo>

using namespace std;


class A
{
	char* s;
	short len;
	
	public:
		A(short m);
		
		virtual double elab(short a)=0;
        short getLen();
        
        virtual ostream & put(ostream & ss)
        {
        	ss<<typeid(*this).name() <<" s=[";
        	for(int i=0; i<(*this).getLen();i++)
        	{
        		ss<< (*this).get(i) <<" ";
        		
			}
			ss<<"]";
			return ss;
		}
        protected:
        	char get(short i);
	
	
};

A::A(short m)
{
	len=m;
	s= new char[len];
	
	for(int i=0; i<len;i++)
	{
		s[i]= (rand()%('z' - 'a' + 1) + 'a');
	}
}


short A::getLen()
{
	return len;
}


char A::get(short i)
{
	return s[i % len];
}


class B: public A
{
	int p;
	
	public:
		B(short m,int x);
		
		double elab(short a);
		B  operator ++(int o);   //operatore postfisso;
		
		ostream & put(ostream & ss)
		{
			return A::put(ss) <<" p="<<p <<" elab(3)="<<(*this).elab(3);
		}
//	friend ostream & operator  <<(ostream & ss, B & b );
		
		protected:
			bool test();
			
};


B::B(short m,int x): A(m), p{x}  {}

double B::elab(short a)
{
	double V=0;
	double C=0;
	for(int i=0;i<getLen();i++)
	{
		switch(get(i))
		{
			case 'a':
			case 'e':
			case 'i':
			case 'o':
			case 'u':
				V++;
				break;
			default:
				C++;
				break;
		}
	}
 return V/(C+1);
}

bool B::test()
{
	int c=0;
	for(int i=0;i<4;i++)
	{
			switch(get(i))
		{
			case 'a':
			case 'e':
			case 'i':
			case 'o':
			case 'u':
				c++;
				break;
		}
	}
	
	if(c>0)
	{
		return true;
		
	}
	else
	{
		return false;
	}
	
}

/*
ostream & operator <<(ostream & ss, B & b)
{
	ss << "1B) s= [";
	for(int i=0; i<b.getLen();i++)
	{
		ss<<b.get(i) <<" ";
	}
	ss<<"] , p="<<b.p <<" elab(3)= "<<b.elab(3);
	return ss;
}
*/
B B::operator ++(int o)
{
	
    B copia= (*this);
    p++;
    return copia;
}







class C : public A
{
	
	char x;
	
	public:
		C(short n,char c);
		
		double elab(short r);
	    string g(char c);
	    ostream & put(ostream & ss)
		{
			return A::put(ss) <<" x="<<x <<" elab(3)="<<(*this).elab(3);
		}
//	    friend ostream & operator  <<(ostream & ss, C & c );
	
	
};



C::C(short n, char c): A(n) , x{c}  {}



double C::elab(short r)
{
	double c=0;

	for(int i=r%getLen(); i<getLen();i++)
	{
		if(get(i) >= x)
		{
			c++;
		}
	}

	return c/getLen();
}

string C::g(char c)
{
  /*  char *h;
    
    h=new char[2];      //sintassi di c, fa schifo        //conviene quasi sempre fare allocazione dinamica
    h[0]=x;
    h[1]=c;
	return h;
	*/
	string s(1,c);
	string d(1,x);
	return(d+s);
}

/*
ostream & operator <<(ostream & ss, C & c)
{
	
	ss << "1C) s= [";
	for(int i=0; i<c.getLen();i++)
	{
		ss<<c.get(i) <<" ";
	}
	ss<<"] , x="<<c.x <<" elab(3)= "<<c.elab(3);
	return ss;


}

*/

ostream & operator <<(ostream & ss, A & a)
{
	return a.put(ss);
}

int main()
{
	srand(111222333);



    A* vett[50];
    for(int i=0; i<DIM; i++)
	{
	short n=1+rand()%10;
	if(rand()%2==0)
	  vett[i]= new B(n, rand()%10 + 1);
	else
	  vett[i]= new C (n, (char) (rand()%((int) 'z' - (int) 'a' + 1) + (int) 'a'));
	}
	
		//elementi di vett sono A*
		
		
		
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
	
	
	
	
	
	double somma=0;
	
	for(int i=0; i<DIM; i++)
	{
		somma=somma+ ((*vett[i]).elab(3));
	}
	
	double media= somma/DIM;
	cout<<media<<endl;
	
	
	
	
    C* ptr_2c;
    string concatenazione="";
    for(int i=0; i<DIM; i++)
    {
    	ptr_2c= dynamic_cast<C*>(vett[i]);
    	if(ptr_2c)
    	{
    		concatenazione= concatenazione + ((*ptr_2c).g('h'));
		}
	}
	
	cout<<concatenazione<<endl;
	
	
	
	//provare incremento postfisso
	B* ptr_2b= dynamic_cast<B*>(vett[0]);
	
	(*ptr_2b)++;
	cout<<(*ptr_2b);




}































#include <iostream>
#include <cstdlib>
#include <typeinfo>
#include <string>
#include <cmath>
#define DIM 50
using namespace std;

class A{
	

    short* arr;
    short len;
   
    public:
    	
	    A(short m);
	    double virtual f(short a)=0;
	    short getLen();
	    
	    virtual ostream & put(ostream & ss)
	    {
	    	ss<<typeid(*this).name() <<" arr=[";
	    	for(int i=0; i<(*this).getLen();i++)
	    	{
	    		ss<< (*this).get(i) <<" ";
			}
			ss<<"]";
			return ss;
		}
	
	protected :
		short get(short i);
   	
};

A::A(short m)
{
	len=m;
	arr=new short[len];
	
	for(int i=0; i<len; i++)
	{
		arr[i]= rand()%(10-1+1)+1;
	}
	
}


short A::getLen()
{
	return len;
}

short A::get(short i)
{
	return arr[i];
}

template <class T>
class B : public A{
	
	T x;
	
	public:
		B(short m, char c);
		double foo(short s);
		double f(short a);
		
		ostream & put(ostream & ss)
		{
			return A::put(ss) <<" x="<<x<<" f(3)="<<(*this).f(3);
		}
/*	friend ostream & operator <<(ostream & ss, B & b)
	{
		ss<< "[ ";
		for(int i=0; i<b.getLen(); i++)
		{
			ss<< b.get(i) <<" ";
		}
		ss<<"] x="<<b.x <<" f(3)= "<<b.f(3);
	} */
};

template <class T>
B<T>::B(short m, char c) : A(m)
{
	if(typeid(x)==typeid(char))
	{
		x=c;
	}
	else
	{
		for(int i=0; i<m; i++)
		{
			x= x+c;
		}
		
    }
}

template <class T>
double B<T>::foo(short s)
{
	return log(s) + sin(f(s));
}

template <class T>
double B<T>::f(short a)
{
	int i= a%getLen();
	double somma=0;
	while(i<getLen())
	{
		somma=somma+get(i);
		i++;
	}
	
	return somma/(getLen() - a%getLen());
}

class C : public A{
	int y;
	
	public:
		C(short n, int k);
		double f(short a);
		short g(short w);
		
		ostream & put(ostream & ss)
		{
			return A::put(ss) <<" y="<<y<<" f(3)="<<(*this).f(3);
		}
/*	friend ostream & operator <<(ostream & ss, C & c)
	{
		ss<< "[ ";
		for(int i=0; i<c.getLen(); i++)
		{
			ss<< c.get(i) <<" ";
		}
		ss<<"] y="<<c.y <<" f(3)= "<<c.f(3);
	}
*/	
	C& operator ++()   //prefisso   
	{
		++y;           //si incrementa ciò che si deve, per poi fare  "return *this"
		return *this;
	}
	
};

C::C(short n, int k): A(n) , y{k} {}

double C::f(short a)
{
	double r=rand()%getLen();
	
	return (a+y)/(get(r));
}

short C::g(short w)
{
	return sin(w+y);
}

ostream & operator <<(ostream & ss, A & a)
{
	return a.put(ss);
}


int main()
{
	
	srand(111222333);

    A *vett[DIM];

    for(int i=0; i<DIM; i++) 
   {
	    short n=1+rand()%10;
	    switch(rand()%3)
		 {
	        case 0: 
	        vett[i]= new C(n, rand()%10 + 1);
	        break;
	        case 1:
	        vett[i]= new B<string>(n, rand()%('z' - 'a' + 1) + 'a');
	        break;
	        case 2: 
	        vett[i]= new B<char>(n ,  rand()%('z' - 'a' + 1) + 'a');
	    }
    }
    
    
    C* ptr_c;
    B<string>* ptr_bs;
    B<char>* ptr_bc;
    
    for(int i=0; i<DIM; i++)
    {
    	ptr_c= dynamic_cast<C*>(vett[i]);
    	if(ptr_c)
    	{
    		cout<<i<<") C "<<*ptr_c<<endl;
		}
		
		ptr_bs= dynamic_cast<B<string>*>(vett[i]);
    	if(ptr_bs)
    	{
    		cout<<i<<") B<string> "<<*ptr_bs<<endl;
		}
		ptr_bc= dynamic_cast<B<char>*>(vett[i]);
    	if(ptr_bc)
    	{
    		cout<<i<<") B<char> "<<*ptr_bc<<endl;
		}
	}
    
    
    C* ptr_2c= dynamic_cast<C*>(vett[3]);
    ++(*ptr_2c);
    cout<<*ptr_2c;
    
}






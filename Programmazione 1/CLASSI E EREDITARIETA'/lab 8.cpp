#include <iostream>
#include <cstdlib>
#include <typeinfo>
#include <string>
#include <cmath>
#include <sstream>
#define DIM 50
using namespace std;

class A
{
	int* ptr;
	short len;
	
	public:
		A(short m,short k);
		virtual double f() const =0;
		int get(short i) const;
		short getLen() const;
		virtual ostream & put(ostream & ss)
		{
			ss << typeid(*this).name() <<" ptr=[";
			for(int i=0; i<(*this).getLen(); i++)
			{
				ss<<(*this).get(i)<<" ";
			}
			ss<<"]";
			return ss;
		}
		
		int & operator [](short i)
		{
			return ptr[i%len];
		}
		
};

A::A(short m, short k)
{
	len=m;
	ptr = new int[len];
	for(int i=0; i<len; i++)
	{
		ptr[i]= rand()%(k-1+1) + 1;
	}
}

int A::get(short i) const
{
	return ptr[i%len];
}

short A::getLen() const
{
	return len;
}

class B : public A
{
	double p;
	
	public:
		B(short m, short k, double y);
		double f() const;
		ostream & put(ostream & ss)
		{
			return A::put(ss) << " p="<<p<<" f()="<<(*this).f();
		}
};

B::B(short m, short k, double y) : A(m, k) , p{y} {}

double B::f() const
{
	double somma=0;
	for(int i=0; i<getLen(); i++)
	{
		if(get(i)%2==0)
		{
			somma=somma+ get(i);
		}
	}
	return somma/p;
}

class C : public A
{
	char x;
	
	public:
		C(short n, short k,char c);
		double f() const;
		string g(char c) const;
		ostream & put(ostream & ss)
		{
			return A::put(ss) << " x="<<x <<" f()="<<(*this).f();
		}
};

C::C(short n, short k, char c): A(n,k) , x{c} {}

double C::f() const
{
	double somma=0;
	double counter=0;
	for(int i=0; i<getLen(); i++)
	{
		if(get(i)%2 != 0)
		{
			somma=somma+ get(i);
			counter++;
		}
	}
	
	if(counter==0)
	{
		return 0;
	}
	else
	{
		return somma/counter;
	}
}

string C::g(char c) const
{
	stringstream ss;
	string ritorno="";
	ss<<ritorno;
	ss<<x << c;
	ss>>ritorno;
	return ritorno;
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
	short m = 1+rand()%8;
	if(rand()%2==0)
	  vett[i]= new B(n, m, rand()/(double) RAND_MAX+0.05);
	else
	  vett[i]= new C(n, m, (char) (rand()%('z' - 'a' + 1) + 'a'));
    }
    
    for(int i=0; i<DIM; i++)
    {
    	cout<<i<<")"<<(*vett[i]) <<endl;
	}
	
	double somma=0;
	for(int i=0; i<DIM ; i++)
	{
		somma=somma + (*vett[i]).f();
	}
	double media= somma/DIM;
	cout<<media<<endl;
	
	C* ptr_c;
	string stringa="";
	for(int i=0; i<DIM; i++)
	{
		ptr_c= dynamic_cast<C*>(vett[i]);
		if(ptr_c)
		{
			stringa= stringa + (*ptr_c).g('h');
		}
	}
	cout<<stringa<<endl;
	
	cout<<(*vett[2])<<endl;
	(*vett[2])[3]=50;
	cout<<(*vett[2])<<endl;
	
    
}









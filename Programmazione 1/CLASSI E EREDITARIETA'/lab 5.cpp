#include <iostream>
#include <cstdlib>
#include <typeinfo>
#include <string>
#include <cmath>
#define DIM 50

using namespace std;


class A{
	
	double* w;
	short len;
	
	public:
		A(short m);
		double virtual foo(short a) const =0;
		short getLen() const;
		
		double& operator [] (int i)
	{
		return w[i%len];
	}	
	protected:
		double get(short i) const;
		

};

A::A(short m)
{
	len=m;
	w=new double[len];
	
	for(int i=0; i<len; i++)
	{
		w[i]=(double) rand()/RAND_MAX;
	}
}

short A::getLen() const
{
	return len;
}

double A::get(short i) const
{
	return w[i%len];
}

class B : public A
{
	
	int p;
	
	public:
		B(short m, int x);
		double foo(short a) const;
		
	protected:
		double sum(short s) const;
		
	friend ostream & operator <<(ostream & ss, B & b)
	{
		ss<<" w=[ ";
		for(int i=0; i<b.getLen();i++)
		{
			ss<<b.get(i) <<" ";
		}
		ss<<"] p=" <<b.p<< " foo(3)= "<<b.foo(3);
	}
};


B::B(short m, int x) : A(m) , p{x}  {}

double B::foo(short a) const
{
	return (sum(a)/p);
}

double B::sum(short s) const
{
	double somma=0;
	for(int i=s%getLen() ; i<getLen() ; i++)
	{
	   somma=somma + get(i);	
	}
	return somma;
}

template <class T>
class C : public A
{
	T x;
	
	public:
		C(short n);
		double foo(short r) const;
		T g(T k) const;
		
		friend ostream & operator <<(ostream & ss, C & c)
	{
		ss<<" w=[ ";
		for(int i=0; i<c.getLen();i++)
		{
			ss<<c.get(i) <<" ";
		}
		ss<<"] p=" <<c.x<< " foo(3)= "<<c.foo(3);
	}
};

template <class T>
C<T>::C(short n) : A{n}
{
	if(typeid(x)==typeid(short))
	{
		x=n;
	}
	else
	{
		x= (double) log(1+ pow(sin(n),2));
	}
}

template <class T>
double C<T>::foo(short r) const
{
	return g(r);
}

template <class T>
T C<T>::g(T k) const
{
	return 2*x*(k+1);
}

int main()
{
	srand(111222333);
    A *vett[DIM];
    for(int i=0; i<DIM; i++)
	{
	short n=1+rand()%10;
	switch(rand()%3) {
	  case 0: 
	    vett[i]= new B(n, rand()%10 + 1);
	    break;
	  case 1:
	    vett[i]= new C<double>(n);
	    break;
	  case 2: 
	    vett[i]= new C<short>(n);
	}
    }    
    
    B* ptr_b;
    C<double>* ptr_cd;
    C<short>* ptr_cs;
    
    for(int i=0; i<DIM; i++)
    {
       ptr_b= dynamic_cast<B*>(vett[i]);
       if(ptr_b)
       {
       	cout<<i<<")B "<<*ptr_b<<endl;
	   }
	   
	   ptr_cd= dynamic_cast<C<double>*>(vett[i]);
       if(ptr_cd)
       {
       	cout<<i<<")C<double> "<<*ptr_cd<<endl;
	   }
	   
	   ptr_cs= dynamic_cast<C<short>*>(vett[i]);
       if(ptr_cs)
       {
       	cout<<i<<")C<short> "<<*ptr_cs<<endl;
	   }
	}
	
	double max=0;
	for(int i=0; i<DIM; i++)
    {
      if( (*vett[i]).foo(3)>max)
      {
      	max=((*vett[i]).foo(3));
	  }
	}
	
	cout<<max<<endl;
	
	C<double>* ptr_2c;
	double somma=0;
	int counter=0;
	for(int i=0; i<DIM; i++)
	{
		ptr_2c=dynamic_cast<C<double>*>(vett[i]);
		if(ptr_2c)
		{
			somma=somma + (*ptr_2c).g(5);
			counter++;
		}
	}
	
	double media= somma/counter;
	cout<<media<<endl;
	
	
	B* ptr_2b = dynamic_cast<B*>(vett[3]);
	cout<<*ptr_2b<<endl;
	
	(*ptr_2b)[2]=3;
	
	cout<<*ptr_2b;
    
	 
}

















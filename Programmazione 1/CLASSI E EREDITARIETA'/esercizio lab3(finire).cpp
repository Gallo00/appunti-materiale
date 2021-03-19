#include <iostream>
#include <cstdlib>
#include <cmath>
#include <typeinfo>
using namespace std;


class A{
	
	protected:
		double *ptr;
		short len;
		
	public:
		A(short n);
		virtual double foo(short a) const =0;   //funzione const
};

A::A(short n)
{
	len=n;
	ptr= new double[len];
	
	for(int i=0; i<len; i++)
	{
		ptr[i]= ((double)rand())/RAND_MAX;
	}
}



class B : public A
{
	
	double alpha;
	
	public:
		B(short m,double d);
		double extract(short s);
		double foo(short b) const;
};


B::B(short m,double d) : A(m) , alpha{d}  {}

double B::extract(short s)
{
	return (ptr[s%len] + alpha)/2;
}


double B::foo(short b) const
{
	
	return log(1 + (*this).extract(b)) ;
}








template <class T>
class C : public A
{
	
	private:
		T x;
		
	public:
		C(short n);
		double foo(short r) const;
		T g(T k) const;
};


template <class T>
C<T>::C(short n)
{
	if(typeid(x)==typeid(short))
	{
		x=g(n);
	}
	else
	{
		x=log(1+n);
	}

}

template <class T>
double C<T>::foo(short r) const
{
	
	return g(r*x);
	
}

template <class T>
T C<T>::g(T k) const
{
	
	return 3*k;
}

int main()
{
     cout<<"ciao";	
}





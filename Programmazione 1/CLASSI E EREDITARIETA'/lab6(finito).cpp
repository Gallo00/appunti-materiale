#include <iostream>
#include <cstdlib>
#include <typeinfo>
#include <string>
#include <cmath>
#define DIM 50
using namespace std;


class A
{
	int x;
	
	public:
		A(int m);
		virtual double v(int a) const =0;
		virtual ostream &put(ostream & ss)
		{
			ss<<typeid(*this).name() <<" x="<<x;
			return ss;
		}
		
};

A::A(int m) : x{m} {}

class B : public A
{
	int* ptr;
	int l;
	
	public:
		B(int z, int y);
		double v(int a) const;
		ostream &put(ostream & ss)
		{
			A::put(ss);
			ss<<" ptr=[";
			for(int i=0; i<l;i++)
			{
				ss << ptr[i] <<" ";
			}
			
			ss<<"]  v(50)="<<(*this).v(50);
			return ss;
		}
		
		int & operator [](int i)
		{
			return ptr[i];
		}
		
	protected:
		int sum(int t) const;
};


B::B(int z, int y) : A(z)
{
	ptr= new int[y];
	for(int i=0; i<y; i++)
	{
		ptr[i]= rand()%(100-1+1)+1;
	}
	l=y;
}

double B::v(int a) const
{
	return (l*1000)/(double)(sum(a)+1);
}

int B::sum(int t) const
{
	int somma=0;
	for(int i=0; i<l; i++)
	{
		if(ptr[i] <= t)
		{
			somma= somma+ ptr[i];
		}
	}
	
	return somma;
}


template <class T>
class C : public A
{
	T k;
	
	public:
		C(int n);
		double v(int r) const;
		T g(T w) const;
		
		ostream &put(ostream & ss)
		{
			return A::put(ss)<< " k="<<k<<" v(50)="<<(*this).v(50);
		
		}
	
};

template <class T>
C<T>::C(int n) : A(n)
{
	if(typeid(k)==typeid(int))
	{
		k=2*n;
	}
	else
	{
		k= (double) log(1 + pow(sin(n),2));
	}
}

template <class T>
double C<T>::v(int r) const
{
	return g(r);
}

template <class T>
T C<T>::g(T w) const
{
	return k*(w+1);
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
		int n=1+rand()%10;
		switch(rand()%3)
		{
			
		case 0: 
	    vett[i]= new B(n, rand()%10 + 1);
	    break;
	    case 1:
	    vett[i]= new C<int>(n);
	    break;
	    case 2: 
	    vett[i]= new C<double>(n);
	    
	    }
    }
	
//  B* ptr_b;
//    C<int>* ptr_c_int;
//    C<double>* ptr_c_double;
    
    for(int i=0; i<DIM; i++)
    {
    	cout<<i<<")"<< (*vett[i])<<endl;
	}
    
    
    double min=(*vett[0]).v(50);
    double max=(*vett[0]).v(50);
    
    for(int i=1; i<DIM; i++)
    {
    	if((*vett[i]).v(50)<min)
    	{
    		min=(*vett[i]).v(50);
		}
		
		if((*vett[i]).v(50) > max)
		{
			max= (*vett[i]).v(50);
		}
	}
	
	cout<<"max="<<max<< "  min="<<min<<endl;
	
	
	double sum=0;
	C<double>* ptr_c;
	int counter=0;
	for(int i=0; i<DIM; i++)
	{
		ptr_c= dynamic_cast<C<double>*>(vett[i]);
		if(ptr_c)
		{
			sum= sum+ (*ptr_c).g(5);
			counter++;
		}
		
	}
	double media= sum/counter;
	cout<<"media di g(5)="<<media<<endl;
	
	
	B* ptr_b;
	ptr_b= dynamic_cast<B*>(vett[2]);
	(*ptr_b)[3]=6;
	cout<<(*ptr_b)[3];
	
}






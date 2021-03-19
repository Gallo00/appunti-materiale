#include <iostream>
#include <cstdlib>
#include <cmath>
#include <typeinfo>
#define DIM 50
using namespace std;




class A{
	
	int* vec;
	short len;
	
	public:
		A(short m,int a,int b);
		double virtual foo(short a)=0;
		short getLen();
		
		virtual ostream & put(ostream &ss)
		{
			ss<<typeid(*this).name() <<" vec=[";
			for(int i=0; i<(*this).getLen(); i++)
			{
				ss<<(*this).get(i) <<" ";
			}
			ss<<"]";
			return ss;
		}
		
		int & operator ()(short i1, int i2)
		{
			int i=i1;
			int somma= get(i);
			for(int i=i1+1;i<i2+1;i++)
			{
				somma=somma + get(i);
			}
			return somma;
		}
		
	protected:
		int get(short i);	
	
	
};

A::A(short m,int a, int b) : len{m}
{
	vec= new int[m];
	
	for(int i=0; i<m; i++)
	{
		vec[i]= rand()%(b-a+1)+a;
	}
}


short A::getLen()
{
	return len;
}

int A::get(short i)
{
	return vec[i];
}


class B : public A{
	
	int p;
	
	public:
		B(short m, int x, int y);
		double foo(short a);
		
		ostream & put(ostream & ss)
		{
			return A::put(ss) <<" p="<<p <<" foo(3)="<<(*this).foo(3);
		}
		
/*	friend ostream & operator <<(ostream & ss, B & b)
	{
		ss<<"B vec= [";
		for(int i=0; i<b.getLen(); i++)
		{
			ss<<b.get(i)<<" ";
		}
		ss<<"] p="<<b.p <<" foo(3)= "<<b.foo(3);
	}
*/		
	protected:
		int prod(short s);	
};


B::B(short m, int x,int y) : A(m,x,y)
{
	
	p= get(rand()%getLen());
}

int B::prod(short s)
{
	int risultato=1;
	int i=s%getLen();
	
	while(i<getLen())
	{
		risultato = risultato * get(i);
		i++;
	}
	
	return risultato;
}

double B::foo(short a)
{
	return (double) (prod(a))/p;
}


template <class T>
class C : public A
{
	
	T x;
	
	public:
		C(short n, int a, int b);
		double foo(short r);
		T g(T k);
		
		ostream & put(ostream & ss)
		{
			return A::put(ss) <<" x="<<x <<" foo(3)="<<(*this).foo(3);
		}
		
/*	friend ostream & operator <<(ostream & ss, C & c)
	{
		ss<<" vec= [";
		for(int i=0; i<c.getLen(); i++)
		{
			ss<<c.get(i)<<" ";
		}
		ss<<"] p="<<c.x <<" foo(3)= "<<c.foo(3);
	}
*/	
};


template <class T>
C<T>::C(short n, int a,int b) : A(n,a,b)
{
	if (typeid(x)==typeid(short))
	{
		x=n;
	}
	else
	{
		x=log(1+(pow(sin(n),2)));
	}
}

template <class T>
double C<T>::foo(short r)
{
	return g(r);
}

template <class T>
T C<T>::g(T k)
{
	return 2*x*(k+1);
}


ostream & operator <<(ostream & ss, A & a)
{
	return a.put(ss);
}


int main()
{
	 srand(111222333);

      A *vett[DIM];

      for(int i=0; i<DIM; i++) {
	short n=1+rand()%10;
	switch(rand()%3) {
	  case 0: 
	    vett[i]= new B(n, rand()%5 + 1, rand()%10 + 5);
	    break;
	  case 1:
	    vett[i]= new C<double>(n, rand()%5 + 1, rand()%10 + 5);
	    break;
	  case 2: 
	    vett[i]= new C<short>(n, rand()%5 + 1, rand()%10 + 5);
	}
    }
    
    
    B* ptr_b;
    
    C<double>* ptr_c_double;
    C<short>* ptr_c_short;
    
    int i=0;
    while(i<DIM)
    {
    	ptr_b= dynamic_cast<B*>(vett[i]);
    	if(ptr_b)
    	{
    		cout<<i<<")"<<*ptr_b<<endl;
		}
		else
		{
			ptr_c_double=dynamic_cast<C<double>*>(vett[i]);
			if(ptr_c_double)
			{
				cout<<i<<")C<double> "<<*ptr_c_double<<endl;
			}
			else
			{
				ptr_c_short=dynamic_cast<C<short>*>(vett[i]);
				cout<<i<<")C<short> "<<*ptr_c_short<<endl;
			}
		}
		
		i++;
	}
	
	i=0;
	int max=0;
	 while(i<DIM)
    {
    	ptr_b= dynamic_cast<B*>(vett[i]);
    	if(ptr_b)
    	{
    		if((*ptr_b).foo(3)>max)
    		{
    			max=(*ptr_b).foo(3);
			}
		}
		else
		{
			ptr_c_double=dynamic_cast<C<double>*>(vett[i]);
			if(ptr_c_double)
			{
				if((*ptr_c_double).foo(3)>max)
    		{
    			max=(*ptr_c_double).foo(3);
			}
			}
			else
			{
				ptr_c_short=dynamic_cast<C<short>*>(vett[i]);
				if((*ptr_c_short).foo(3)>max)
    		{
    			max=(*ptr_c_short).foo(3);
			}
			}
		}
		
		i++;
	}
	
	cout<<"max di foo(3)="<<max<<endl;
	
	C<double>* ptr2c;
	int somma=0;
	double counter=0;
	for(int i=0; i<DIM; i++)
	{
		ptr2c=dynamic_cast<C<double>*>(vett[i]);
		if(ptr2c)
		{
			somma= somma + (*ptr2c).g(5);
			counter++;
		}
	}
	
	double media= somma/counter;
	cout<<"media= "<<media<<endl;
	
	
   
    cout<<(*vett[10])(4,8)<<endl;
    cout<<"ciao";
}




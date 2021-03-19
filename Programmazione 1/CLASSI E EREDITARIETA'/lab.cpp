#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <math.h>
#include <typeinfo>
#define DIM 50
using namespace std;

//srand(111222333);
class A{
	
	char* ptr;
	short len;
	
	public:
		A(short m, char c);
		virtual string elab(short a, char c) const =0;
		short getLen() const;
		
	protected:
		char get(short i) const;
			
};


A::A(short m,char c) : len{m}
{
	ptr= new char[len];
	
	for(int i=0; i<len; i++)
	{
		ptr[i]= rand()%(c - 'a'+1) + 'a';
	}

}

short A::getLen() const
{
	return len;
}


char A::get(short i) const
{
	return ptr[i%len];
}



class B : public A
{
	
	double x;
	
	public:
		B(short m, double y, char c);
		double foo(short s);
		string elab(short a, char c) const;
		
	friend ostream & operator<<(ostream & ss,const  B & b)
	{
		
	ss << "B ptr =[ ";
	for(short i=0; i < b.getLen(); i++)
	{
		ss << b.get(i) <<" ";
//		cout<<"in B get(i)= "<<b.get(i);
	}
	
	ss<< "]" <<"x= "<<b.x << " elab= "<<b.elab(5, 'z');
	return ss;
}

	
	
};

B::B(short m, double y, char c) : A(m , c) , x{y} {}

double B::foo(short s)
{
   return ((sin(x+s))/(log(x+s)));	
} 


string B::elab(short a, char c) const
{

	int counter=0;
	int i=0;
	while(i<getLen())
	{
		if(fabs(get(i)-c)<=a)
		{
			counter++;
		}
		i++;
	}
	
	i=0;
	string stringa="";
	while(i<getLen())
	{
		if(fabs(get(i)-c)<=a)
		{
			stringa=stringa + get(i);
			
		}
		i++;
	}
	
	return stringa;
}





template <typename T>
class C : public A
{
	T y;
	
	public:
		C(short n, double k, char c);
		string elab(short a, char c) const;
		double g(short w);
	
	
		
friend ostream & operator<<(ostream & ss,const  C & c)
	{
		
	if(typeid(c)==typeid(C<double>))
	{
		ss<< "C<double> ptr[";
	}
	else
	{
		ss<< "C<short> ptr[";
	}
	
	
	for(short i=0; i < c.getLen(); i++)
	{
		ss << c.get(i) <<" ";
	}
	
	ss<< "]" <<"y= "<<c.y <<" elab= "<< c.elab(5, 'z');
	return ss;
}

	
	
};


template <typename T>
C<T>::C(short n, double k, char c) : A(n , c) 
{
    if(typeid(T)==typeid(short))
    {
        y=(short) round(100*k);
	}
	else
	{
		y=(double)k;
	}
    
}



template <typename T>
string C<T>::elab(short a, char c) const
{
	if(getLen() >= a)
	{
		string giacomo="";
		for(int i=0; i< a; i++);
		{
			giacomo=giacomo + c;
		}
		return giacomo;
	}
	else
	{
		string giacomo="";
		for(int i=0; i< getLen(); i++)
		{
			giacomo= giacomo + get(i);
		}
		
		return giacomo;
	}
}

template <typename T>
double C<T>::g(short w)
{
	return sin(w+y);
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
        vett[i]= new B(n, (double) rand()/RAND_MAX, rand()%('z' - 'a' + 1) + 'a');
	break;
      case 1:
	    vett[i]= new C<double>(n, (double) rand()/RAND_MAX, rand()%('z' - 'a' + 1) + 'a');
	break;
      case 2:
     	vett[i]= new C<short>(n, (double) rand()/RAND_MAX,  rand()%('z' - 'a' + 1) + 'a');
    }
}

B* ptr_b;
C<double>* ptr_double_c;
C<short>* ptr_short_c;

//ptr_b= dynamic_cast<B*>(vett[1]);
//cout<<*ptr_b;


for(int i=0; i<DIM; i++)
{

	ptr_b= dynamic_cast<B*>(vett[i]);
	if(ptr_b)
	{
		cout<<i<<") "<<*ptr_b<<endl;
		
	}
	else
	{
		ptr_double_c= dynamic_cast<C<double>*>(vett[i]);
		if(ptr_double_c)
		{
			cout<<i<<") "<< *ptr_double_c <<endl;
		}
		else
		{
			ptr_short_c= dynamic_cast<C<short>*>(vett[i]);
			if(ptr_short_c)
			{
				cout<<i<<") "<<*ptr_short_c<<endl;
			}
		}
	}

}







}







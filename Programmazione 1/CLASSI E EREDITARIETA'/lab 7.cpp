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
	char* base;
	short len;
	
	public:
		A(short m);
		virtual string extract(short x) const =0;
		
		short getLen() const;
		
		string operator ()(int i1, int i2)
		{
			stringstream ss;
			string stringa="";
			ss<<stringa;
			if(i1<len && i2<=len && i1<=i2) 
			{
				for(int i=i1; i<i2; i++)
				{
					ss<< base[i];
				}
				ss>>stringa;
				return stringa;
			}
		}
		
		virtual ostream & put(ostream & ss) const
		{
			ss<<typeid(*this).name() <<" base=[";
			for(int i=0; i<(*this).getLen(); i++)
			{
				ss<<(*this).get(i) <<" ";
			}
			ss<<"]";
			return ss;
		}
		
	protected:
		char get(short i) const;
	
};

A::A(short m)
{
	len=m;
	base= new char[len];
	
	for(int i=0; i<len; i++)
	{
		base[i]= rand()%('z'-'a'+1)+'a';
	}
	
}

short A::getLen() const
{
	return len;
}

char A::get(short i) const
{
	return base[i];
}

class B : public A
{
	string str;
	double k;
	
	public:
		B(short m, double p);
		double foo(short s);
		string extract(short x) const;
		ostream &put(ostream & ss) const
		{
			return A::put(ss)<<" str="<<str<<" k="<<k<<" extract(3)="<<(*this).extract(3);
		}
};

B::B(short m, double p): A(m) , k{p}
{
	str="";
	stringstream ss;
	ss<<str;
	for(int i=0; i<getLen();i++)
	{
		switch(get(i))
		{
			case 'a':
			case 'e':
			case 'i':
			case 'o':
			case 'u':
				ss<<get(i);
			break;
			default:
			break;
		}
	}
	
	ss>>str;
}

string B::extract(short x) const
{
	string ritorno="";
	stringstream ss;
	ss<<ritorno;
	
	for(int i=0; i<x; i++)
	{
		short k= rand()%(getLen());
		ss<<get(k);
	}
      ss>>ritorno;
	return ritorno;
}

double B::foo(short s)
{
	return (double)(sin(k+s)/log(s+1));
}


class C : public A
{
	int y;
	
	public:
		C(short n, int k);
		string extract(short x) const;
		double g(short w);
		ostream &put(ostream & ss) const
		{
			return A::put(ss)<<" y="<<y<<" extract(3)="<<(*this).extract(3);
		}
	
	
	C  operator ++(int i)
	{
		C copia= *this;
		y++;
		return copia;
	}
};

C::C(short n,int k) : A(n) , y{k} {}

double C::g(short w)
{
	return sin(w+y);
}


string C::extract(short x) const
{
	string ritorno="";
	stringstream ss;
	ss<<ritorno;
	
	int counter=0;
	for(int i=0; i<getLen(), counter < x; i++)
	{
		switch(get(i))
		{
			case 'a':
				case'e':
					case'i':
						case'u':
							case 'o':
								break;
			
			default:
				ss<<get(i);
				counter++;
		}
	}
	
	ss>>ritorno;
	return ritorno;
}

ostream & operator <<(ostream & ss,const A & a)  //operator << vuole i reference, il secondo parametro opportuno sia const
{
	return a.put(ss);
}

int main()
{
	A *vett[DIM];
    srand(111222333);
      for(int i=0; i<DIM; i++){
	short n=10+rand()%10;
	switch(rand()%2)
	{
	  case 0:
	    vett[i]= new C(n, rand()%20 + 1);
	    break;
	  case 1:
	    vett[i]= new B(n, rand()/(double) RAND_MAX);
	    break;
	}
    }
    
    for(int i=0; i<DIM; i++)
    {
    	cout<<i<<")"<<(*vett[i])<<endl;
	}
	
	double somma=0;
	B* ptr_b;
	C* ptr_c;
	
	for(int i=0; i<DIM; i++)
	{
		ptr_b= dynamic_cast<B*>(vett[i]);
		
		if(ptr_b)
		{
			somma= somma + (*ptr_b).foo(5);
		}
		else
		{
			ptr_c= dynamic_cast<C*>(vett[i]);
			if(ptr_c)
			{
				somma=somma+ (*ptr_c).g(5);
			}
		}
		
	}
	
	somma=somma/DIM;
	cout<<"la media e'="<<somma<<endl;
	
	C* ptr_2c;
	ptr_2c= dynamic_cast<C*>(vett[0]);
	

    
    cout<<(*ptr_2c)<<endl;
    cout<<((*ptr_2c)++)<<endl;    //(*ptr_2c)++ rappresenta una rvalue , perciò per poterci effettuare "cout"
         
     
     
     
    cout<<(*ptr_2c)<<endl;
    
    
    cout<<(*vett[0])(1 ,4);
    

    
}








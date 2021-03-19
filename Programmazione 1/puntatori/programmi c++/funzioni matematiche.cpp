#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>

using namespace std;

int main()
{
	int x=pow(5,2);
	cout<<x <<endl;
	float y=sqrt(x);
	cout <<y <<endl;
	float c=sin(90* M_PI / 180);   /* per fare il seno scrivere il numero moltiplicato per M_PI fratto 180,è importante usare all'inizio
	                                    #define _USE_MATH_DEFINES e anche #include <cmath>   per le funzioni matematiche */
	cout<<c <<endl; 
	//int gallo=((sqrt(cbrt(x))));
	//cout<<gallo;
	int v_a=abs(-5);
	cout<<v_a <<endl;
	float r=log(2.7182818284590);
	cout <<r <<endl;
	
	float a=log10(10);
	cout <<a <<endl;
	
	float b=log2(2);
	cout <<b <<endl; 
	
	float h=cos(60*M_PI/180);
	cout<<"il valore h e\' "<<h;
	
	float k=tan(60*M_PI/180);
	cout<<endl <<"il valore k e\'"<<k;
	 double w=sin(60*M_PI/180)/cos(60*M_PI/180);
	 cout<<endl <<"il valore w e\'"<<w;
	 
	 
	 
	 float s=1.23456789123456789;
	 cout<<endl<<s;
	 double z=1.23456789123456789;
	 cout<<endl<<z;
	 
	 
	 
	 
	 

	
	
	
	
}

//homework 11.5

#include <iostream>
using namespace std;

int main()
{

	int somma=0;
	for(int i=2;i<1000&&somma<100000;i=i+2)
	{
		
		somma=somma+i;
		
	}
	
	
	cout<<somma;
	
}

//homework 11.4

#include <iostream>
using namespace std;

int main()
{
	
	
	int somma=0;
	
	for(int i=1;i<100;i=i+2)
	{
		if(i%3!=0)
		{
			somma=somma+i;
		}
	}
	
	cout<<somma;
	
	
	
}

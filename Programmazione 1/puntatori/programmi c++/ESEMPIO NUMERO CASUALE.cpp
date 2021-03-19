#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main()
{
	cout<<"inserisci 2 numeri e diro un casuale tra essi";
	cout<<"(il primo deve essere minore)"<<endl;
	int num1;
	int num2;
	
	bool voglio=true;
	while(voglio)
	{
	
	cin>>num1>>num2;
	
	srand(time(NULL));
	
	int r=num1+(rand()%(num2-num1+1));   //generazione casuale tra num1 e num2
	cout<<r<<endl;
	
	cout<<"vuoi riprovare?(y/n)"<<endl;
	char a;
	cin>>a;
	switch(a)
	{
		case 'y':
	    break;
	    case 'n':
	    voglio=false;
	    break;
	}
}
}

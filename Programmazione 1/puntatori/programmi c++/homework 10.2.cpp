//HOMEWORK 10.2
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main()
{
	
	int a;
	int b;
	int c;
	cout<<"inserisci il valore a"<<endl;
	cin>>a;
	cout<<"inserisci il valore b"<<endl;
	cin>>b;
	cout<<"inserisci il valore c"<<endl;
	cin>>c;
	cout<<"inserisci una parola ";
	string pippo;
    cin>>pippo;
	
	if(a!=c&&pippo.length()<8)
	{
	b=a+c;
	cout<<"i valori sono"<<a<<" "<<b<<" "<<c<<endl;
}
    else 
    {
    	if(a=c&&pippo.length()<8)
    	{
    		a=c-b;
    		cout<<"i valori sono"<<a<<" "<<b<<" "<<c<<endl;
		}
		else
		{
			a=0;b=0;c=0;
			cout<<"i valori sono"<<a<<" "<<b<<" "<<c<<endl;
		}
	}
	
	
	
	
}

//HOMEWORK 10.1
#include <iostream>


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
	cout<<"i valori a, b e c sono rispettivamente "<<a<<" "<<b<<" "<<c<<endl;
	int x;
	(a>b?x=a :x=b);
//	cout<<"il massimo tra " <<a<<" e "<<b<<" e' "<<x;
	 int y;
	 (x>c?y=x:y=c);
	 
	 	cout<<"il massimo tra " <<a<<" , "<<b<<" e "<<c<<" e' "<<y;
	
	
	
	
	
	
	
	
	
}

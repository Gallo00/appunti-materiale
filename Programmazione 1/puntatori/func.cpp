#include <iostream>
using namespace std;

void func(int *x,int *y)
{
	int a;
	int b;
	cout<<"inserisci a, b"<<endl;
	cin>>a>>b;
	*x=a+b;
	*y=a-b;
	
}


int main()
{
	int pippo;
	int pluto;
	func(&pippo,&pluto);
	
	cout<<"il puntatore *x punta alla somma,*y alla differenza"<<endl;
	cout<<pippo<<" "<<&pippo<<endl;
	cout<<pluto<<" "<<&pluto<<endl;
	
	
	int r=50;
	int *v=&r;
	cout<<v<<" "<<*v<<" "<<r<<" "<<&r;
	
	
	
	
	
	
	
	
	
	
}

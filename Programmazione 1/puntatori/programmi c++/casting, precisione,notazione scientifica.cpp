#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	
	
	float d=10.2678;
	cout<<d<<endl;
	char result=static_cast<double>(d);     //conversione
	cout<<result;
	
	float s;
	cout<<"metti s "<<endl;
	cin>>s;
	cout<<fixed<<setprecision(3)<<s<<endl; // precisione dell'approssimazione(senza il fixed la precisione vale per tutte le cifre,con solo per le decimali)
	
	float w=7.363929;
	cout<<scientific<<w;           //notazione scientifica
	
	
	
	
}

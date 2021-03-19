#include <iostream>
using namespace std;

int main()
{
	string y="y";
	string n="n";
	float x;
	float prezzo_finale;
	float differenza=0.0;
	string a;
	string t;
	cout<<"importo=";
	cin>>x;
	cout<<"prodotto in promozione?(y/n)";
	cin>>a;
	cout<<"tessera cliente?(y/n)";
	cin>>t;
	bool uscire=true;
	
	if(x<=100)
	{
	
	prezzo_finale=x-(x*0.1); 
	uscire=false;
    }
    if(x>100&&x<=1000&&uscire)
    {
    	if(t==y)
    	{
    		prezzo_finale=x-(x*0.2);
    		
    		uscire=false;
		}
		else
		{
			if(a==y)
			{
				prezzo_finale=x-(x*0.18);
				uscire=false;
			}
			else
			{
				prezzo_finale=x-(x*0.15);
				uscire=false;
			}
		}
	}
	if(x>1000&&uscire)
	{
		differenza=x-1000;
		differenza=differenza-(differenza*0.3);
		x=1000;
		if(x>100&&x<=1000&&uscire)
    {
    	if(t==y)
    	{
    		prezzo_finale=x-(x*0.2);
		}
		else
		{
			if(a==y)
			{
				prezzo_finale=x-(x*0.18);
				uscire=false;
			}
			else
			{
				prezzo_finale=x-(x*0.15);
				uscire=false;
			}
		}
	}
		
		
	}
	
	cout<<(prezzo_finale+differenza);
	
	
}

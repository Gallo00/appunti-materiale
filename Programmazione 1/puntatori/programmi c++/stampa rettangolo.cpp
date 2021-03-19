#include <iostream>
using namespace std;

int main()

{
	int b;
	int h;
	cout<<"inserisci una base b e una altezza h" <<endl;
	cin>>b;
	cout<<"la tua base e\'"<<b <<endl;
	cin>>h;
    cout<<"la tua altezza e\'"<<h <<endl;
    int x=0;
    
    for(int c=0;c<h;x++)
    {
    	if((x+c)%2==0)
    	{
    		cout<<"*";
    
		}
		else
		{
			cout<<"-";
		}
    	if(x==b-1)
    	{
    		cout<<endl;
    		x=-1;
    		c++;
		}
    	
	}
	
	
	
	
}

#include <iostream>
using namespace std;

int main()
{
	cout<<"inserisci capitale iniziale"<<endl;
	float x;
	cin>>x;
	cout<<"inserisci tasso interesse"<<endl;
	float t_i;
	cin>>t_i;
	cout<<"inserisci target"<<endl;
	float t;
	cin>>t;
	int N;
	cout<<"inserisci anni"<<endl;
	cin>>N;
	
	if(t<=0||N<=0)
	{
		if(t>0)
		{
		cout<<"non uso anni";
	    }
	    if(N>0)
	    {
	    	cout<<"non uso target";
		}
	   if(t<=0&&N<=0)
	{
		cout<<"errore";
	}
	
}
	
	
}

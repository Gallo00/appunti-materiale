#include <iostream>
using namespace std;

int main()
{
//	bool _0errori=false;
	int p;
	cout<<"inserisci un valore uguale o maggiore a 1"<<endl;
    cin>>p;
    int controllo=0;
while(controllo==0)
{
	controllo=0;
	
    cin>>p;
	if(p<1)
	{
		cout<<"errore"<<endl;
		cout<<"inserisci un valore uguale o maggiore a 1"<<endl;
	}
	else
	{
		controllo=controllo+1;
//		_0errori=true;
		cout<<"hai creato un array di dimesione "<<p<<endl;
		int A[p];
		int i=0;
		while(i<p)
		{
			cout<<"decidi valore casella "<<i<<endl;
			cin>>A[i];
			i++;
		} 
	/*	for(int i=0;i<p;i++)
		{
			cout<<"decidi valore casella "<<i<<endl;
			cin>>A[i];
	    }
	
	   do{
	    	cout<<"decidi valore casella "<<i<<endl;
			cin>>A[i];
		}
		
		while(i<p)
		*/
		i=0;
		while(i<p)
		{
			cout<<A[i]<<"-";
			i++;
		}
		
		
		
		
		
		
		
	}
	
}
}

#include <iostream>
#include <stdlib.h>   // stdlib.h e time.h servono per la funzione rand
#include <time.h>
using namespace std;

int main()
{
	
	int x;
	int y;
	cout<<"inserisci lunghezza stringa" <<endl;
	cin>>x;
	y=(x/2);
	
	char A[x];
	cin>>A;
	cout <<A;
	int j=x-1;
	int i=0;
	bool esci=true;
	while(i<y&&esci)
	{
	
	 if(A[i]==A[j])
	 {
	 	i=i+1;
	 	j=j-1;
	 }
	else
	{
		esci=false;
		 cout<<"non e\' palindroma";
	}
}
	if(i==y)
	{
		cout<<"e\' palindroma";
	}
	return 0;
}

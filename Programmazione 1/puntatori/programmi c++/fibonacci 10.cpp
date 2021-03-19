#include <iostream>
 #include <windows.h>   //For Beep & Sleep functions
using namespace std;

int main()
{
 
 int A[121];
 Sleep(1000);
 cout<<"1" <<endl;
 Sleep(1000);
 cout<<"1" <<endl;
 Sleep(1000);
 A[0]=1;
 A[1]=1;
	int i=2;
//	int x=0;
	while(true)
	{
	
	A[i]=A[i-1]+A[i-2];
	
	
	cout<<A[i];
	cout<<endl;
	Sleep(1000);
	
	i++;
}
	
	
	
	
	
	
	
return 0;	
}

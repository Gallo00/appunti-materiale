#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <string>

using namespace std;

int main()
{
	
   
   char x='c';
   string x_s(1,x);
   cout<<x_s<<endl;
   
   x_s= x_s + 'p';
   cout<<x_s<<endl;
   
   string stringa(1,x);
		for(int i=1; i<5; i++)
		{
			stringa= stringa + x;
		}
		cout<<stringa<<endl;
   
   
   
   
}


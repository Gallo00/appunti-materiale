//HOMEWORK 10.5
#include <iostream>
using namespace std;

int main()
{
	cout<<"metti y";
	char y;
	cin>>y;
	int result;
//	string a,e,i,o,u,A,E,I,O,U;
	switch(y)
	{
		case 'a':
		case 'e':
		case 'i':
	    case 'o':
	    case 'u':
	  //  cout<<y;
	    result=static_cast<int>(y);
	    cout<<result;
	    break;
	    case 'A':
		case 'E':
		case 'I':
	    case 'O':
	    case 'U':
	    cout<<y;
	    break;
}
       int l=static_cast<int>(y);
       
       if(y>=1&&y<=3)
       {
       	
       	cout<<(10*y);
	   }
	
	
}

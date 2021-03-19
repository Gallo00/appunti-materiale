//homework 11.7
#include <iostream>
#include <sstream>
using namespace std;

int main()
{
	stringstream sa;
	int i=97;
		while(i<122)
	{
		char x=static_cast<char>(i);
		sa<<x;
		cout<<x;
		i++;
	}
	
    cout<<endl;

	string g;
	sa>>g;
	cout<<g.length();
	
	
	
}

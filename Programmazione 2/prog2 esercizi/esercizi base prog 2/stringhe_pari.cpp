#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <locale>

using namespace std;


int main()
{
	fstream miofile("input.txt",fstream::in);
	fstream outfile("output.txt",fstream::out);
	
	for(int riga=0; riga<100; riga++)
	{
		string parola;
		miofile>>parola;
		int x=parola.length();
		if(x%2==0)
			outfile<<parola<<endl;
		else
			outfile<<parola.substr(0,x-1)<<endl;
	}
	return 0;
}
#include <iostream>
#include <fstream>
#include <string>
using namespace std;



int main()
{
	fstream miofile("input.txt",fstream::in);
	fstream outfile("output.txt",fstream::out);
	
	for(int riga=0; riga<100; riga++)
	{
		string parola;
		miofile>>parola;
		parola=parola + parola;
		outfile<<parola<<endl;
	}
	miofile.close();
	outfile.close();
	return 0;
}
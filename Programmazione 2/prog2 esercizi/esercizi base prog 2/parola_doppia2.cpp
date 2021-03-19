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
		int lung=parola.length();
		lung=lung/2 ;
		string nuova_parola=parola.substr(0,lung);
		outfile<<nuova_parola<<endl;
	}
	
	miofile.close();
	outfile.close();
	return 0;
}
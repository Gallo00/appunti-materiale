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
//	setlocale(LC_ALL, "en_US.UTF-8");
	for(int riga=0; riga<100; riga++)
	{
		int counter=0;
		for(int i=0; i<3; i++)
		{
			int lung;
			miofile>>lung;
			string parola;
			miofile>>parola;
			if(parola[0]==parola[lung-1])
				counter++;
		}
		outfile<<counter<<endl;
		cout<<counter<<endl;
	}
	miofile.close();
	outfile.close();
	return 0;
}
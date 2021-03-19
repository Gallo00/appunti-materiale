#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
using namespace std;


int main()
{
	fstream miofile("input.txt",fstream::in);
	fstream outfile("output.txt",fstream::out);
	
	for(int riga=0; riga<100; riga++)
	{
		char lettera;
		miofile>>lettera;
		for(int i=0; i<3;i++)
		{
			int lung;
			miofile>>lung;
			string parola;
			miofile>>parola;
			
			if(parola[0]==lettera)
			{
				outfile<<parola<<" ";
			}
		}
		outfile<<endl;
	}
	miofile.close();
	outfile.close();
    return 0;	
}
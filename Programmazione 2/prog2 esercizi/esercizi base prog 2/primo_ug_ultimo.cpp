#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <cstring>
#include <string>
#include <locale>

using namespace std;


int main()
{
	fstream miofile("input2.txt",fstream::in);
    FILE* outFile = fopen( "output.txt", "w+,ccs=UTF-8");
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
		string x=to_string(counter);
		char cstr[x.size()+1];
		strcpy(cstr,x.c_str());
	    fwprintf(outFile, L"%hs %s", cstr,"\n");
	}
	miofile.close();
	fclose(outFile);
	return 0;
}
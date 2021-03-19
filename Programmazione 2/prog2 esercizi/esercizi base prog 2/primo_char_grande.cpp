#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
using namespace std;


string char_grande(string nome,int i)
{
	nome[i]=toupper(nome[i]);
	return nome;
}

int main()
{
	fstream miofile("input.txt",fstream::in);
	fstream outfile("output.txt",fstream::out);
	
	for(int riga=0; riga<100; riga++)
	{
		for(int i=0; i<3; i++)
		{
		    int lung;
		    miofile>>lung;
		    string x;
		    miofile>>x;
			x=char_grande(x,0);
			outfile<<x<<" ";
		}
		outfile<<endl;
	}
	miofile.close();
	outfile.close();
	return 0;
}


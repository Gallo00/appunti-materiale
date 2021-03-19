#include <iostream>
#include <fstream>
#include <string>
using namespace std;


int main()
{
	fstream miofile("input.txt", fstream::in);
	fstream outfile("output.txt",fstream::out);
	
	for(int riga=0; riga<100; riga++)
	{
		char A;
		miofile>>A;
		char B; 
		miofile>>B;
		
		for(int i=0; i<3; i++)
		{
			int lung;
			miofile>>lung;
			string nome;
			miofile>>nome;
			
			if( (nome[0]==A || nome[lung-1]==A) && (nome[0]!=B && nome[lung-1]!=B) )
			{
				outfile<<nome<<" ";
			}
	    }
		outfile<<endl;
	}
	miofile.close();
	outfile.close();
	return 0;
}
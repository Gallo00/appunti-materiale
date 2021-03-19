#include <iostream>
#include <fstream>
using namespace std;


int main()
{
	fstream miofile("input.txt" , fstream::in);
	fstream outfile("output.txt" , fstream::out);
	
	for(int riga=0; riga<100; riga++)
	{
		int x;
		miofile>>x;
	    int array[x];
		for(int i=0; i<x; i++)
		{
			double a;
			miofile>>a;
			int b= static_cast<int>(a);
			array[i]=b;
	    }

		for(int i=0; i<x; i++)
		{
			outfile<<array[i] <<" ";
		}
	outfile<<endl;
    }
	
	miofile.close();
	outfile.close();
}
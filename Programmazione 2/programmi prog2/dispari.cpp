#include <iostream>
#include <fstream>
using namespace std;


string dispari(int array[], int n){
	string ritorno="";
	for(int i=0; i<n; i++){
		if(array[i]%2==1)
		{
			ritorno= ritorno + to_string(array[i]) + " ";
		}
	}
	ritorno= ritorno + "\n";
	return ritorno;
}



int main()
{
	fstream miofile("input.txt", fstream::in);
	fstream outfile("output.txt",fstream::out);
	
	for(int riga=0; riga<100; riga++)
	{
		int x;
		miofile>>x;
		int s[x];
		for(int i=0; i<x; i++)
		{
			miofile>>s[i];
		}
		outfile<<dispari(s,x);
	}
}
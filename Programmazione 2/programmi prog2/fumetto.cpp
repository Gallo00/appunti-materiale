#include <iostream>
#include <fstream>
using namespace std;

int scorrimento(int array[], int n, int f){
	for(int i=0; i<n; i++){
		if(array[i]==f) return i+1;
	}
	return 0; //non presente
	
}

int main(){
	fstream miofile("input.txt", fstream::in);
	fstream outfile("output.txt", fstream::out);
	
	for(int riga=0; riga<100; riga++){
		int x,f;
		miofile>>x;
		miofile>>f;
		int s[x];
		for(int i=0; i<x; i++)
		{
			miofile>>s[i];
		}
		
		int numero=scorrimento(s,x,f);
		outfile<<numero<<endl;
	}
}			
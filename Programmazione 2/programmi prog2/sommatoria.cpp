#include <iostream>
#include <fstream>
using namespace std;

double sommatoria(double array[] , int n){
	double sum=0;
	for(int i=0; i<n; i++)
	{
		sum=sum+array[i];
	}
	//cout<<sum;
	return sum;
}



int main(){
	fstream miofile("input.txt", fstream::in);
	fstream outfile("output.txt",fstream::out);
	
	for(int riga=0;riga<100; riga++){
	//	cout<<"primo for"<<endl;
		int x;
		miofile>>x;
		double s[x];
		
		for(int i=0; i<x; i++)
		{
			
			miofile>>s[i];
		//	cout<<"s[i]="<<s[i]<<endl;
		}
		
		outfile<< sommatoria(s,x)<<endl;
	
	
}
}
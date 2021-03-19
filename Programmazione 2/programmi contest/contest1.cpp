#include <iostream>
#include <fstream>
using namespace std;


int main(){
	fstream infile("input.txt" , fstream::in);
	fstream outfile("output.txt",fstream::out);
	
	for(int riga=0; riga<100; riga++){
		int classi;
		int gruppi;
		infile>>classi;
		infile>>gruppi;
		
		int num_studenti[classi];

		for(int i=0; i<classi; i++){
			infile>>num_studenti[i];
		}

		
		int array_gruppo[gruppi*2];

		for(int i=0; i<gruppi*2; i=i+2){
			int a, b;
			infile>>a;
			infile>>b;
			array_gruppo[i]=a;   //id classe
			array_gruppo[i+1]=b; //studenti saliti sul pullman

			
		}

		
		for(int i=0; i<gruppi*2; i=i+2){
			int x=(array_gruppo[i]);
			num_studenti[x]=num_studenti[x]-array_gruppo[i+1];
		}
		

		int c=0;
		for(int i=0; i<classi;i++){
			if(num_studenti[i] >0){
				c++;
			}
		}

		
		if(c>0)
		{
			outfile<<to_string(c) + " ";
			for(int i=0; i<classi; i++){
				outfile<< to_string(i) + " " + to_string(num_studenti[i])+ " ";
			}
		}
		else
		{
			outfile<<to_string(c);
		}
		
		outfile<<endl;
}
}
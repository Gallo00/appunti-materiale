#include <iostream>
#include <fstream>
#include <string>
using namespace std;





string minori(int s[], int n, int limite){
	string ritorno="";
	for(int i=0; i<n; i++)
	{
		if(s[i]>limite)
		{
			ritorno= ritorno + to_string(s[i])+ " ";

		}
    }
 
	return ritorno;
}

int conta_numeri(string s){
	int numero=0;
	for(int i=0; i<s.length(); i++){

		if(s[i]==' ')
		{
			numero++;
		}
	}
	return numero;

}



int main(){
	fstream miofile("input.txt", fstream::in);
	fstream outfile("output.txt", fstream::out);
	
	
	
	for(int riga=0; riga<100;riga++)
	{
		
	    int x , limite;
	    miofile>>x;
	    miofile>>limite;

	    int s[x];
	    for(int i=0; i<x; i++)
	    {
		    miofile>>s[i];
	    }
	    string a=minori(s,x,limite);
	    outfile<<conta_numeri(a)<<" "<<a<<endl;
}
    
	cout<<endl;
//	cout<<s[1]+50;
}
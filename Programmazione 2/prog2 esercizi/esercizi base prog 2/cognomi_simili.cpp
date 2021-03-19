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
		int prefisso;
		miofile>>prefisso;
		
		string nomi[3];
		for(int i=0; i<3; i++)
		{
			string nome;
			miofile>>nome;
			nomi[i]=nome;
		}
		
		bool primo_sec=false;
		if((nomi[0]).substr(0,prefisso-1)==((nomi[1]).substr(0,prefisso-1)) && (nomi[0])[prefisso]!=(nomi[1])[prefisso])
		{
			primo_sec=true;
		}
		
		bool primo_ter=false;
		if((nomi[0]).substr(0,prefisso-1)==((nomi[2]).substr(0,prefisso-1)) && (nomi[0])[prefisso]!=(nomi[2])[prefisso])
		{
			primo_ter=true;
		}
		
		bool sec_ter=false;
		if((nomi[1]).substr(0,prefisso-1)==((nomi[2]).substr(0,prefisso-1)) && (nomi[1])[prefisso]!=(nomi[2])[prefisso])
		{
			sec_ter=true;
		}
		
		
		if(primo_sec && primo_ter && sec_ter)
		{
			outfile<<nomi[0]<<" "<<nomi[1]<<" "<<nomi[2]<<endl;
		}
		else if(primo_sec && primo_ter)
		{
			outfile<<nomi[0]<<" "<<nomi[2]<<endl;
		}
		else if(primo_sec && sec_ter)
		{
			outfile<<nomi[0]<<" "<<nomi[1]<<endl;
		}
		else if(primo_ter && sec_ter)
		{
			outfile<<nomi[0]<<" "<<nomi[1]<<endl;
		}
		else if(primo_ter)
		{
			outfile<<nomi[0]<<" "<<nomi[2]<<endl;
	    }
		else if(sec_ter)
		{
			outfile<<nomi[1]<<" "<<nomi[2]<<endl;
	    }
		else if(primo_sec)
		{
			outfile<<nomi[0]<<" "<<nomi[1]<<endl;
		}
	}
	miofile.close();
	outfile.close();
	return 0;
}
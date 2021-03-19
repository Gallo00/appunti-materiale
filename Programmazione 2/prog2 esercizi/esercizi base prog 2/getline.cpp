#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;




int main()
{
	fstream f("ciao.txt",fstream::in);
	string s;
	getline(f,s);
	cout<<s<<endl;
	
	int i=0;
	string a="";
	bool num=false;
	while(i<s.length())
	{
		if(s[i]!=32)
		{
			num=true;
			if(s[i]!=46)
			{
			    a=a + to_string(s[i]-48);
			}
			else
			{
				a= a + ".";
			}
			cout<<a<<endl;
		}
		else
		{
			if(num)
			{
				stringstream ss;
				double numero;
				ss<<a;
				ss>>numero;
				cout<<"il numero e'"<<numero<<endl;
				num=false;
				a="";
			}
		}
		i++;
	}
	stringstream ss;
	double numero;
	ss<<a;
	ss>>numero;
	cout<<"il numero e'"<<numero<<endl;
	
	
}
    


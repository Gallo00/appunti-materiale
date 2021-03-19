//HOMEWORK 10.3
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main()
{
	
	string s1;
	string s2;
	string s3;
	string mys;
	cout<<"inserisci stringa 1"<<endl;
	cin>>s1;
	cout<<"inserisci stringa 2"<<endl;
	cin>>s2;
	cout<<"inserisci stringa 3"<<endl;
	cin>>s3;
	cout<<"inserisci stringa mys"<<endl;
	cin>>mys;
//	bool controllo=falses
	
	if((s1.length()>10||s2.length()>10||s3.length()>10)&&(s1.length()>=20||s2.length()>=20||s3.length()>=20))
	{
		int i=0;
		while(i<3)
		{
	        mys=mys+s2[i];
	        i++;
        }
       int c=0;
       int j=s3.length()-1;       
	   while(c<3)
       {
           	mys=mys+s3[j];
       	    j--;
        	c++;
	   }
	   cout<<mys;
	}
	else
	{
		if(s1.length()>10||s2.length()>10||s3.length()>10)
		{
			mys=mys+s1+s2+s3;
			cout<<mys;
		}
		else{
			cout<<s1.length()<<endl;
			cout<<s2.length()<<endl;
			cout<<s3.length()<<endl;
			
		}
	}
	
}
	
	
	
	
	
	


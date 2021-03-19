#include <fstream>
#include <iostream>

using namespace std;

void stampa(int arr[],int n)
{
	for(int i=0; i<n; i++)
	{
		cout<<arr[i]<<" ";
	}
	cout<<endl;
}


int main()
{
	fstream miofile("input.txt" , fstream::in);
	fstream outfile("output.txt", fstream::out);
	
	for(int riga=0; riga<100; riga++)
	{
		string r;
		getline(miofile,r);
		int occorrenze[26];
		for(int i=0; i<26;i++)
		{
			occorrenze[i]=0;
		}
	/*	if(riga<2)
		{
		cout<<"stampa di r"<<r<<endl;
		stampa(occorrenze,26);
		} */
		for(int i=0; i<r.length(); i++)
		{
			if(r[i]!=32)
			{
				occorrenze[(int)(r[i]) - 72 -25]=occorrenze[(int)(r[i]) - 72 -25] + 1;
			}
		}
	/*	if(riga<2)
		stampa(occorrenze,26); */
		int max=occorrenze[0];
		int ind_max=0;
		for(int i=0; i<26;i++)
		{
			if(max<occorrenze[i])
			{
				max=occorrenze[i];
				ind_max=i;
			}
		}
		for(int i=0; i<26; i++)
		{
			if(occorrenze[i]==max)
			{
				ind_max=i;
				break;
		    }
		}
		
		char lettera= 97 + ind_max;
		outfile<<lettera<<" "<<max<<endl;
		
	}
	miofile.close();
	outfile.close();
	return 0;
}
    
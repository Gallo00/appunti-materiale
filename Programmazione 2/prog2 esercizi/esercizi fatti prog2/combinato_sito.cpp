#include <iostream>
#include <fstream>
using namespace std;


int trova_min(int arr[],int ind)
{
	int min=arr[0];
	int ind_min=0;
	for(int i=0; i<ind;i++)
		if(arr[i]<min) {min=arr[i]; ind_min=i;}
	return ind_min;
}


class Lista_comb
{
	public:
	int *K;
	int *N;
	int lung;
	int ind;
	
	
	
	Lista_comb(int len)
	{
		ind=-1;
		lung=len;
		K=new int[lung];
		N=new int[lung];
	}
	
	void insert(int dato)
	{
		ind=ind+1;
		K[ind]=dato;
		
		if(ind==0) N[0]=-1;
		else
		{
			int i=trova_min(K,ind);
			if(K[ind]<K[i])
			{
				N[ind]=i;
			}
			else
			{
				int l=i;
				while(K[ind]>=K[i] && i!=-1)
				{
					l=i;
					i=N[i];
				}
				if(!(K[ind]>=K[i]))
				{
					N[l]=ind;
					N[ind]=i;
				}
				else
				{
					N[l]=ind;
					N[ind]=-1;
				}
			}
		}
	}
	
	void print(ofstream & f)
	{
		for(int i=0; i<lung;i++)
		{
			int a=N[i];
			f<<a<<" ";
		}
		f<<endl;
	}
	

};


int main()
{
	fstream miofile("input_comb1.txt",fstream::in);
	ofstream outfile("output.txt");
	
	for(int riga=0; riga<100; riga++)
	{
		int lung;
		miofile>>lung;
		Lista_comb lc(lung);
		
		for(int i=0; i<lung;i++)
		{
			int a;
			miofile>>a;
			lc.insert(a);
		}
		lc.print(outfile);
	}
	return 0;
}









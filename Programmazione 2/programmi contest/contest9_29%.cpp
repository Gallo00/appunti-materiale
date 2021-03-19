#include <iostream>
#include <fstream>
#include <limits.h>
using namespace std;

void stampa(int arr[],int n)
{
	cout<<"[";
	for(int i=0; i<n; i++)
	{
		cout<<arr[i]<<" ";
	}
	cout<<"]"<<endl;
}

bool finito(int arr[],int s,int n)
{
	int c=1;
	for(int i=s-1;i>-1;i--)
	{
		if(arr[i]!=n-c)
		{
			return false;
		}
		c++;
	}
	return true;
}

int calcolo_min(int arr1[],int arr2[],int s)
{
//	cout<<"31"<<endl;
	int min=INT_MAX;
	for(int i=0; i<s-1;i++)
	{
		for(int j=i+1;j<s;j++)
		{
			int a=arr2[j];
			int b=arr2[i];
		//	cout<<a<<" "<<b;
			if(min>arr1[a]-arr1[b])
			{
				min=arr1[a]- arr1[b];
			}
		}
	}
//	cout<<"46"<<endl;
	return min;
}

int comb(int arr1[],int arr2[],int s,int n,int riga)
{
	int max=0;
	while(!finito(arr2,s,n))
	{
//		cout<<"53"<<endl;
		if(max<calcolo_min(arr1,arr2,s))
		{
			max=calcolo_min(arr1,arr2,s);
		}
		
//		cout<<"61"<<endl;
		int i=s-1;
		int c=1;
		bool incremento=false;
		while(!incremento && i>=1)
		{
//			cout<<"while"<<endl;
//			cout<<arr2[i]<<" "<<n<<" "<<c<<endl;
			if(arr2[i]<n-c)
			{
//				cout<<"1 than"<<endl;
				arr2[i]=arr2[i]+1;
//				cout<<arr2[i]<<endl;
				incremento=true;
			}
			else
			{
//				cout<<"1 else";
				i--;
				c++;
			}
		}
        if(riga==30)
		cout<<i<<endl;
		if(i==0)
		{

		arr2[0]=arr2[0]+1;
		for(int j=1; j<s;j++)
			{
				arr2[j]=arr2[0]+j;
			}
		
		}
		
		if(riga==30)
		stampa(arr2,s);
	}
	
	int p=1;
	for(int i=s-1;i>0;i--)
	{
		arr2[i]=n-p;
		p++;
	}
	int a=calcolo_min(arr1,arr2,s);
	
	
	if(a>max)
	{
		max=a;
	} 
	
	return max;
}
		
				
			
		

	






int main()
{
	
	fstream miofile("inputtt.txt",fstream::in);
	fstream outfile("output.txt",fstream::out);
	
	for(int riga=0; riga<100;riga++)
	{
//		cout<<"riga="<<riga<<endl;
		int n; 
		miofile>>n;
		
		int s;
		miofile>>s;
		
		int arr1[n];
		for(int i=0; i<n; i++)
		{
			int a;
			miofile>>a;
			arr1[i]=a;
		}
		
		int arr2[s];
		for(int i=0; i<s; i++)
		{
			arr2[i]=i;
		}
		
		if(s==2)
		{
			outfile<<arr1[n-1] - arr1[0]<<endl;
		}
		else
		{
//		stampa(arr1,n);
//		stampa(arr2,s);
//		cout<<"result="<<comb(arr1,arr2,s,n)<<endl;
            
			outfile<<comb(arr1,arr2,s,n,riga)<<endl;
		 
		}
	}
	
	miofile.close();
	outfile.close();
		
		

	return 0;
		
	
	
}
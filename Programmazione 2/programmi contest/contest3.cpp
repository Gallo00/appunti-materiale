#include <iostream>
#include <fstream>

using namespace std;


int prossima_stazione(int carburante,int a[],int i,int n){
	
	int j=i;
	while((a[j]-a[i])<=carburante && j<n)
	{
		j++;
	}
	if(j==n){
		return n+1;
	}
	else{
	return j-1;
	}
}
		
	




int main(){
	
	
	fstream miofile("input.txt",fstream::in);
	fstream outfile("output.txt",fstream::out);
	

	for(int riga=0; riga<100; riga++)
	{
	    int n;
	    miofile>>n;   //numero stazioni
	    int k;
	    miofile>>k;   
	    int m;
	    miofile>>m;   
		
		int a[n+2];
		a[0]=0;
		for(int i=1;i<n+1;i++)
		{
			int b;
			miofile>>b;
			a[i]=b;
		}
		a[n+1]=m;
		int i=0;
		int c=0;
		while(i<n+1)
		{
			i=prossima_stazione(k,a,i,n+2);
			c++;
		}
		c=c-1;
		outfile<<c<<endl;
		
	}
		
	miofile.close();
	outfile.close();
	
}
	
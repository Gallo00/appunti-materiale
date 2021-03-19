#include <iostream>
#include <fstream>

using namespace std;

void stampa(int** a,int n)
{
	for(int i=0; i<n;i++)
	{
		for(int j=0; j<i+1;j++)
		{
			cout<<a[i][j]<<" ";
		}
		cout<<endl;
	}
}

int somma_max(int **a,int n)
{
	if(n==1)
	{
		return a[0][0];
	}
	int**b=new int*[n-1];
	for(int i=0; i<n-1;i++)
	{
		b[i]=new int[n-1];
	}
	
	for(int i=0; i<n-1;i++)
	{
		for(int j=0; j<i+1;j++)
		{
			b[i][j]=a[i][j];
		}
	}
	
	for(int j=0; j<n-2+1;j++)
	{
	    if(a[n-2+1][j]>a[n-2+1][j+1])    //ogni numero ne avrà due sotto, gli addizioniamo il maggiore dei due e salviamo il risultato in quella stessa cella			
	    {
		    b[n-2][j]=a[n-2][j]+a[n-2+1][j];	
	    }
	    else
	    {
	        b[n-2][j]=a[n-2][j]+a[n-2+1][j+1];
	    }
	}
	return somma_max(b,n-1);
}



int main()
{
	fstream miofile("input.txt", fstream::in);
	fstream outfile("output.txt",fstream::out);
	
	for(int riga=0; riga<100;riga++)
	{
		int x;
		miofile>>x;
		
		int **mat=new int*[x];
		for(int i=0; i<x;i++)
			mat[i]=new int[x];
		
		
		for(int i=0; i<x;i++)
		{
			for(int j=0; j<i+1;j++)
			{
				int k;
				miofile>>k;
				mat[i][j]=k;
			}
		}
//		stampa(mat,x);
 //   	cout<<" \n \n \n";
		
//		cout<<"somma max="<<somma_max(mat,x);
//		cout<<"\n \n \n";
        
		
		
		
		
		outfile<<somma_max(mat,x)<<endl;
		
	}
		
}
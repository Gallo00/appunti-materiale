#include <iostream>
#include <fstream>
using namespace std;


void stampa(int a[], int n)
{
	cout<<" [";
	for(int i=0; i<n;i++)
	{
		cout<<a[i]<<" ";
	}
	cout<<"]"<<endl;
}


//ordinamento per inserimento

int ord_inserimento(int a[], int n)
{  
	int i,j,valore;  
	int counter=0;
	for (i=1; i <n; i++) // i identifica il sottovettore A[0]..A[i] 
   	{	
   		valore=a[i];
   		j=i-1; // Attraversiamo il vettore partendo da A[i] e cercando la posizione j 
   			// dove inserire l'elemento destinazione
   		while (j>=0 && a[j]>valore) 
   			{
   				a[j+1]=a[j]; // Spostiamo gli elementi a destra per far spazio  
   				j--;		// all'elemento in posizione i 
				counter++;
   			}
   		a[j+1]=valore;
   	}
	return counter;
}   



int main()
{
	fstream miofile("input.txt",fstream::in);
	fstream outfile("output.txt",fstream::out);
	
	for(int riga=0; riga<100; riga++)
	{
		int x;
		miofile>>x;
		int vett[x];
		for(int i=0; i<x; i++)
		{
			int a;
			miofile>>a;
			vett[i]=a;
		}
		
		outfile<<ord_inserimento(vett,x)<<endl;
    }
	miofile.close();
	outfile.close();

}








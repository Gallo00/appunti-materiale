#include <iostream>
#include <fstream>
using namespace std;



void stampa(int a[], int n){
	cout<<" [";
	for(int i=0; i<n;i++){
		cout<<a[i]<<" ";
	}
	cout<<"]"<<endl;
}

void scambia(int &a, int &b){
	int var=a;
	a=b;
	b=var;
}


int selection_sort(int a[],int n)
{
	int temp;
	int sum=0;
    for(int i=0;i<n-1;i++)
    {
	    int min=i;
        for(int j=i+1;j<n;j++)
        	if (a[j]<a[min])
        	    min=j;
        temp=a[min];
        a[min]=a[i];
		sum=sum+min-i;
        a[i]=temp;
    }
	return sum;
}

int main()
{
	fstream miofile("input_selec.txt",fstream::in);
	fstream outfile("output.txt",fstream::out);
	
	for(int riga=0; riga<100; riga++)
	{
		int lung;
		miofile>>lung;
		
		int vett[lung];
		for(int i=0;i<lung; i++)
		{
			int a;
			miofile>>a;
			vett[i]=a;
		}
		
		int somma=selection_sort(vett,lung);
		outfile<<somma<<endl;
    }
	miofile.close();
	outfile.close();
}
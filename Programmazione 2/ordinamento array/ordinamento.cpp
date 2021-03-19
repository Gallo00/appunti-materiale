#include <iostream>
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



//ordinamento di un array

//per scambio


void ordinamento_scambio(int a[],int n){
	for(int i=0;i<n-1; i++){
		for(int j=i+1; j<n;j++){
			if(a[i]>a[j]) scambia(a[i],a[j]);
        }
	}
}


//ordinamento per inserimento

void ord_inserimento(int a[], int n)
{  
	int i,j,valore;  
	for (i=1; i <n; i++) // i identifica il sottovettore A[0]..A[i] 
   	{	
   		valore=a[i];
   		j=i-1; // Attraversiamo il vettore partendo da A[i] e cercando la posizione j 
   			// dove inserire l'elemento destinazione
   		while (j>=0 && a[j]>valore) 
   			{
   				a[j+1]=a[j]; // Spostiamo gli elementi a destra per far spazio  
   				j--;		// all'elemento in posizione i 
   			}
   		a[j+1]=valore;
   	}
}   


//ordinamento bubble sort

void bubble_sort(int a[],int n)
{
	for(int i=0; i<n-1; i++)
	{
		for(int j=0;j<n-i-1;j++)
		{
			if(a[j]>a[j+1]) scambia(a[j],a[j+1]);
		}
	}
}
		

void selection_sort(int a[],int n)
{
	int temp;
    for(int i=0;i<n-1;i++)
    {
	    int min=i;
        for(int j=i+1;j<n;j++)
        	if (a[j]<a[min])
        	    min=j;
        temp=a[min];
        a[min]=a[i];
        a[i]=temp;
    }
}



int main()
{
	int array[7]={3,5,11,7,1,2,4};
//	ordinamento_scambio(array,7);
//  ord_inserimento(array,7);
    bubble_sort(array,7);
	stampa(array,7);
}













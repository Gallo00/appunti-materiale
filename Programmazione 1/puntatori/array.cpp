#include <iostream>
using namespace std;

//operatore new



	void funzione_array(int array[],int n)   //si potrebbe scrivere  "int *array"  al posto di   "int array[]"
	{
		int i=0;
		while(i<n)
		{
			array[i]=i;
			cout<<array[i];
			i++;
		}
	}
	
	
	
int main()
	{
	cout<<"decidi la lunghezza dell'array"<<endl;
	int N;
	cin>>N;
	int arr[N];
	
	funzione_array(arr,N);
	
	
	
	
	
	
	
	
	
	
	
	
	}
	
	
	


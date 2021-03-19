#include <iostream>
using namespace std;



void bubble_sortPointer(int* v[],int n)
{
	for(int i=0; i<n-1;i++)
	{
		for(int k=0; k<n-1-i;k++)
		{
			if(*v[k]>*v[k+1])
			{
				int *temp=v[k];
				v[k]=v[k+1];
				v[k+1]=temp;
			}
		}
	}
}


int main()
{
	int vec[10]={4,3,5,2,1,6,7,9,10,8};
	int* vec_pointer[10];
	
	for(int i=0; i<10; i++)
	{
		vec_pointer[i]=vec+i;
	}
	bubble_sortPointer(vec_pointer,10);
	
	for(int i=0; i<10;i++){
		cout<<*vec_pointer[i]<<" ";
	}
}
				
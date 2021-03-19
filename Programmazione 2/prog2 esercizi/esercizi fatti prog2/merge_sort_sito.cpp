#include <iostream>
#include <fstream>
using namespace std;

void merge(int arr[],int sx,int cx,int dx,int n);

int merge_sort(int arr[],int sx,int dx,int n)
{
	if(sx<dx)
	{
		int sum=arr[sx];
		
		int cx=(sx+dx)/2;
		sum=sum+merge_sort(arr,sx,cx,n);
        sum=sum+merge_sort(arr,cx+1,dx,n);
		merge(arr,sx,cx,dx,n);
		return sum;
	}
	return 0;
}


void merge(int arr[],int sx,int cx,int dx,int n)
{
	int i=sx;
	int j=cx+1;
	int arr_b[n];  //array di supporto
	int k=sx; //indice per arr_b
	while(i<=cx && j<=dx)
	{
		if(arr[i]<=arr[j])
		{
			arr_b[k]=arr[i];
			i++;
		}
		else
		{
			arr_b[k]=arr[j];
			j++;
		}
		k++;
	}
	
	for(i;i<=cx;i++)
	{
		arr_b[k]=arr[i];
		k++;
	}
	
	for(j;j<=dx;j++)
	{
		arr_b[k]=arr[j];
		k++;
	}
	
	for(int l=sx; l<=dx;l++)
	{
		arr[l]=arr_b[l];
	}
	
}

int main()
{
	fstream miofile("input_merge.txt",fstream::in);
	fstream outfile("output.txt",fstream::out);
	
	for(int riga=0; riga<100; riga++)
	{
		int lung;
		miofile>>lung;
		int arr[lung];
		for(int i=0; i<lung;i++)
		{
			int a;
			miofile>>a;
			arr[i]=a;
		}
		
		int somma=merge_sort(arr,0,lung-1,lung);
		outfile<<somma<<endl;
	}
	miofile.close();
	outfile.close();
}



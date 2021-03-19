#include <iostream>
#include <fstream>
using namespace std;


int calcola_elementi_fibo(int x)
{
	int a=1;
	int b=2;
	int c;
	int counter=2;
	while(c<=x)
	{
		c=a+b;
		a=b;
		b=c;
		counter++;
	}
	return counter-1;
}
	
	
	
	
int fibonacci(int &a,int &b)
{
	return a+b;
}



int main()
{
	fstream miofile("input.txt",fstream::in);
	fstream outfile("output.txt",fstream::out);
	
	for(int riga=0; riga<100;riga++)
	{
		int x;
		miofile>>x;
		int num=calcola_elementi_fibo(x);
		int *array=new int[num];
		array[0]=1;
		array[1]=2;
		int i=2;
		while(i<num)
		{
			array[i]=fibonacci(array[i-1],array[i-2]);
			i++;
		}
		
		int somma=0;
		int array_bin[num];
		int j=num-1;
		while(j>=0)
		{
			if(somma+array[j]>x)
			{
				array_bin[j]=0;
			}
			else
			{
				somma=somma+array[j];
				array_bin[j]=1;
			}
			
			j--;
		}
    
	    for(int n=0; n<num;n++)
		{
			outfile<<array_bin[n];
		}
		outfile<<endl;
		delete []array;
		
	}
	miofile.close();
	outfile.close();

	
}







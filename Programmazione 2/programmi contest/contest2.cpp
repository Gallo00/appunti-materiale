#include <iostream>
#include <fstream>
using namespace std;


void riduci(int array[] ,int min, int i , int j)
{
	for(i;i<=j;i++)
	{
		array[i]=array[i]-min;
	}
}


int trova_minore(int array[] , int i, int j)
{
	int min=array[i];
	for(i=i+1; i<=j; i++)
	{
		if(min>array[i])
		{
			min=array[i];
		}
	}
	return min;
}


int main()
{
	fstream miofile("input.txt" , fstream::in);
	fstream outfile("output.txt" , fstream::out);
	
	for(int riga=0; riga<100; riga++)
	{
		
		int x;
		miofile>>x;
		int scheletro[x];
		for(int i=0; i<x; i++){
			int a;
			miofile>>a;
            scheletro[i]=a;   		//for miofile>>
		} 
		int c=0;  //counter
		bool finito=false;
		while(!finito)
		{
		
		    int k=0, i=0;
			bool sentinella=true;
		    while(i<x && sentinella)
		    {
			    if(scheletro[i]!=0)  //trovare primo valore nell'array non 0
			    {
				    k=i;
					sentinella=false;
			    }
			    i++;
		    }
		    int h=x-1;
			i=x-1;
		    while(i>=k && h>0)
		    {
			    if(scheletro[i]==0)    //trova ultimo valore nell'array non 0
			    {
				    h=i-1;
			    }
			    i--;
		    }
			
			//se k e h finiscono per coincidere e l'elemento in quella posizione è 0, significa che l'array ha tutti 0.
		    
		    if(h==k && scheletro[h]==0)
			{
				finito=true;
			}
			else
			{
				int num_macchina=trova_minore(scheletro,k,h);  //trova il minore della sequenza
			    riduci(scheletro,num_macchina,k , h); 		
				c=c+num_macchina;
			}
		
		}
		outfile<<c<<endl;
	} 
	miofile.close();
	outfile.close();
	
}
		
		
		
		
		
		
		
		
		
		
		
			
			
			
			
			
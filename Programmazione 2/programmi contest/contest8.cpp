#include <iostream>
#include <fstream>
using namespace std;

bool indice_contenuto(int a[],int n,int k)
{
	for(int i=0; i<n;i++)
	{
		if(a[i]==k)
		{
			return true;
		}
	}
    return false;
}

int ricerca_carattere(char a, string b,int i,int k,int* array_ind,int n)
{
	while(i<k)
	{
		if(a==b[i] && !(indice_contenuto(array_ind,n,i)) )
		{
			return i;
		}
		i++;
	}
	return -1; //non lo ha trovato
}


bool ricerca_meno_uno(int* a,int n)
{
	for(int i=0; i<n;i++)
	{
		if(a[i]==-1)
		{
			return true;
		}
	}
	return false;
}

void Stampa (int a[], int n) 
{
	cout<<"[";
	for (int i=0; i<n;i++) 	
		cout << a[i] << " ";
    cout<<"]";
	cout << endl;  
}

int num_perm(string parola,string lettera)
{
	int i=0;
	int counter=0;
	while(i<lettera.length()-parola.length()+1)
	{
		int x=parola.length();
		int array_indici[x];
		for(int j=0; j<x;j++)
		{
			array_indici[j]=-1;
		}  
		
		for(int j=0; j<x;j++)
		{
			int h=ricerca_carattere(parola[j],lettera,i,i+x,array_indici,x);
			array_indici[j]=h;		
		}
		
		if(!ricerca_meno_uno(array_indici,x))
		{
			counter++;
		}
		
		i++;
	}
	return counter;
}	
		
	
		
	




int main()
{
	fstream miofile("input.txt",fstream::in);
	fstream outfile("output.txt",fstream::out);

    for(int riga=0; riga<100;riga++)
	{
		string parola;
		miofile>>parola;
	
		string lettera;
		miofile>>lettera;
		
/*		if(riga<5)
		{
			cout<<parola<<" "<<lettera<<endl;
		}
		*/
		
		int x=num_perm(parola,lettera);
//		cout<<x<<endl;
	    outfile<<x<<endl;
	}
	
	miofile.close();
	outfile.close();
}
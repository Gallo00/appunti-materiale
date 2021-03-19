#include <iostream>
#include <fstream>
#include <limits>
using namespace std;


void stampa(int a[],int n)
{
	cout<<"[";
	for(int i=0; i<n;i++)
	{
		cout<<a[i]<<" ";
	}
	cout<<"] \n ";
}



bool indice_gia_preso(int a[],int j,int n)
{
	if(n==0)
	{
		return false;
	}
	else
	{
		for(int i=0; i<n;i++)
		{
			if(a[i]==j)
			{
				return true;
			}
		}
	}
	return false;
}

bool indice_contenuto(int a[],int j,int n)
{
	for(int i=0; i<n;i++)
	{
		if(a[i]==j)
		{
			return true;
		}
	}
    return false;
}



int main()
{
	fstream miofile("input.txt",fstream::in);
	fstream outfile("output.txt",fstream::out);
	
	for(int riga=0; riga<100;riga++)
	{
/*		bool ok=false;
		if(riga==0 || riga==1)
		{
			ok=true;
		} */
		int dolci;
		miofile>>dolci;
		int voti[dolci*2];
		for(int i=0; i<dolci*2;i++)
		{
			int a;
			miofile>>a;
			voti[i]=a;
		}
        
	/*	if(ok)
		{
			cout<<"array inziale=";
			stampa(voti,dolci*2);
		}  */
		int differenze[dolci];
		for(int i=0, k=0; i<dolci;i++,k=k+2)
		{
			differenze[i]=voti[k]-voti[k+1];
		}
		
	/*	if(ok)
		{
			cout<<"array_diff";
			stampa(differenze,dolci);
		}  */
		
		int indici_max[dolci/2];
	    for(int i=0; i<dolci/2;i++)
		{

			int max=INT8_MIN;
			int k=0;
			for(int j=0; j<dolci;j++)
			{
				if(differenze[j]>max && !indice_gia_preso(indici_max,j,i))
				{
					max=differenze[j];
					k=j;
				}
			}
			indici_max[i]=k;
		}
	/*	if(ok)
		{
		cout<<"array indici_max=";
        stampa(indici_max,dolci/2);
		}
		*/
		int somma_montalbano=0;
		int h=0;
		int somma_francesco=0;
		
		for(int i=0; i<dolci;i++)
		{

			if(indice_contenuto(indici_max,i,dolci/2))  //controllare se i è contenuto in indici_max
			{

				somma_montalbano=somma_montalbano+voti[2*i];

			}
			else
			{
				somma_francesco=somma_francesco+voti[2*i+1];
			}
		}
		
		int somma_totale= somma_montalbano+somma_francesco;
		outfile<<somma_totale<<endl;
	/*	if(ok)
		{
		cout<<endl<<somma_totale<<"\n \n \n";
		} */
	}
	miofile.close();
	outfile.close();
}
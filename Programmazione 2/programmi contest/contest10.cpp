#include <iostream>
#include <fstream>

using namespace std;


void stampa(int arr[],int n)
{
	cout<<"[";
	for(int i=0; i<n; i++)
	{
		cout<<arr[i]<<" ";
	}
	cout<<"]"<<endl;
}


int guardia(int arr[], int i, int j,int A)  //deve vedere se ci sono almeno due guardie nel gruppo
{
	int k=i;
	int c=0;

	for(int k=i; k<=j;k++)
	{
		if(arr[k]==1)
			c++; 
	}
	
	if(c>=A)
	{
//		cout<<"guardie_da_aggiungere="<<0<<endl;
		return 0;  //non serve nessuna guardia giurata da posizionare nel gruppo
	}
	else
	{
		int guardie_da_aggiungere=A-c;
		for(j; j>=i , A-c>0 ;j--)
		{
			if(arr[j]==0)
			{
				arr[j]=1;
				c++;
			}
		}
//		cout<<"guardie_da_aggiungere="<<guardie_da_aggiungere<<endl;
		return guardie_da_aggiungere;
	}
}




int main()
{
	
	fstream miofile("input.txt",fstream::in);
	fstream outfile("output.txt",fstream::out);
	
	for(int riga=0; riga<100; riga++)
	{
		int N;
		miofile>>N;  //num gioiellerie
		
		int L;
		miofile>>L;  //num di gioiellerie di un gruppo
		
		int A;
		miofile>>A;  //num min guardia per ogni gruppo
		
		int gioielleria[N];
		for(int i=0; i<N; i++)
		{
			int a;
			miofile>>a;
			gioielleria[i]=a;
		}
		
	//	stampa(gioielleria,N);
	//	cout<<endl<<endl<<endl<<endl;
		
		
		int counter=0;
		int i=0;
		int j;
		for(i, j=i+L-1 ;i<=N-L ;i++,j++)
		{
			counter=counter+guardia(gioielleria,i,j,A);
//			stampa(gioielleria,N);
		}
//		cout<<counter<<endl;
        outfile<<counter<<endl;
	}
	
	miofile.close();
	outfile.close();
		
			
}
	
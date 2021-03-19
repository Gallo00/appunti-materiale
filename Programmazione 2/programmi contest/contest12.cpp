#include <iostream>
#include <fstream>
using namespace std;



void stampa(int a[], int n){
	cout<<" [";
	for(int i=0; i<=n;i++){
		cout<<a[i]<<" ";
	}
	cout<<"]"<<endl;
}

void scambia(int &a, int &b){
	int var=a;
	a=b;
	b=var;
}

void ordinamento_scambio(int a[],int n){
	for(int i=0;i<n-1; i++){
		for(int j=i+1; j<n;j++){
			if(a[i]>a[j]) scambia(a[i],a[j]);
        }
	}
}

void calcolo_freq(int num_occ[],int l,int num_freq[])
{
	int max=num_occ[0];
	for(int i=1; i<=l;i++)
	{
		if(max<num_occ[i])
			max=num_occ[i];
	}
	
	for(int i=0; i<=l;i++)
	{
		if(num_occ[i]==max)
			num_freq[i]=num_freq[i]+1;
	}
}


void incremento_occor(int num_occ[],int i)
{
	num_occ[i]=num_occ[i]+1;
}

int ricerca_tip(int x,int tip_doc[],int g,int num_occ[])
{
	//se c'è l'occorrenza aumenta di 1 il suo valore
	//se non c'è viene inserito,la sua occorrenza viene messa a 1
	
	for(int i=0; i<=g;i++)
	{
		if(x==tip_doc[i])
		{
			incremento_occor(num_occ,i);
			return g;
	    }
	}
	g=g+1;
	tip_doc[g]=x;
	num_occ[g]=1;
	return g;
}



int main()
{
	fstream miofile("input.txt", fstream::in);
	fstream outfile("output.txt",fstream::out);
	
	for(int riga=0; riga<100;riga++)
	{
		int N;
		miofile>>N;
		
		int documenti[N];
		for(int i=0; i<N;i++)
		{
			int a;
			miofile>>a;
			documenti[i]=a;
		}
		
		
		
		
		int tip_doc[N];
		int num_occ[N];
		int num_freq[N];
		for(int i=0; i<N;i++)
		{
			num_freq[i]=0;
			num_occ[i]=0;	
		}
		int k=-1;
		
		for(int i=0; i<N; i++)
		{
			k=ricerca_tip(documenti[i],tip_doc,k,num_occ);
			calcolo_freq(num_occ,k,num_freq);
		}
		
		int c=0;
		for(int i=0; i<=k;i++)
		{
			if(num_freq[i]>0)
			{
				c++;
			}
		}
/*		cout<<"tip - occ - freq"<<endl;
		stampa(tip_doc,k);
		stampa(num_occ,k);
		stampa(num_freq,k);
		cout<<endl<<endl;  */
		
		
		int vett[c];
		int i_c=0;
		int i_k=0;
		while(i_c<c && i_k<=k)
		{
			if(num_freq[i_k]>0)
			{
				vett[i_c]=tip_doc[i_k];
				i_c++;
			}
			i_k++;
		}
		
		//algoritmo ordinamento su vett e stampa
		
		ordinamento_scambio(vett,c);
		
		outfile<<c<<" ";
		for(int i=0; i<c;i++)
		{
			outfile<<vett[i]<<" ";
		}
		outfile<<endl;
		

	}
	miofile.close();
	outfile.close();
	return 0;
}
#include <iostream>

using namespace std;

int main()
{
	float n;
	
	
	cout<<"scegli N"<<endl;
	cin>>n;
	int N=n+0.5;
//	cout<<N<<endl;
	float m;
	cout<<"scegli M"<<endl;
	cin>>m;
	int M=m+0.5;
//	cout<<M<<endl
	
	cout<<N<<"x"<<M<<endl;
	float A[N][M];
	int i=0;
	int j=0;
	while(i<N)
	{
		j=0;
		while(j<M)
		{
			cout<<"scegli valore a caso in casella"<<i<<"x"<<j<<endl;
			cin>>A[i][j];
			j++;
			
		}
		
		i++;
	}
	i=0;
	j=0;
	while(i<N)
	{
		j=0;
		while(j<M)
		{
	
		cout<<A[i][j]<<"  ";
		j++;
			
		}
		cout<<endl;
		i++;
	}
	
	cout<<" scegli uno scalare per cui moltiplicare la matrice"<<endl;
	float k;
	cin>>k;
	i=0;
	j=0;
	while(i<N)
	{
		j=0;
		while(j<M)
		{
			A[i][j]=k*A[i][j];
			cout<<A[i][j]<<"  ";
			j++;
		}
		cout<<endl;
		i++;
	}
	
	if(N<M)
	{
		M=N;
	}
	else
	{
		N=M;
	}
	i=0;
	j=0;
	cout<<endl;
	while(i<N)
	{
		j=0;
		while(j<M)
		{
			cout<<A[i][j]<<"  ";
			j++;
		}
		cout<<endl;
		i++;
	}
	
	
	
	
	
	
}

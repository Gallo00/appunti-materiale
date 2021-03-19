#include <iostream>
using namespace std;

#define N 5
#define M 10
#define L 15

void funzione(int w[][M][L])  //int (*w)[M][L]
{
	int i=0;
	while(i<N)
	{
		int j=0;
		while(j<M)
		{
		   int k=0;
		   while(k<L)
		   {
		   	w[i][j][k]=i;
		   	cout<<w[i][j][k]<<" ";
		   	k++;
		   }
		   cout<<endl;
		   j++;
		}
		cout<<endl;
		i++;
	}
	cout<<"\n \n \n \n";
}

int main()
{
	int x[N][M][L];
	funzione(x);
}

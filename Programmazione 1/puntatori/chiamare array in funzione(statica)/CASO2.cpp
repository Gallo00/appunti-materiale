#include <iostream>
#define N 5
#define M 10
using namespace std;
	
void funzione1(int v[][M],int n)     //prototipo della funzione,stiamo usando un array dallo STACK e dobbiamo specificare le dimensioni (almeno) dalla seconda in poi
{
	int i=0;
	while(i<n)
	{
		int j=0;
		while(j<M)
		{
			v[i][j]=i;
			cout<<v[i][j]<<" ";
			j++;
		}
		cout<<endl;
		i++;
    }
} 
		


int main()
{
		int x[N][M];
		funzione1(x,N);
		
}	

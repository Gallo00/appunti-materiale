#include <iostream>
#include <string>

using namespace std;

int main()
{
	
	//allocare dinamicamente(e inizilizzare) una matrice n*m,in ogni cella è contenuta un puntatore a string*
	
	//per allocare sullo heap allora, la matrice si presenterà nella forma 
	//         string* ** matrice;
	
	int n=4;
	int m=5;
	string* **matrice;
	matrice= new string**[n];
	
	
	for(int i=0;i<n;i++)
	{
		matrice[i]=new string*[m];
		for(int j=0;j<m;j++)
		{
			string x;
			cout<<"inserisci una stringa"<<endl;
			cin>>x;
			matrice[i][j]=new string(x);
		}
	}
	
	for(int a=0;a<n;a++)
	{
		for(int b=0;b<m;b++)
		{
			cout<<(*matrice[a][b])<<" ";
		}
		cout<<endl;
	}
	
	
	
}

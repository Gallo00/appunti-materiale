#include <iostream>
#include <string>

#define n 3
#define m 2 
using namespace std;

bool func(string* P[n][m],short a,short b,string s)
{
	int l1=s.length();
	int l2=0;
	int j=0;
	while(j<m)
	{
		int i=0;
		int c2=0;
		while(i<n)
		{
			l2=(*P[i][j]).length();
			int k=0;
			int q;
			int c1;
			while(k<l2)
			{
				q=0;
				c1=0;
				while(q<l1)
				{
					if((*P[i][j]).at(k+q)==s[q])
					{
						c1++;
					}
					q++;
				}
				if(c1==l1)
				{
					c2++;
				}
				k++;
			}
			i++;
		}
		if(c2>a&&c2<=b)
		{
			return true;
		}
		j++;
	}
	return false;
}





 int main()
 {
    string* **matrice;
	matrice= new string**[n];
	
	//ora dobbiamo allocare ogni cella puntata da un puntatore di tale array
	// notare allora che ogni cella punta a un altro array
	
    //matrice[2]=new string*[m]  //ogni cella punterà a un array di dim m(ovvero il numero di colonne)
    //così abbiamo allocato dinamicamente la cella puntata puntata dalla terza casella dell'array iniziale
    int i=0;
    int j=0;
    
    while(i<n)
    {
    	matrice[i]=new string*[m];    //si usa string* poichè gli elementi della matrice sono puntatori a stringhe,non stringhe
    	//fatto questo, string* dovrà puntare a una certa stringa
    	j=0;
    	while(j<m)
    	{
    		string x;
    		cout<<"inserisci stringa"<<endl;
    		cin>>x;
    		matrice[i][j]=new string(x);
    		
    		j++;
		}
		i++;
    	
	}
	i=0;
	while(i<n)
	{
		j=0;
		while(j<m)
		{
			cout<<(*matrice[i][j])<<" ";
			j++;
		}
		cout<<endl;
		i++;
	}
	string s;
	cout<<"inserisci stringa della func";
	cin>>s;
	cout<<func(matrice,2,4,s);
	
	
	
	
	
 	
 }















#include <iostream>
#include <string>

using namespace std;


//esercizio stringhe sorelle puntate da due puntatori di una medesima colonna in una matrice
//che appunto ha come elementi puntatori a stringhe



bool funzione(string* **mat,int n,int m)
{
	
	int aux[n];
	//utilizziamo un array ausiliario in cui metteremo in ogni cella
	// il valore c,ovvero il contatore di vocali di ogni stringa
	
	//effettuare un controllo per colonne
	int j=0; //indice colonna
	while(j<m)
	{
		int i=0; //indice riga
		while(i<n)
		{
			//*mat[i][j] è la stringa puntata dal puntatore contenuto nella cella di coordinate i e j
			//*mat[i][j].length() indica perciò la lunghezza di questa stringa
			
			//effettuare perciò un controllo su tutti i caratteri della stringa
			unsigned int k=0;
			int c=0;  //contatore vocali in una stringa, va resettata a 0 prima di ogni controllo per stringa(riga 33)
			
			while(k<(*mat[i][j]).length())   //conviene usare come indice un insigned poichè la lunghezza di una stringa è sicuramente >0, ma comunque non
			{                                    // è un errore
				switch((*mat[i][j]).at(k))
				{
					case 'a':
					case 'e':
					case 'i':
					case 'o':
					case 'u':
						c++;
					break;
				
				}
				k++;
			}
			aux[i]=c;
			i++;
		}
		i=0;
		cout<<"aux=";
		while(i<n)
		{
			cout<<aux[i]<<" ";
			i++;
		}
		cout<<endl;
		int h=0;
		int l=h+1;
		while(h<n-1)
		{
		  	l=h+1;
		  	while(l<n)
		  	{
		  	   if(aux[h]==aux[l])
				{
				 	return true;
				}
			 l++;
			}
			h++;
		}
		j++;
	}
	
	return false;	
}

int main()
{
	
	int n=3;
	int m=3;
	int i=0;
	int j=0;
	
	string* **matrice;
	matrice= new string**[n]; //allocazione dinamica dell'array di dimensione n sullo heap.
	
	//ora dobbiamo allocare ogni cella puntata da un puntatore di tale array
	// notare allora che ogni cella punta a un altro array
	
    //matrice[2]=new string*[m]  //ogni cella punterà a un array di dim m(ovvero il numero di colonne)
    //così abbiamo allocato dinamicamente la cella puntata puntata dalla terza casella dell'array iniziale
    
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
	
	
cout<<funzione(matrice,n,m);
	
	
}























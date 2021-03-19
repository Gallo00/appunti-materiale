#include <iostream>
#include <fstream>

using namespace std;


struct Nodo
{
	int val;
	Nodo* succ;
	
	int colonna; //serve per capire in quale colonna si trova il nodo
};

class Lista
{
	public:
	      
		Nodo* testa;
		Lista() {testa=NULL;}
		
		void insert(int dato) //inserimento in coda
		{
			Nodo* nuovo=new Nodo;
			nuovo->val=dato;
			nuovo->succ=NULL;
			
			if(testa==NULL)
			{
				testa=nuovo;
				nuovo->colonna=0;
			}
			else
			{
				Nodo* iter=testa;
				while(iter->succ!=NULL)
					iter=iter->succ;
				iter->succ=nuovo;
				
				nuovo->colonna=iter->colonna + 1;
			}
		}
		
		int elemento_colonna(int j)
		{
			Nodo* iter=testa;
			while(iter!=NULL)
			{
				if(iter->colonna==j)
					return iter->val;
				iter=iter->succ;
			}
			return -1; //non dovrebbe mai succedere
		}
		
		void stampa_file(ofstream & f)
		{
			Nodo* iter=testa;
			while(iter!=NULL)
			{
				f<<iter->val<<" ";
				iter=iter->succ;
			}
		}
	
};

class Matrice
{
	public:
	    int num_righe;
	    int num_colonne;
		
		Lista** righe; //array di puntatori a lista
		
		Matrice(int r,int c)
		{
			num_righe=r;
			num_colonne=c;
			
			righe=new Lista*[num_righe];
			for(int i=0; i<num_righe;i++)
				righe[i]=new Lista;
		}
		
		void crea_mat(int* elementi) //elementi contiene gli elementi presi in input per metterli nella matrice
		{
			int x=0;
			
			for(int i=0; i<num_righe;i++)
			{
				for(int j=0; j<num_colonne;j++)
				{
					righe[i]->insert(elementi[x]);
					x++;
				}
			}
		}
		
		friend Matrice* mat_prodotto(Matrice* X,Matrice* Y,Matrice* result)  
		{
			int elementi_result=result->num_righe * result->num_colonne;
			int arr[elementi_result];
			int counter=0;
			
			/*PRODOTTO RIGHE PER COLONNE
			
			Per ogni riga di X prendo ogni colonna di Y (il numero di righe di X coincide con le colonne di Y)
			creo variabile somma settata a 0
			moltiplico elemento 0 della riga di X con elemento 0 della colonna Y metto risultato in somma, faccio così per ogni elemento
			
			alla fine la variabile somma va messa nella posizione (i,j) della result, dove i indica la riga che ho usato e j la colonna
			*/
			
			for(int i=0; i<X->num_righe;i++)
			{
				for(int j=0; j<Y->num_colonne;j++)
				{
					int somma=0;
					for(int k=0; k<X->num_colonne;k++) //avremmo potuto scrivere anche k<Y->num_righe
					{
						somma= somma + ((X->righe[i]->elemento_colonna(k))*(Y->righe[k]->elemento_colonna(j)));
						
						//X->righe[i]->elemento_colonna(k)  dobbiamo ispezionare ogni elemento della riga i-esima
						//Y->righe[k]->elemento_colonna(j)  dobbiamo ispezionare ogni elemento della colonna j-esima
					}
					
					arr[counter]=somma; //salvataggio risultati intermedi nell'array ausiliario
					counter++;
				}
			}
			
			result->crea_mat(arr);
			return result;
		}
		
		void stampa(ofstream & f)
		{
			for(int i=0; i<num_righe;i++)
				righe[i]->stampa_file(f);
			f<<endl;
		}
	
};

int main()
{
	ifstream miofile("input.txt");
	ofstream outfile("output.txt");
	
	for(int riga=0; riga<100;riga++)
	{
		int n; //righe di mat_1 /righe di mat_result
		int m; //colonne di mat_1 / righe di mat_2
		int p; //colonne di mat_2 /colonne di mat_result
		
		miofile>>n;
		miofile>>m;
		miofile>>p;
		
		//riempimento mat_1
		Matrice* mat_1=new Matrice(n,m);
		int elementi1[n*m];
		for(int i=0; i<n*m;i++)
		{
			int a;
			miofile>>a;
			elementi1[i]=a;
		}
		mat_1->crea_mat(elementi1);
		
		//riempimento mat_2
		Matrice* mat_2=new Matrice(m,p);
		int elementi2[p*m];
		for(int i=0; i<p*m;i++)
		{
			int a;
			miofile>>a;
			elementi2[i]=a;
		}
		mat_2->crea_mat(elementi2);
		
		//prodotto
		Matrice* result=new Matrice(n,p);
		result=mat_prodotto(mat_1,mat_2,result);
		
		//stampa
		result->stampa(outfile);
	}
	return 0;
};


































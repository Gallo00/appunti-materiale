#include <iostream>
#include <fstream>
using namespace std;


template <class H> class Nodo
{
	public:
	
	    H* array_disordinato;
		H* array_ordinato;
		int dim;
		
		Nodo<H>* padre;
		Nodo<H>* sin;
		Nodo<H>* des;
		
		Nodo(H* arr,int sx,int dx)
		{
			dim=dx-sx+1;
			int x=sx;
			array_disordinato=new H[dim];
			for(int i=0; i<dim;i++)
			{
				array_disordinato[i]=arr[x];
				x++;
			}
			
			array_ordinato=new H[dim];
		}
		
		void inserimento_ordinato(H* arr,int sx) //inizializza l'array corrispettivo ORDINATO
		{
			int x=sx;
			for(int i=0;i<dim;i++)
			{
				array_ordinato[i]=arr[x];
				x++;
			}
		}
		
		void stampa(ofstream & f) //stampa singolo nodo
		{
			f<<"[ ";
			
			for(int i=0; i<dim;i++) f<<array_disordinato[i]<<" ";
			
			f<<": ";
			
			for(int i=0; i<dim;i++) f<<array_ordinato[i]<<" ";
			
			f<<"] ";
		}
	
};


template <class H> class Albero{
	
	public:
	    Nodo<H>* radice;
		
		Albero() {radice=NULL;}
		
		//NON è un albero binario di ricerca 
		
		
		Nodo<H>* insert(H* arr,int sx,int dx,Nodo<H>* parent)  //parent è il padre, arr[sx] ... arr[dx] l'array da buttare nel nuovo nodo 
		{                                                       // che sarà figlio di parent
			Nodo<H>* nuovo=new Nodo<H>(arr,sx,dx);
			nuovo->sin=nuovo->des=NULL;
			
			if(parent==NULL)radice=nuovo; //se è vuoto diventa radice
			else 
			{
				nuovo->padre=parent; //suo padre diventa parent
				if(parent->sin==NULL) parent->sin=nuovo; //facciamo così in modo che il primo figlio ad essere inserito il il sin
				else parent->des=nuovo;
			}
			return nuovo; //ritorniamo il nuovo perchè lo useremo come padre nel successivo inserimento
		}
		
		void stampa(ofstream & f)
		{
			preorder(f,radice);
			f<<endl;
		}
		
		void preorder(ofstream & f,Nodo<H>* sotto_rad)
		{
			if(sotto_rad!=NULL)
			{
			    sotto_rad->stampa(f);
			    preorder(f,sotto_rad->sin);
			    preorder(f,sotto_rad->des);
			}
		}
	
};

template <class H>
void merge(H arr[],int sx,int cx,int dx,int n)
{
	int i=sx;
	int j=cx+1;
	
	H b[n];
	int k=sx;
	while(i<=cx && j<=dx)
	{
		if(arr[i]<=arr[j])
		{
			b[k]=arr[i];
			i++;
		}
		else
		{
			b[k]=arr[j];
			j++;
		}
		k++;
	}
	
	for(i;i<=cx;i++,k++)
		b[k]=arr[i];
	
	for(j;j<=dx;j++,k++)
		b[k]=arr[j];
	
	for(int l=sx;l<=dx;l++)
		arr[l]=b[l];
	
}


//supponendo ogni nodo dell'albero abbia 2 chiavi, una che è il sottoarray e l'altra è il sottoarray ORDINATO

template <class H>
void merge_sort(H a[], int sx,int dx,int n,Nodo<H>* parent,Albero<H>* bst)
{
	if(sx<dx) //non avrebbe alcun senso se l'indice estremo sinistro fosse maggiore dell'indice estremo destro
	{
		//inserimento nell'albero del sottoarray   a[sx] ... a[dx]
		
		Nodo<H>* p=bst->insert(a,sx,dx,parent);
		
	    int cx=((sx+dx)/2);
		
		if((sx+dx)%2==0)cx=cx-1;  //faro vuole che la metà più grande venga messa a destra
		
	    merge_sort(a,sx,cx,n,p,bst);
	    merge_sort(a,cx+1,dx,n,p,bst);
	    merge(a,sx,cx,dx,n);
		
		p->inserimento_ordinato(a,sx);
		
		//inserimento nell'albero del sottoarray  a[sx] ... a[dx]  (arrivati a questo punto sarà ordinato)
	}
	
	if(sx==dx)
	{
		//inserimento nell'albero dell'array  a[sx] (ha un'unica cella) nella parte disordinata
		Nodo<H>* p=bst->insert(a,sx,dx,parent);
		
		p->inserimento_ordinato(a,sx);
		// inserimento nell'albero dell'array a[sx] (ha un'unica cella) nella parte ordinata
	}
	
}

int main()
{
	ifstream miofile("input.txt");
	ofstream outfile("output.txt");
	
	for(int riga=0; riga<100; riga++)
	{
		string tipo;
		miofile>>tipo;
		
		int lung;
		miofile>>lung;
		
		if(tipo=="int")
		{
			int arr[lung];
			for(int i=0; i<lung; i++)
			{
				int a;
				miofile>>a;
				arr[i]=a;
			}
			
			Albero<int>* bst=new Albero<int>;
			Nodo<int>* par=NULL;
			merge_sort(arr,0,lung-1,lung,par,bst);
			
			bst->stampa(outfile);
		}
		
		if(tipo=="char")
		{
			char arr[lung];
			for(int i=0; i<lung; i++)
			{
				char a;
				miofile>>a;
				arr[i]=a;
			}
			
			Albero<char>* bst=new Albero<char>;
			Nodo<char>* par=NULL;
			merge_sort(arr,0,lung-1,lung,par,bst);
			
			bst->stampa(outfile);
		}
		
		if(tipo=="double")
		{
			double arr[lung];
			for(int i=0; i<lung; i++)
			{
				double a;
				miofile>>a;
				arr[i]=a;
			}
			
			Albero<double>* bst=new Albero<double>;
			Nodo<double>* par=NULL;
			merge_sort(arr,0,lung-1,lung,par,bst);
			
			bst->stampa(outfile);
		}
		
		if(tipo=="bool")
		{
			bool arr[lung];
			for(int i=0; i<lung; i++)
			{
				bool a;
				miofile>>a;
				arr[i]=a;
			}
			
			Albero<bool>* bst=new Albero<bool>;
			Nodo<bool>* par=NULL;
			merge_sort(arr,0,lung-1,lung,par,bst);
			
			bst->stampa(outfile);
		}
	}
	
	miofile.close();
	outfile.close();
};










































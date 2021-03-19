#include <iostream>
#define DIM 20
using namespace std;



void merge(int a[], int sx,int cx,int dx){
	
	int i=sx;
	int j=cx+1;
	
	int k=sx;
	int b[DIM];  //array di supporto //dimensione array che potrebbe essere passata come argomento della funzione
	
	while(i<=cx && j<=dx)
	{
		if(a[i]<=a[j])
		{
			b[k]=a[i];
			i++;
		}
		else
		{
			b[k]=a[j];          
			j++;
		}
		k++;
	}                       //uno dei due sottoarray sarà finito, ma le celle di b non sono ancora del tutto inizializzate
	
	for(i;i<=cx;i++ , k++){
		b[k]=a[i];
	}
	
	for(j; j<=dx;j++,k++){
		b[k]=a[j];
	}
	
	for(int i=sx; i<=dx; i++){
		a[i]=b[i];
	}
	
}

void merge_sort(int a[], int sx,int dx){
	if(sx<dx) //non avrebbe alcun senso se l'indice estremo sinistro fosse maggiore dell'indice estremo destro
	{
	int cx=(sx+dx)/2;
	merge_sort(a,sx,cx);
	merge_sort(a,cx+1,dx);
	merge(a,sx,cx,dx);
	}
}
	
	
	
	


void Stampa (int a[], int n) 
{
	cout<<"[ ";
	for (int i=0; i<n;i++) 	
		cout << a[i] << " ";
	cout <<"]" <<endl;  
}

int main(){
	int vettore[DIM]={12,3,6,5,131,7,43,89,54,34,11,21,13,4,90,15,16,71,19,31};

    cout << "Vettore iniziale \n"; 
    Stampa(vettore,DIM);
    merge_sort(vettore,0,DIM-1);    //scriviamo DIM-1 perchè l'estremo a destra è 19(infatti stiamo passando gli estremi, non la dimensione dell'array)
    cout << endl << "Vettore ordinato " << endl; 
    Stampa(vettore,DIM); 
	
	
}


	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
		
	
	
	
	
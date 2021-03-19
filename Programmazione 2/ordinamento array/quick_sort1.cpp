#include<iostream>
using namespace std;

void scambia (int& a, int& b) 
{  
	int aux=a; 
	a=b; 
   	b=aux; 
}   


void Stampa (int a[], int n) 
{
	for (int i=0; i<n;i++) 	
		cout << a[i] << " ";
	cout << endl;  
}


void quick_sort1(int a[], int sx, int dx){
	if(sx<=dx){  //la procedura avviene entro un certo limite, ovvero sx e dx devono al massimo combaciare
		
	int cx=(sx+dx)/2;
	int pivot=a[cx];

	scambia(a[cx],a[dx]);

	int i=sx;
	int j=dx-1;
	while(i<j){
		while(a[i]<pivot && i<j){
			i++;

		}
		while(a[j]>pivot && i<j){
			j--;

		}
		
		scambia(a[i],a[j]);
	}

	scambia(a[i],a[dx]);
	quick_sort1(a,sx,i-1);
	quick_sort1(a,i+1,dx);
	}
}

int partizione(int a[],int sx,int dx)
{
	int pivot=a[dx];
	int i=sx-1;	
	for(int j=sx; j<dx;j++)
	{
		if(a[j]<=pivot)
		{
			i++;
			scambia(a[i],a[j]);
		}
	}
	scambia(a[i+1],a[dx]);
	return i+1;
	
}


void quick_sort2(int a[],int sx,int dx)
{
	if(sx<dx)
	{                      
	int prossimo_estremo=partizione(a,sx,dx);
	quick_sort2(a,sx,prossimo_estremo-1);
	quick_sort2(a,prossimo_estremo+1,dx);
	}
}



	
int main() 
{//	int n;
	int a[10]={8,1,4,9,6,3,5,2,7,0};
	
	cout << "Vettore iniziale \n"; 
	Stampa(a,10);
	quick_sort2(a,0,9);
	cout << endl << "Vettore ordinato " << endl; 
	Stampa(a,10); 
}









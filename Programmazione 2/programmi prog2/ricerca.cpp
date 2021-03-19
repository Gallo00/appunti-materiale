#include <iostream>
using namespace std;


int ricerca_sequenziale(int a[],int n,int k){
	for(int i=0; i<n;i++){
		if(a[i]==k){
			return i;
		}
	}
	return -1;
}


int ricerca_binaria(int a[], int sx,int dx,int k){   //valida solo se l'array è ordinato
	if(sx==dx){
		if(k==a[sx]){
			return sx;
		}
		else{
			return -1;
		}
	}
	
	int cx=(sx+dx)/2;
	
	if(a[cx]>=k){
		return ricerca_binaria(a,sx,cx,k);
	}
	else{
		return ricerca_binaria(a,cx+1,dx,k);
	}
	
}


int ricerca_binaria_iterativa(int a[],int n,int k){
	int sx=0;
	int dx=n-1;
//	bool trovato=false;
	int indice_ritorno=-1;
	
	while(sx<=dx /*&& !trovato */){
		int cx=(sx+dx)/2;
		
		if(a[cx]>k)
		{
			dx=cx-1;
		}
		else
		{
			if(a[cx]<k)
			{
				sx=cx+1;
			}
			else
			{
				return cx;
//				indice_ritorno=cx;
//				trovato=true;
			}
		}
	}
	return indice_ritorno;
}


int main(){
	
	int a[10]={1,2,3,4,5,6,7,8,9,10};
	int chiave=6;
	
	cout<<"ricerca sequenziale:"<<ricerca_sequenziale(a,10,chiave)<<endl;
	cout<<"ricerca binaria ricorsiva:"<< ricerca_binaria(a,0,9,chiave)<<endl;
	cout<<"ricerca binaria iterativa:"<<ricerca_binaria_iterativa(a,10,chiave)<<endl;
	
}









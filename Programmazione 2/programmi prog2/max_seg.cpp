#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;


int* creaArray(int n){
	int * array= new int[n];
	for(int i=0; i<n; i++){
		array[i]=(rand()%256 )- 128;
	}
	return array;
}

void stampa_array(int * array, int n){
	for(int i=0; i<n;i++){
		cout<<array[i]<<" ";
	}
cout<<endl;
}

int segmento_massimo(int * array, int n){
	int max= array[0];
	
	for(int i=0; i<n; i++){
		int somma=0;
                string stringa="";
		for(int j=i; j<n; j++)
                {
			somma=somma+ array[j];
			if(somma>max)
                        {
				max=somma;
			}
                        cout<<"segmento corrente=";
                        stringa=stringa+" " + to_string(array[j]);
                        cout<<stringa<<" somma="<<somma<<endl;
		}
	}
        cout<<"max="<<max<<endl;
	return max;
}

int main(){
        srand(111222333);
	int * a=creaArray(10);
	stampa_array(a,10);
        segmento_massimo(a,10);
	
	
	
	
	
	
	
	
	
	
	
}
	
		
		
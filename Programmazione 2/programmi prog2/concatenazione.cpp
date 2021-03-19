//Esercizio: Concatenazione di array. 
//Il programma prende due array di 10 elementi ciascuno e 
//restituisce in output un array che contiene 20 elementi. 

#include <iostream>
#include <stdlib.h>
#define DIM 10
using namespace std;

int* creaArray(int x){
	int * array= new int[x];
	for(int i=0; i<x; i++){
		array[i]=(rand()%256)-128;
	}
	return array;
}

void stampaArray(int* array , int x){
	cout<<"[ ";
	for(int i=0; i<x;i++){
		cout<<array[i]<<" ";
	}
	cout<<"]"<<endl;
}

int* concatenaArray(int * array1, int* array2, int x){
	int* array3= new int[2*x];
	for(int i=0; i<x;i++){
		array3[i]=array1[i];
		array3[i+x]=array2[i];
	}
	return array3;
}

int main(){
	int* a=creaArray(DIM);
	stampaArray(a,DIM);
	int* b=creaArray(DIM);
	stampaArray(b,DIM);
	
	int* c=concatenaArray(a,b,DIM);
	stampaArray(c,2*DIM);
	
}
	
	
	
	
	
	
	
	
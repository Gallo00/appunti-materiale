#include <iostream>

using namespace std;

//l'allocazione dinamica avviene in C++ tramite l'operatore "new"
//esso permette di accedere alla sezione di memoria chiamata 
//"heap" o "free store"

int main()
{
	
	int *a=new int(2);             //in questo modo "a" viene allocato dinamicamente nell'HEAP con il valore 2
	cout<<*a<<endl;
	cout<<a<<endl;
	
	double *arr=new double[6];    //allocazione dinamica di un array
	arr[0]=5;
	arr[1]=3;
	arr[2]=8;
	arr[3]=10;
	arr[4]=4;
	arr[5]=5.5;
	cout<<arr<<endl;        //indirizzo della prima cella
	cout<<(a+1)<<endl;      //indirizzo della seconda cella
	cout<<(a+2)<<endl;      //indirizzo della terza cella
	 
	cout<<*arr<<" "<<arr[1]<<" "<<arr[2]<<" "<<arr[3]<<" "<<endl;
	
	
	//LA MEMORIA ALLOCATA DINAMICAMENTE VA LIBERATA SUCCESSIVAMENTE CON L'OPERATORE "DELETE"
	
	delete a;                          //riga 12,il valore della cella è stato cambiato,ma non il valore del puntatore(l'indirizzo)
	cout<<*a<<endl<<a<<endl;
	
	delete []arr;    //riga 15 (deallocazione di un blocco di memoria)
	
	cout<<*arr<<" "<<arr[1]<<" "<<arr[2]<<" "<<arr[3]<<" "<<arr[4]<<" "<<arr[5]<<endl;
	
	
	//buona norma azzerare i puntatori dopo il delete
	a=nullptr;
	cout<<a<<endl;
	
	arr=nullptr;
	cout<<arr<<endl;
	cout<<(arr+1)<<endl;
	cout<<(arr+2)<<endl;
	cout<<(arr+3)<<endl;
	cout<<(arr+4)<<endl;
	cout<<(arr+5)<<endl;
	
	
	
	
	
	
	
	
}

#include<iostream>
#include <cstdlib>
#include <ctime>
#define star 100
using namespace std;

void Stampa (int a[], int n) 
{
	for (int i=0; i<n;i++) 	
		cout << a[i] << " ";
	cout << endl;  
}



bool conosce(int &a , int &b) {   //restituisce true se a conosce b
    
	if(a==star)
	{
		return false;            // se a è la star, non conosce sicuramente b
	}
	else 
	{
		if(b==star)
	    {
		    return true;        // se b è la star, sicuramente a lo conosce
	    }
		else
		{
			return rand()%2;   // se ne a ne b sono la star, c'è una possibilità che a conosca b su e un a possibilità che non lo conosca
		}
	}
	
}

int trova_star(int a[],int n){
	int stella=0;
	for(int i=1;i<n;i++)
	{
		if( conosce(a[stella],a[i]))
		{
			stella=i;
		}
	}
	return stella;
}


int main()
{
	srand(time(NULL));
	int invitati[10]={ 32, 5, 53 , 3, star, 60, 89 , 43 , 41 , 32};
	cout<<trova_star(invitati,10)<<endl;
}
	

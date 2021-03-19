#include <iostream>
#include <stdlib.h>
using namespace std;


bool opinione(int &a,int &b)
{
	if(a==1)
	{
		return b;     //se a è onesto la sua opinione sarà veritiera
	}
	else
	{
		return rand()%2;   //se a è disonesto la sua opinione è imprevedibile
	}
}




int* crea_array_onesti(int* a,int n)
{
	int* array1=new int;   //array con i senatori con un'opinione positiva su i
	int* array2=new int;   //array con i senatori con un'opinione negativa su i
	
	int c1=0;
	int c2=0;
	for(int j=1; j<n;j++)
	{
		if(opinione(a[j],a[0]))
		{
			array1[c1]=a[j];
			c1++;
		}
		else
		{
			array2[c2]=a[j];
			c2++;
		}
	}
	
	
	if(c1>=(n/2)+1)   //i sarebbe onesto e l'array1 conterrebbe tutti  i senatori onesti più qualche disonesto
	{
		array1[c1+1]=a[0];
		return crea_array_onesti(array1,c1+1);
	}
	else
	{
		array2[c2+1]=a[0];
		return crea_array_onesti(array2,c2+1);
	}
	
}


int main()
{
	
    //un senatore è denotato con 0 se è disonesto,1 se è onesto
    int senatori[20]={0,1,0,0,1,1,1,0,1,0,1,0,0,1,0,1,1,0,1,1};
    int* array_onesti=crea_array_onesti(senatori,20);

}










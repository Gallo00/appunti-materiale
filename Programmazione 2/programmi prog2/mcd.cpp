//fare MCD di due interi (iterativa e ricorsiva)

#include <iostream>
using namespace std;

//versione iterativa

int calcola_MCD(int primo, int secondo){   //quest'operazione la faccio nella condizione primo>secondo
	int var;
	
	while(secondo!=0)
	{
		var=secondo;
		secondo=primo%secondo;
		primo=var;
	}
	return primo;
}

int MCD_iterativo(int primo, int secondo)
{
	if(secondo<=primo && primo%secondo==0)
		return secondo;
	else
	{
		if(secondo>primo)
			return calcola_MCD(secondo , primo);
		else
			return calcola_MCD(primo , secondo);
	}
}

int MCD_ricorsivo(int primo, int secondo){
	if(secondo<=primo && primo%secondo==0)
		return secondo;
	else
	{
		if(secondo>primo)
			return MCD_ricorsivo(secondo, primo);
		else
			return MCD_ricorsivo(secondo , primo%secondo);
	}
}







int main(){
	cout<<"MCD iterativo con i 3 casi possibili:"<<endl;
	cout<<MCD_iterativo(8,12)<<endl;
	cout<<MCD_iterativo(12,8)<<endl;
	cout<<MCD_iterativo(10,10)<<endl<<endl;
	
	cout<<"MCD ricorsivo con i 3 casi possibili:"<<endl;
	cout<<MCD_ricorsivo(8,12)<<endl;
	cout<<MCD_ricorsivo(12,8)<<endl;
	cout<<MCD_ricorsivo(10,10)<<endl;
	
	//cout<<MCD_iterativo(11, 4); numero primo quindi darà 1.
	
	
	
}
	
	
		
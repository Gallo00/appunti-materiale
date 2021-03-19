#include <iostream>

using namespace std;

//esempio semplice di una classe

class samuele{
	
	
	
	samuele(); 
	
	int a;
	int b;
	int c;
	
	public:
	samuele(int valore1,int valore2,int valore3){  //funzione samuele;la stiamo definendo
		
		a=valore1;
		b=valore2;  //non fa nulla
		c=valore3;  //non fa nulla
		
	}
	
	
	int funzione1(int k){
		return k+a;
	}
	
	void funzione2(int a){
		
		//qui potrebbero esserci dei problemi,abbiamo usato a nella classe e a nella funzione,quale a verrà usata?
		
		cout<<"senza aver usato this-> a+a="<<a+a<<endl;
		cout<<"usando this->, this->a+a="<<this->a+a<<endl;
	}
	

};


/*
int main()
{
	
	
	
	cout<<"decidi valore a(della classe)"<<endl;
	int val1;
	cin>>val1;
	
	cout<<"decidi valore b(della classe)"<<endl;
	int val2;
	cin>>val2;
	
	cout<<"decidi valore c(della classe)"<<endl;
	int val3;
	cin>>val3;
	
	
	samuele test(val1,val2,val3);     //costruttore nel main,stiamo dicendo di "costruire la classe attorno a questi valori dati in input
	
	
	int j;
	cout<<"dai valore a k,verra\' usato nella funzione 1 "<<endl;
	cin>>j;
	
	cout<<test.funzione1(j);   //funzione1 non è dichiarata in questo scope,possiamo però richiamarla usando test.funzione1,
	                           // quindi sfruttando il costruttore
	                         

	int u;
	cout<<"dai valore a u, verra\' usato nella funzione2"<<endl;
	cin>>u;
	
	test.funzione2(u);
	
}

*/



















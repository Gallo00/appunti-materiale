#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main()
{
	
	string name="pippo";         //assegnamo a name il valore pippo
	cout<<name<<endl;
	
	string your_name;         //dichiarazione stringa senza assegnare valore
	cout<<"what's your name?"<<endl;
	cin>>your_name;
	cout<<"your name is "<<your_name<<endl;
	
	string all_names;
	all_names=name+your_name;                           //concatenazione di stringhe
	cout<<"the two concatenated names are "<<all_names<<endl;
	
	cout<<"the length of your name is "<<your_name.length()<<endl;       //calcolo lunghezza di una stringa
	
	int i;
	cout<<"quale carattere di "<<your_name<<" vuoi che venga stampato?"<<endl;  //selezionare un carattere con un determinato indice(trattare la stringa come un array)
	cin>>i;
	cout<<"il carattere numero "<<(i)<<"e\'"<<your_name[i-1]<<endl;
	
	//int g;
	//cout<<"quale lettera non vuoi piu' vedere in "<<your_name<<endl;
	//cin>>g;
	cout<<"your name without the char number "<<1<<"is "<< your_name.substr((1,your_name.length()-(your_name.length()-1)));  //stampa stringa senza primo carattere
	cout<<endl;
	
//	stringstream ss;
//	int a=5634;
	
	//ss<<"hello"<<endl;
	//oppure
//	ss.str("ciao mi chiamo fabio");
//	cout<<ss<<endl;
//	cout<<ss.str()<<endl;
	
//	ss<<5634;
//	cout<<ss;

    stringstream sa;
    sa<<"123456";
    int y;
    sa>>y;                    //conversione stringa in numero
    cout<<"y="<<y<<endl;              
    
    cout<<sa.str();                
    
    int u=y+2;
	cout<<u;
	
	
	
	
	
	
	
	
	
	
	
	
}

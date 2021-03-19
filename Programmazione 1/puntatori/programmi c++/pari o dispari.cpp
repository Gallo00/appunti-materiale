#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

int main()
{
  int p_o_d; int cont_punti_gioc; int cont_punti_pc; int num_gioc; int num_pc; int somma;
  do{
  
  cout<<"inserisci -1 per uscire,0 pari, 1 dispari" <<endl;
  cin>>p_o_d;
  cont_punti_gioc=0;
  cont_punti_pc=0;
}
while(p_o_d>1||p_o_d<-1); //condizione contraria per ripetere
  
  while(p_o_d!=-1&&cont_punti_gioc<5&&cont_punti_pc<5)
  {
  	do
  	{
  		cout<<"inserisci un numero tra 0 e 5" <<endl;
  		cout<<"  ";
  		cin>>num_gioc;
  	
	  }
	  while(0>num_gioc||num_gioc>5);  // dobbiamo ciclare solo se il numero inserito non va bene,si mette OR poichè basta che una condizione sia verificata per ciclare
	{
	
	num_pc=rand()%6; //il numero del pc è casuale,compreso tra 0 e 5
	  somma= num_gioc+num_pc;
	  cout<<"la somma e\'"<<somma <<endl;
	  cout<<"   ";
	  bool _pari;
	  if(somma%2==0) //bool _pari=(somma%2==0)?_pari=true:_pari=false;    ? comprende il ramo vero, i due punti il falso
	
	  {
	  	_pari=true;
	  }
	  else
	  {
	  	_pari=false;
	  }
	  if((_pari&&p_o_d==0)||(!_pari&&p_o_d==1))
	    {
		cont_punti_gioc++;
		cout<<"hai fatto un punto,il tuo punteggio e\'" <<cont_punti_gioc <<endl;
		cout<<"   ";
	}
	else
	{
		cont_punti_pc++; 
		cout<<"coglione,hai scelto male,il  punteggio del pc e\'" <<cont_punti_pc <<endl;
		cout<<"   ";
	}
	 if(cont_punti_gioc==5) 
	 {
	 	cout<<"hai vinto   "<<endl;
	 }
	 if(cont_punti_pc==5)
	 {
	 	cout<<"stupido down hai perso    "<<endl;
	 }
	  if(cont_punti_gioc==5||cont_punti_pc==5)
	  {
	  	cout<<"inserisci -1 per uscire,0 per pari,1 per dispari"<<endl;
	  	cin>>p_o_d;
	  	cont_punti_gioc=0;
	  	cont_punti_pc=0;
	  }
}
}
}
	  
  
	
	
	
	


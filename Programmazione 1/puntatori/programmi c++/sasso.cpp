#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main()
{
	int x;
	cout<<"decidi a che punteggio si vince(se si arriva a 3 e state 2 a 2, si arrivera' a 4) "<<endl;
	int punti_pc=0;
	int punti_user=0;
	int MAX;
	cin>>MAX;
	cout<<"punteggio max="<<MAX;
	while(punti_pc<MAX&&punti_user<MAX)
	{
	
	cout<<"metti 1 per sasso,2 per carta, 3 per forbice "<<endl;
	cin>>x;
	srand(time(NULL));
	int y=1+rand()%(3-1+1);
	cout<<"il computer ha buttato "<<y<<endl;
	switch(x)
	{
		case 1:
		if(y==1)
		{
			cout<<"pareggio"<<endl;
		}
		else
		{
			if(y==2)
			{
				cout<<"carta batte sasso"<<endl;
				punti_pc++;
			}
			else
			{ 
			    cout<<"sasso batte forbici"<<endl;
			    punti_user++;
			}
		}
		break;
		case 2:
			if(y==2)
		{
			cout<<"pareggio"<<endl;
		}
		else
		{
			if(y==1)
			{
				cout<<"carta batte sasso"<<endl;
				punti_user++;
			}
			else
			{ 
			    cout<<"forbici batte carta"<<endl;
			    punti_pc++;
			}
		}
		break;
		case 3:
		if(y==3)
		{
			cout<<"pareggio"<<endl;
		}
		else
		{
			if(y==1)
			{
				cout<<"sasso batte forbici"<<endl;
				punti_pc++;
			}
			else
			{ 
			    cout<<"forbici batte carta"<<endl;
			    punti_user++;
			}
		}
			
	}
	cout<<"punti user="<<punti_user<<endl;
	cout<<"punti pc="<<punti_pc<<endl;
	
	if(punti_pc==punti_user)
	{
		if(punti_pc==MAX-1)
		{
		
		MAX++;
		cout<<"nuovo punteggio max="<<MAX;
     	}
	}
}


}

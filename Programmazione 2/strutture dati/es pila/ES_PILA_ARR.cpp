

//crea pila usando array

#include <iostream>
using namespace std;



class Pila{
	
	private:
	    int array[100];
		int cima;
		
	public:
	    
		Pila() : cima(-1)  {}  //inizializziamo la cima a -1
		
		//funzioni booleane per verificare se la pila è vuota o piena(oppure nessuna delle due)
		
		bool pila_vuota() 
		{
			if(cima==-1) return true;
		    else return false; 
		}
		
		bool pila_piena()
		{
			if(cima==99) return true;
			else return false;
		}
		
		//operazioni push e pop
           
        int pop() 
		{
			if(!pila_vuota())
			{
			    int x=array[cima];
			    cima=cima-1; 
			    return x; 
		    }
			else
			{
				cout<<"pila vuota"<<endl;
				return -1;
			}
		}
		
        void push(int dato_nuovo)
		{
			if(!pila_piena())
			{
			    cima++;
		        array[cima]=dato_nuovo;
			}
			else
			{
				cout<<"pila piena"<<endl;
			}
		}

        void stampa()
        {
			if(pila_vuota())
			{
				cout<<"pila vuota"<<endl;
			}
			else
			{
				for(int i=cima; i>=0;i--)
				{
					cout<<array[i]<<endl;
				}
			}
		}
				
	
};



int main()
{
	Pila p;
	
	p.stampa(); 
	p.push(4); 
	p.push(8); 
	p.push(16); 
	p.stampa(); 
	int x=p.pop(); 
	p.stampa();
	
	cout<<x<<endl;
	return 0;	
	
}









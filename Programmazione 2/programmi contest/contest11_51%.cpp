#include <iostream>
#include <fstream>
using namespace std;

class condizione{
	
	public:
	    char direzione;  //n  e  s  o
		int x;
		int y;
		
		condizione(char dir_arrivo='n',int pos_x=1,int pos_y=2)
		{
			direzione=dir_arrivo;
			x=pos_x;
			y=pos_y;
		}
		
		//metodi get
		char get_dir()
		{
			return direzione;
		}
		int get_x()
		{
			return x;
		}
		int get_y()
		{
			return y;
		}
		
		//metodi set
		void set_x(int d)
		{
			x=d;
		}
		void set_y(int d)
		{
			y=d;
		}
		void set_dir(char d)
		{
			direzione=d;
		}
		//per vedere se due condizioni sono uguali
		bool operator == (condizione& alpha)
		{
			if(this->direzione == alpha.get_dir() && this->x == alpha.get_x() && this->y==alpha.get_y() )
				return true;
			else
				return false;
		}
};

bool ricerca_ogg(condizione arr[] , int n,condizione ogg)
{
	for(int i=0; i<=n ; i++)
	{
		if(arr[i]==ogg)
			return true;
	}
	return false;
}

void stampa_mat(char** a,int n,int m)
{
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<m; j++)
		{
			cout<<a[i][j]<<" ";
		}
		cout<<endl;
	}
}


int main()
{
	fstream miofile("input.txt" , fstream::in);
	fstream outfile("output.txt",fstream::out);
	
	for(int riga=0; riga<100; riga++)
	{
		int n;
		miofile>>n;
		
		int m;
		miofile>>m;
		
		string s;
		miofile>>s;
		int c=0;
		char villa[n][m];
		
		for(int i=0; i<n; i++)
		{
			for(int j=0; j<m; j++)
			{
				villa[i][j]=s[c];
				c++;
			}
		}

		condizione arr[n*m*4];
		int l=-1;   //l tiene il conto di quanti oggetti abbiamo in arr
	
		bool trovato_f=false;
	/*	if(s[0]=='F')
		{
		    trovato_f=true;
		}  */
		bool ciclo_infinito=false;
		bool ciclico=false;
		bool prima_volta=true;
		int x=0;
		int y=0;
		char direzione='o';
		condizione personaggio('o',x,y);
		condizione iniziale('o',0,0);
		int passi=0;
		while(!trovato_f  && !ciclico)
		{
			
			if(ciclo_infinito)
			{
				passi=0;
				iniziale.set_x(personaggio.get_x());
				iniziale.set_y(personaggio.get_y());
				iniziale.set_dir(personaggio.get_dir());
				prima_volta=false;
				
			//	if(riga==0)
			//		cout<<iniziale.get_x()<<" "<<iniziale.get_y()<<" "<<iniziale.get_dir()<<endl;
			}
			
			switch(villa[y][x])
			{
				case 'F':
				    int p;
				break;
				
				case 'A':
			
				    switch(personaggio.get_dir())
					{
						case ('n'):
						    y--;
							if(y==-1)
								y=n-1;
						break;
						
						case ('o'):
						    x--;
							if(x==-1)
								x=m-1;
						break;
						
						case ('s'):
						    y++;
							if(y==n)
								y=0;
						break;
						
						case ('e'):
						    x++;
							if(x==m)
								x=0;
						break;
					}
				    personaggio.set_x(x);
                    personaggio.set_y(y);	
                    passi++;
				//	if(riga==0)
                 //   cout<<personaggio.get_x()<<personaggio.get_y()<<personaggio.get_dir()<<endl;
				break;
				
				case 'J':
				    switch(personaggio.get_dir())
					{
						case 'n':
						    y=y-2;
							if(y==-1)
								y=n-1;
						    if(y==-2)
								y=n-2;
						break;
						
						case 'o':
						    x=x-2;
							if(x==-1)
								x=m-1;
							if(x==-2)
							    x=m-2;
						break;
						
						case 's':
						    y=y+2;
							if(y==n)
								y=0;
							if(y==n+1)
								y=1;
						break;
						
						case 'e':
						    x=x+2;
							if(x==m)
								x=0;
							if(x==m+1)
								x=1;
						break;
					}
				    personaggio.set_x(x);
                    personaggio.set_y(y);		
				    passi=passi+2;	
				//	if(riga==0)
                 //   cout<<personaggio.get_x()<<personaggio.get_y()<<personaggio.get_dir()<<endl;				
				break;
					
				case 'S':
				    switch(personaggio.get_dir())
					{
						case 'n':
						    x--;
							if(x==-1)
								x=m-1;
							direzione='o';
						break;
						
						case 'o':
						    y++;
							if(y==n)
								y=0;
							direzione='s';
						break;
						
						case 's':
						    x++;
							if(x==m)
								x=0;
							direzione='e';
						break;
						
						case 'e':
						    y--;
							if(y==-1)
								y=n-1;
							direzione='n';
						break;
					}
					
				    personaggio.set_x(x);
                    personaggio.set_y(y);
                    personaggio.set_dir(direzione);				
				    passi++;		
				break;
				
				case 'D':
				    switch(personaggio.get_dir())
					{
						case 'n':
						    x++;
							if(x==m)
								x=0;
							direzione='e';
						break;
						
						case 'o':
						    y--;
							if(y==-1)
								y=n-1;
							direzione='n';
						break;
						
						case 's':
						    x--;
							if(x==-1)
								x=m-1;
							direzione='o';
						break;
						
						case 'e':
						    y++;
							if(y==n)
								y=0;
							direzione='s';
						break;
					}
					
				    personaggio.set_x(x);
                    personaggio.set_y(y);
                    personaggio.set_dir(direzione);				
				    passi++;	
				break;
			}

			if(personaggio==iniziale)
			{
                ciclico=true;
			/*	if(riga==0)
				{
					cout<<"sd"<<x<<" "<<y<<" "<<direzione<<iniziale.get_x()<<" "<<iniziale.get_y()<<" "<<iniziale.get_dir()<<endl;
					cout<<personaggio.get_x()<<personaggio.get_y()<<personaggio.get_dir()<<passi;	
				}  */
			}
			else
			{
				if(ricerca_ogg(arr,l,personaggio) && prima_volta)
			    {
				    ciclo_infinito=true;
			    }
			    else
			    {
				    l++;
				    arr[l]=personaggio;
			    }
			}
			
			if(passi>=n*m*4)
			{
				trovato_f=true;
			}
			
		}
		if(!ciclico)
		{
			outfile<<-1<<endl;
		}
		else
		{
			if(passi==0)
				passi=-1;
			
			outfile<<passi<<endl;
		}
	}
	outfile.close();
	miofile.close();
	return 0;
}
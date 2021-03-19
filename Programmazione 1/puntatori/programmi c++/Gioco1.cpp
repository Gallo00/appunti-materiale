
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

int main ()

{
	//int controllo_bombe;
/*	int bombe_adiacenti;
	int life_points=8;
	int points=0;
	int actual_r=2;
	int actual_c=2;
	int bomb;
	int life;
	int x;
	int under_map[5][5];*/
	int u;
	cout<<"vuoi giocare? inserisci 1 per si,altro valore o lettera per no"<<endl;
	cin>>u;
	
	while(u==1)
	{
    int bombe_adiacenti;
	int life_points=8;
	int points=0;
	int actual_r=2;
	int actual_c=2;
	int bomb;
	int life;
	int x;
	int under_map[5][5];
	cout<<"inserisci la difficolta\'" <<endl <<"1 per facile"<<endl<<"2 per media"<<endl<<"3 per difficile" <<endl;
	do
	{
	cin>>x;
}

while(x<1 || x>3);
	switch(x)
	{
	case 1:
	bomb=5;
	life=7;
	break;
	case 2:
	bomb=6;
	life=6;
	break;
	case 3:
	bomb=7;
	life=5;
	break;
}
	int over_map[5][5];
	int i=0;
	int j;
	srand(time(NULL));
	while(i<5)
	{
		j=0;
		while(j<5)
		{
        over_map[i][j]=0;
        //cout<<over_map[i][j] <<"  ";
        j++;
    }
    //cout<<endl;
    i++;	
	}
	i=0;
	cout<<endl;
	int r=0;
	int c=0;
	srand(time(NULL));
		while(r<5)
	{
		c=0;
		while(c<5)
		{
        under_map[r][c]=0;
        //cout<<under_map[r][c] <<"  ";
        c++;
    }
    //cout<<endl;
    r++;	
	}
	//cout<<endl;
	while(i<bomb)
	{
		int r;
		int c;
	r=rand()%5;
	c=rand()%5;
	if(under_map[r][c]==1)
	{	
}
else
{
	under_map[r][c]=1;
	i++;
}
	} 
/*	r=0;
	while(r<5)
	{
		c=0;
		while(c<5)
		{
			cout<<under_map[r][c]<<"  ";
			c++;
		}
		cout<<endl;
		r++; 
	} */
	i=0;
		while(i<life)
	{
		int r;
		int c;
	r=rand()%5;
	c=rand()%5;
	if(under_map[r][c]==0)
	{
	under_map[r][c]=2;
	i++;
}
}
/*cout<<endl;
r=0;
	while(r<5)
	{
		c=0;
		while(c<5)
		{
			cout<<under_map[r][c]<<"  ";
			c++;
		}
		cout<<endl;
		r++; 
	} 
cout <<endl; */
over_map[2][2]=4;     //omino
i=0;
	while(i<5)
	{
		j=0;
		while(j<5)
		{
        if(i==2&&j==2)
        {
        	cout<<":)" <<"  ";
		}
		else
		{
		
		cout<<"IN" <<"  ";
	}
        j++;
    }
    cout<<endl;
    i++;
}
char p;
 while(life_points>0&&points<14)
 {
 //	controllo_bombe=0;
 	bombe_adiacenti=0;
 		if(under_map[actual_r-1][actual_c]==1 && actual_r!=0)
 		{
 			bombe_adiacenti+=1;
		 }
		if(under_map[actual_r][actual_c-1]==1 && actual_c!=0)
 		{
 			bombe_adiacenti+=1;
		 }
		if(under_map[actual_r+1][actual_c]==1 && actual_r!=4)
 		{
 			bombe_adiacenti+=1;
		 } 
		if(under_map[actual_r][actual_c+1]==1 && actual_c!=4)
 		{
 			bombe_adiacenti+=1;
		 }
	 cout<<endl <<"warning! there are " <<bombe_adiacenti <<"bombs next you"; 
 	cout<<endl <<"muoviti con wasd"<<endl;
 	cin>>p;
 	switch(p)
 	{
 	case 'w':
 	if(actual_r==0)	
 	{
	 }
 	else
	 {
	over_map[actual_r][actual_c]=1;	
 	actual_r--;
 }
 	break;
 	case 'a':
 	if(actual_c==0)
 	{
 	}
    else{
	over_map[actual_r][actual_c]=1;
 	actual_c--;
 }
 	break;
 	case 's':
 	if(actual_r==4)
 	{
 	}
 	else {
 		over_map[actual_r][actual_c]=1;
	 actual_r++;
}
    break;
 	case 'd':
 	if(actual_c==4)
 	{
 	}
 	else{
 		over_map[actual_r][actual_c]=1;
	 actual_c++;
}
 	break;
 }
 i=0;
 over_map[actual_r][actual_c]=4;
 	while(i<5)
	{
		j=0;
		while(j<5)
		{
		if(i==actual_r&&j==actual_c)
		{
			cout<<":)  ";
		}
		else
		{
		if(over_map[i][j]==1)
		{
        cout<<"E" <<"   ";
    } 
    else
    {
    	cout<<"IN"<<"  ";
	}
    }  
        j++;
    }
    cout<<endl;
    i++;	
	} 
	
  switch(under_map[actual_r][actual_c]) 
  {
  case 0:
  points+=1;
  cout<<"you've done a point" <<endl;
  under_map[actual_r][actual_c]=-1;
  break;
  case 1:
  life_points-=2;
  cout<<"ALLAH AKBAR" <<endl;
   under_map[actual_r][actual_c]=-1;
  break;
  case 2:
  	cout<<"you've done a point" <<endl;
  	cout<<"you received an extra point life" <<endl;
  life_points+=1;
  points+=1;
   under_map[actual_r][actual_c]=-1;
  break; 
}
cout<<endl<<"your life points are" <<life_points;
cout<<endl<< "your points are"<<points;
cout<<endl <<endl <<endl <<endl <<endl<<endl <<endl <<endl <<endl <<endl<<endl <<endl <<endl <<endl <<endl<<endl <<endl;
 }
 cout<<endl <<"vuoi giocare? inserisci 1 per si,altro valore o lettera per no"<<endl;
	cin>>u;
}
 return 0;
 
}

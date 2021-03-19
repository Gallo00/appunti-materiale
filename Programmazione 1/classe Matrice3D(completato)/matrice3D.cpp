#include <iostream>
#include "matrice3D.h"




Matrice3D::Matrice3D(int x,int y,int z){    //costruzione matrice
	cout<<"ho fatto la costruzione"<<endl;
	int v=0;
	a=x;
	b=y;
	c=z;
	cubo=new int**[a];           //problema con operator+
	for(int i=0;i<a;i++){
		cubo[i]=new int*[b];
		for(int j=0;j<b;j++){
			cubo[i][j]=new int[c];
			for(int h=0;h<c;h++){
				
				cubo[i][j][h]=v;
				v++;
			}
		}
	}
  
}

 int  Matrice3D::getdimX() const {
	return a;
}

 int Matrice3D::getdimY() const  {
	return b;
}

 int Matrice3D::getdimZ() const {
	return c;
}

void Matrice3D::stampa()
{
	for(int i=0;i<a;i++){
		for(int j=0;j<b;j++){
			for(int h=0;h<c;h++){
				cout<<cubo[i][j][h]<<" ";
			}
			cout<<endl;
		}
		cout<<endl<<endl;
	}
}





Matrice3D* Matrice3D::sum_by_ptr(Matrice3D* m1,Matrice3D* m2){  
	
	Matrice3D* mat_sum_ptr=new Matrice3D((*m1).getdimX(),(*m1).getdimY(),(*m1).getdimZ());
	for(int i=0;i<(*m1).getdimX();i++){
		for(int j=0;j<(*m1).getdimY();j++){
			for(int h=0;h<(*m1).getdimZ();h++)
			{
			    (*mat_sum_ptr).cubo[i][j][h]=(*m1).cubo[i][j][h] + (*m2).cubo[i][j][h];
			}
		}
	}
	
	return mat_sum_ptr;
}


Matrice3D Matrice3D::sum_by_ref(Matrice3D &m1,Matrice3D &m2){  
	
	Matrice3D mat_sum_ref(m1.getdimX(),m1.getdimY(),m1.getdimZ());
	
	for(int i=0;i<m1.getdimX();i++){
		for(int j=0;j<m1.getdimY();j++){
			for(int h=0;h<m1.getdimZ();h++)
			{
			    (mat_sum_ref).cubo[i][j][h]=m1.cubo[i][j][h] + m2.cubo[i][j][h];
			}
		}
	}
	return mat_sum_ref;
}


 int& Matrice3D::get_element(int Cx,int Cy,int Cz) const{
	
	int &element=cubo[Cx][Cy][Cz];
	return element;
	
}

 int Matrice3D::get_value(int Cx,int Cy,int Cz) const {
	return cubo[Cx][Cy][Cz];
}


Matrice3D::Matrice3D(const Matrice3D &m)
{
	
	cubo=new int**[m.getdimX()];
	for(int i=0;i<m.getdimX();i++)
	{
		cubo[i]=new int*[m.getdimY()];
		for(int j=0;j<m.getdimY();j++)
		{
			cubo[i][j]=new int[m.getdimZ()];
			for(int h=0;h<m.getdimZ();h++)
			{
				
				cubo[i][j][h]=m.cubo[i][j][h];
				
			}
		}
	}
}

//farà la stessa cosa di somma,ma sarà possibile ora scrivere m1+m2 invece di  sum(m1,m2)


Matrice3D operator +(Matrice3D &sx ,Matrice3D &dx)
{
	Matrice3D  sum(sx.getdimX(), sx.getdimY(), sx.getdimZ());
	cout<<"inizio operator+"<<endl;
	for(int i=0;i<sx.getdimX();i++)
	{
	//	cout<<"inizio primo for"<<endl;
		for(int j=0;j<sx.getdimY();j++)
		{
		//	cout<<"secondo for"<<endl;
			for(int h=0;h<sx.getdimZ();h++)
			{
			   // cout<<"terzo for"<<endl;
			    
			    sum.cubo[i][j][h]=sx.cubo[i][j][h] + dx.cubo[i][j][h];
		//		cout<<"somma"<<endl;
			}
		}
	}   
	
	
	return sum;  
}



Matrice3D & Matrice3D::operator=(Matrice3D &dx)     //perchè un alias?
{
    for(int i=0;i<dx.getdimX();i++)
    {
	    for(int j=0;j<dx.getdimY();j++)
	    {
	    	for(int h=0;h<dx.getdimZ();h++) 
			{
	    		(this->cubo[i][j][h])=dx.cubo[i][j][h];		 
			}
		}
	}
	return *this;
}

bool Matrice3D::operator == (Matrice3D &dx)
{
	if( this->a == dx.getdimX() && this->b==dx.getdimY() && this->c==dx.getdimZ() )
	{
		for(int i=0;i<this->a;i++)
		{
			for(int j=0;j<this->b;j++)
			{
				for(int h=0;h<this->c;h++)
				{
					if(this->cubo[i][j][h]!=dx.cubo[i][j][h])
					{
						return false;
					}
					
				}
			}
		}
	}
	else
	{
		return false;
	}
	
	return true;
}

int & Matrice3D::operator() (int i,int j,int h)
{
	return this->cubo[i][j][h];
}


ostream & operator <<(ostream &sx,const Matrice3D &dx)
{
	//devo "mettere dentro" sx e poi tornarlo
	
	for(int i=0;i<dx.getdimX();i++)
	{
		for(int j=0;j<dx.getdimY();j++)
		{
			for(int h=0;h<dx.getdimZ();h++)
			{
				sx<< dx.cubo[i][j][h] <<" ";
			}
			sx<<endl;
		}
		sx<<endl;
	}
	return sx;
}

istream & operator >>(istream &sx, Matrice3D &dx)
{
	cout<<"stai usando cin con una matrice"<<endl;
	for(int i=0;i<dx.getdimX();i++)
	{
		for(int j=0;j<dx.getdimY();j++)
		{
			for(int h=0;h<dx.getdimZ();h++)
			{
				cout<<"inserisci elemento i, j , h"<<endl;
				sx >> dx.cubo[i][j][h];
			}
		}
	}
	return sx;
}






















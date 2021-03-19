/*
Sovraccaricamento degli Operatori.
Esercizio 3. Operatore <<  
*/
#include<iostream>
using namespace std; 

class Punto	{
private: 
	double x;
	double y; 
public: 
	Punto(double xx,double yy): x(xx), y(yy) {} 
	double getX() {return x;}
	double getY() {return y;}
	void setX(double xx) {x=xx;} 
	void setY(double yy) {y=yy;}
	Punto operator+(const Punto& b); 
	Punto& operator+=(const Punto& a);
};

Punto Punto:: operator+(const Punto& b)	{
	Punto temp(0.0,0.0);
	
	temp.x=this->x+b.x; 
	temp.y=this->y+b.y; 
	return temp;  
}

Punto& Punto:: operator+=(const Punto& b)	{
	x+=b.x; 
	y+=b.y; 
	return *this;  
}

ostream& operator<< (ostream& out,Punto& a)
{
	out << "Coordinata x:" << a.getX() << "\t Coordinata y:" << a.getY() << endl;
	return out; 
}

int main()	{
	Punto p1(3,4), p2(5,7), p(0,0);
	
	p=p1+p2; 
	cout << "p.x:" << p.getX() << "\t p.y:" << p.getY() << endl; 
	p+=p1;
	cout << "p.x:" << p.getX() << "\t p.y:" << p.getY() << endl;
	cout << p; 
	return 0; 	
}
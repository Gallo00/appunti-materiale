/*
Sovraccaricamento degli Operatori.
Esercizio 2. Operatore + usando funzioni friend. 
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
	friend Punto operator+(Punto& a, Punto& b);
	//Punto operator+(const Punto& b); 
};

Punto operator+(Punto& a, Punto& b)	{
	Punto temp(0.0,0.0);
	
	temp.setX(a.getX()+b.getX()); 
	temp.setY(a.getY()+b.getY()); 
	return temp;  
}

int main()	{
	Punto p1(3,4), p2(5,7), p(0,0);
	
	p=p1+p2; 
	cout << "p.x:" << p.getX() << "\t p.y:" << p.getY() << endl; 
	return 0; 	
}
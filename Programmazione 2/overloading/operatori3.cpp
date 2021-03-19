/*
Sovraccaricamento degli Operatori.
Esercizio 4. Addizione di punti con scalari. 
*/
#include<iostream>
using namespace std; 

class Punto	{
private: 
	double x;
	double y; 
public: 
	Punto(double xx,double yy): x(xx), y(yy) {} 
	Punto(double d): x(d),y(d) {}
	/* L'aggiunta di questo secondo costruttore 
		permette di fare l'addizione di un punto con uno 
		scalare senza modificare la procedura di addizione definita sotto
	*/ 
	double getX() {return x;}
	double getY() {return y;}
	void setX(double xx) {x=xx;} 
	void setY(double yy) {y=yy;}
	Punto operator+(const Punto& b); 
			//Addizione di due punti
	Punto& operator+=(const Punto& a);
	Punto& operator++(); //Versione prefissa ++p
	Punto operator++(int); //Versione postfissa p++
	/* La presenza di int tra i parametri serve per differenziare 
		le due funzioni (darebbe errore senza una differenza nei
		parametri in input) 
	*/
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

Punto& Punto:: operator++()	{
// Questo implementa ++p
	x++; 
	y++; 
	return *this;
}

Punto Punto:: operator++(int)	{
// Questo implementa p++
	Punto pp(this->x,this->y); 
	++(*this); 
	return pp;
}

int main()	{
	Punto p1(3,4), p2(5,7), p(0.0);
	
	p=p1+p2; 
	cout << "p.x:" << p.getX() << "\t p.y:" << p.getY() << endl; 
	p+=p1;
	cout << "p.x:" << p.getX() << "\t p.y:" << p.getY() << endl;
	++p; 
	cout << "p.x:" << p.getX() << "\t p.y:" << p.getY() << endl;
	p++;
	cout << "p.x:" << p.getX() << "\t p.y:" << p.getY() << endl;
	double s=3; 
	p=p+s;
	cout << "p.x:" << p.getX() << "\t p.y:" << p.getY() << endl;
	return 0; 	
}
#include <iostream>
using namespace std;



class Matrice3D{
  int a,b,c;
  int*** cubo;

  
  

	public:
	    //costruttori
		Matrice3D(int x, int y,int z);
		Matrice3D(const Matrice3D &);  //costruttore di copia
		
		//metodi get
		int getdimX() const ;
		int getdimY() const ;
		int getdimZ() const ;
		int& get_element(int Cx,int Cy,int Cz) const;
		int get_value(int Cx,int Cy,int Cz) const;
		
		//metodo stampa
		void stampa();
		
		//overloading operatori
	    friend Matrice3D  operator+(Matrice3D & , Matrice3D &);  
        Matrice3D & operator=(Matrice3D &);    //
		bool operator == (Matrice3D &);   //perchè
		int & operator () (int i, int j, int h); //metodo che permettere di prendere l'elemento [i][j][h] e anche di modificarlo
		
//	    Matrice3D operator * (Matrice3D &);   prodotto tra matrici a 3 dimensioni come si fa?
	    
		
		//metodi somma
		//somma coi puntatori
	    static Matrice3D* sum_by_ptr(Matrice3D* m1, Matrice3D* m2); //deve essere static poichè la somma tra matrici esiste a prescindere dall'esistenza o meno di tali matrici
		//somma coi reference
		static Matrice3D sum_by_ref(Matrice3D &m1,Matrice3D &m2);
		
		
		
		//operator <<  e  >> , sono più particolari necessitano di essere scritti con ostream e istream
		
		friend ostream & operator <<(ostream & sx,const Matrice3D &dx); //usiamo const poichè la lettura non deve appunto modificare l'oggetto in input
		friend istream & operator >>(istream & sx, Matrice3D &dx);
		
		//perchè friend?
		
		
		
		
		
		
		
		
		
		
		
		
		
		
};



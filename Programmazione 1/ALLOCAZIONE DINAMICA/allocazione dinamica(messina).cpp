#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std; 

//bool func(string v[], int n){
// bool func(string *v, int n){

//matrice di puntatori a stringhe

bool func(string* **v, int n, int m){
  
    short aux[n]; 
    int c; 
  
    for(int j=0; j<m; j++){// colonna     
      for(int i=0; i<n; i++){ //riga 
	c = 0; 
	//v[i][j] ? nullptr? 
	if(v[i][j]!=nullptr){
	  for(unsigned int k=0; k<(*v[i][j]).length(); k++){
	    switch((*v[i][j]).at(k)){ 
	      case 'a': 
	      case 'e': 
	      case 'i': 
	      case 'o': 
	      case 'u':
		c++; 
		break; 
	    } // end switch
	  } // end for(k)
	  aux[i] = c; 
	} // end if
	else
	  aux[i] = -1;
      } // end for(i) 

      for(int a=0; a<n-1; a++)
	for(int b=a+1; b<n; b++)
	  if(aux[a] == aux[b] && aux[a]!=-1){
	    cout << "mat(), found at " <<  a << ", " << j << endl;  
	    return true;
	  }
    }// for(j) 

    return false;       
}


int main(){
  
  srand(time(0)); 

  int n = 4; 
  int m = 3;

// string **mat[n]; //A-  allocazione del vettore di puntatori al tipo string*  sullo stack

  string* **mat;  // B- allocazione del vettore di puntatori al tipo string*  sullo heap 
   mat = new string**[n]; 

  for(int i=0; i<n; i++){
    mat[i] = new string*[m]; 
    for(int j=0; j<m; j++){
      switch(rand()%5){
	case 0:
	  mat[i][j] = nullptr; 
	  break; 
	case 1: 
	case 2: 
	case 3: 
	case 4: 
	  mat[i][j] = new string();
	  short l = rand()%10 + 5; 
	  for(int k=0; k<l; k++)
	    *(mat[i][j]) +=  rand()%('z' - 'a' + 1)  + 'a';
	  break; 
      } // end switch 
    } // end for(j) 
  } // end for(i) 

  for(int i=0; i<n; i++){
    cout << endl; 
    for(int j=0; j<m; j++)
      if(mat[i][j])
	cout << " " << *mat[i][j]; 
      else
	cout << " NULL";
  }

	cout << endl; 

  cout << "func(mat)=" << func(mat, n, m) << endl; 

}

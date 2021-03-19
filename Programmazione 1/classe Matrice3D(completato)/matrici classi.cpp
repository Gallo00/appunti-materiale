#include <iostream>
#include "matrice3D.cpp"
using namespace std;


int main(){


int dim1k,dim2k,dim3k;
cin>>dim1k>>dim2k>>dim3k;
Matrice3D k(dim1k,dim2k,dim3k);

cout<<"la dimX di k e'"<<k.getdimX()<<endl;
cout<<"la dimY di k e'"<<k.getdimY()<<endl;
cout<<"la dimZ di k e'"<<k.getdimZ()<<endl;

cout<<"metodo stampa su k"<<endl;
k.stampa();    //stampa tutti gli elementi della matrice contenuta nell'oggetto k


//ora dobbiamo creare un metodo che prende in input due puntatori a tipo Matrice3D, fa la somma e restituisce un puntatore a Matrice3D

//ci servono dunque due matrici,creiamo la seconda(facciamo caso sia "uguale" alla prima)

int dim1h,dim2h,dim3h;
cin>>dim1h>>dim2h>>dim3h;
Matrice3D h(dim1h,dim2h,dim3h);

cout<<"la dimX di h e'"<<h.getdimX()<<endl;
cout<<"la dimY di h e'"<<h.getdimY()<<endl;
cout<<"la dimZ di h e'"<<h.getdimZ()<<endl;

cout<<"metodo stampa su h"<<endl;
h.stampa();  //stampa gli elementi della matrice contenuta nell'oggetto h



cout<<"dimensioni uguali,e' possibile eseguire la somma"<<endl;
cout<<"metodo sum_by_ptr"<<endl;
Matrice3D* sum_h_k_ptr=Matrice3D::sum_by_ptr(&k,&h);

cout<<"metodo stampa su *sum_h_k_ptr"<<endl;
(*sum_h_k_ptr).stampa();


//creiamo due alias di k e h

Matrice3D &kR=k;
Matrice3D &hR=h;


//invochiamo ora il metodo sum_by_ref



cout<<"metodo sum_by_ref"<<endl;
Matrice3D sum_h_k_ref=Matrice3D::sum_by_ref(kR,hR);

cout<<"metodo stampa su sum_h_k_ref"<<endl;
sum_h_k_ref.stampa();



//adesso usiamo il metodo get_element per prendere un elemento da "cubo" in un Matrice3D
// a nostro piacere con coordinate a nostro piacere
cout<<"inserisci coordinata Cx"<<endl;
int Cx;
cin>>Cx;

cout<<"inserisci coordinata Cy"<<endl;
int Cy;
cin>>Cy;

cout<<"inserisci coordinata Cz"<<endl;
int Cz;
cin>>Cz;

cout<<"metodo get_element su k usando Cx,Cy,Cz"<<endl;
cout<<k.get_element(Cx,Cy,Cz)<<endl;

cout<<"metodo get_value su k usando Cx,Cy,Cz"<<endl;
cout<<k.get_value(Cx,Cy,Cz)<<endl<<endl<<endl;



cout<<"adesso facciamo la somma tra due matrici dopo aver fatto overloading su +, facciamo h+k "<<endl;
Matrice3D sum_by_operator= operator+(h,k);


sum_by_operator.stampa();



cout<<"k prima di operator=(sum ref)"<<endl;
k.stampa();

k.operator=(sum_h_k_ref);

cout<<"k dopo aver usato operator="<<endl;
k.stampa();


cout<<"usiamo ora operator=="<<endl;
cout<<(k==h)<<endl;
cout<<(k==sum_h_k_ref)<<endl;


cout<<"metodo ()"<<endl;
cout<<k.operator()(1,0,1)<<endl;

k.operator()(1,0,1)= 3;    //poichè restituisce reference è possibile modificarlo
cout<<k.operator()(1,0,1)<<endl;

cout<<k<<endl;
cin>>k;
cout<<k;



}

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "math.h"
using namespace std;


template <class T>
class nodo{
public :

    T key;

    nodo<T>* padre;
    nodo<T>* sx;
    nodo<T>*dx;
    nodo(){
        sx=NULL;
        dx=NULL;
    }
};

template<class T>
class albero{
    
public:
    
    nodo<T>* radice;
    
    albero(){
        radice=NULL;
    }
    
    void inserimento (T x){
        
        nodo<T>* temp=radice;
        nodo<T>* temp2=NULL;
        
        while(temp){
            
            temp2=temp;
            
            if(x>temp->key){
                temp=temp->dx;
            }
            else 
                temp=temp->sx;
        }
        
        temp=new nodo<T>;
        temp->key=x;
        temp->padre=temp2;
        if(temp2==NULL)
            radice=temp;
        else{
            if(x>temp2->key)
                temp2->dx=temp;
            else 
                temp2->sx=temp;
        }
    }
    
    nodo<T>* minimo(nodo<T>* x){
        
        if(x){
            
            if(x->sx!=NULL){
                return minimo(x->sx);
    
            }
            else 
                return x;
        }
    }
    
    void trapianta(nodo<T>*x,nodo<T>*y){
        
        if(x->padre==NULL)
            radice=y;
        else if(x==x->padre->dx)
            x->padre->dx=y;
        else 
            x->padre->sx=y;
            
            
        if(y!=NULL)
            y->padre=x->padre;
        
    }
    
    
    void elimina(nodo<T>*x){
        
        if(x->dx==NULL){
            trapianta(x,x->sx);
        }
        else if(x->sx==NULL){
            trapianta(x,x->dx);
        }
        else {
            
            nodo<T>*y=minimo(x->dx);
            
            if(x->dx!=y){
                trapianta(y,y->dx);
                y->dx=x->dx;
                y->dx->padre=y;
                
            }
            trapianta(x,y);
            y->sx=x->sx;
            y->sx->padre=y;
        }
    }
    
    
    nodo<T>* cerca(T x){
        nodo<T>* temp=radice;
        
        
        while (temp){
            
            if(temp->key==x){
                return temp;
            }
            
            if(x>temp->key){
                temp=temp->dx;
            }
            else 
                temp=temp->sx;
            
        }
    }
    
    
    int count(nodo<T>* x){
        
        if(x==NULL)
            return 0;
        
        if(x->sx!=NULL&&x->dx!=NULL)
            return count(x->sx)+count(x->dx)+1;
        else{
            return count(x->sx)+count(x->dx);
        }
        
    }
    
    void operazione (string tipo, string dato){
        
        if(typeid(T).name()[0]==tipo[0]){
            
            if(dato[0]=='i'){
                cout<<"hello"<<endl;
                dato.erase(0,4);
                cout<<dato<<endl;
                stringstream ss;
                ss<<dato;
                T x;
                ss>>x;
                inserimento(x);
            }
            else{
                dato.erase(0,5);
                stringstream ss;
                ss<<dato;
                T x;
                ss>>x;
                elimina(cerca(x));
            }
        }
    }
    
    
    
    
    
};

int main(){
    
    ifstream input;
    ofstream output;
    
    input.open("input.txt");
    output.open("output.txt");
    
    
    for (int task=1;task<=100;task++){
        
        string tipo;
        int op;
        
        input>>tipo>>op;
        
        albero<int> a_int;
        albero<double> a_double;
        
        for(int i=0;i<op;i++){
            
            string dato;
            input>>dato;
            
            a_int.operazione(tipo,dato);
            a_double.operazione(tipo,dato);
            
        }
        
        if(tipo[0]=='i'){
            output<<a_int.count(a_int.radice)<<" "<<endl;
        }
        else 
            output<<a_double.count(a_double.radice)<<endl;
        
    }
}

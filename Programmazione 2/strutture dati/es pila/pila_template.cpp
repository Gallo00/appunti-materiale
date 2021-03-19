#include<iostream>

using namespace std;




template<class T>
class Pila
{   
private:
    int lunghezza;
    T* tabella;
    int cima;

public:
    Pila(int lungh = 10);
    ~Pila() {delete [] tabella;}
    void Push(T);
    T Pop();
    int num_elementi();
    void visualizza();
    int leggi_lunghezza() {return lunghezza;}


};

template<class T>
Pila<T>::Pila(int lungh)
{
    lunghezza = lungh;
    tabella = new T[lunghezza];
    cima = -1;
}

template<class T>
void Pila<T>::Push(T x)
{
    if (cima<lunghezza-1)
    {
		cima++;
        tabella[cima] = x;
    }
    else
    {
        cout << "Pila Piena!\n";
    }
}

template<class T>
T Pila<T>::Pop()
{
    T elem = 0;
    if (cima>=0)
    {
        elem = tabella[cima--];
    }
    else
    {
        cout << "Pila vuota!\n";
    }
    return elem;
}

template<class T>
void Pila<T>::visualizza()
{
    for (int i = cima; i >= 0; i--)
    {
        cout << "[" << tabella[i] << "]" << endl; 
    }
} 

template<class T>
int Pila<T>::num_elementi()
{
    return (cima+1);
}

int main()
{
    Pila<int> stack(6);

    stack.Push(4);
    stack.Push(7);
    stack.Push(87);
    cout << "Numero elementi: " << stack.num_elementi() << endl;
    stack.visualizza();
    stack.Pop();
    stack.visualizza();
	
	Pila<char> stack_c(11);
	stack_c.Push('b');
	stack_c.Push('t');
	stack_c.Push(',');
	stack_c.Push('?');
	stack_c.visualizza();
	

    return 0;
}










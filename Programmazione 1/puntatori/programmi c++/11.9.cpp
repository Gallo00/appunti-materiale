#include <iostream>
using namespace std;

int main()
{
	float y;
	float x;
	cout<<"inserisci 2 numeri decimali maggiori di 0 e diversi tra loro"<<endl;
	cin>>x;
	cout<<"il primo e'"<<x<<endl;
	cin>>y;
	cout<<"il secondo e'"<<y<<endl;
	int x_arrotondamento_eccesso=x;
	cout<<"l'arrotondamento del primo per eccesso e'"<<x_arrotondamento_eccesso<<endl;
	int y_arrotondamento_eccesso=y;
	cout<<"l'arrotondamento del secondo per eccesso e'"<<y_arrotondamento_eccesso<<endl;
	
	int x_arrotondamento_difetto=x+0.5;
	cout<<"l'arrotondamento del primo per eccesso e'"<<x_arrotondamento_difetto<<endl;
	int y_arrotondamento_difetto=y+0.5;
	cout<<"l'arrotondamento del secondo per eccesso e'"<<y_arrotondamento_difetto<<endl;
}

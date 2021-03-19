#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
int main()
{
	while(1<2)
	{
//	string y;
//	cin>>y;
    cout<<"digita qualunque cosa per eseguire"<<endl;
    string a;
    cin>>a;
	srand(time(NULL));
	int x=(rand()%6)+1;        //generazione casuali da 1 a 6(compresi)
	cout<<x<<" ";
	int u=(rand()%6)+1;
	cout<<u<<endl;
}
}

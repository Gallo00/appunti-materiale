#include <iostream>
#include <limits>

using namespace std;

int main()
{
	
	int x;
	cout<<"inserisci"<<endl;
	cin>>x;
	//cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout<<x<<endl;
	
	
//	if(cin.fail())
//	{
//		cout<<"errore"<<endl;
//	}
	if(cin.fail()==0)
	{	
	cout<<"c'e' stato nessun erroe(cin.fail()=0)"<<endl;
}
else
{
	cout<<"errore"<<endl;



cout<<"adesso resetto lo stato del flag..."<<endl;
cin.clear();

cout<<cin.fail();

}





}

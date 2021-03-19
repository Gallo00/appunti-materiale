#include <iostream>
using namespace std;

int main()
{
	int anno=0;
	int N;
	float capitale;
	cout<<"inserisci capitale"<<endl;
	cin>>capitale;
	int t;
	cout<<"inserisci numero di anni massimi"<<endl;
	cin>>N;
	cout<<"inserisci target"<<endl;
	cin>>t;
	while(anno<N&&capitale<t)
	{
		
		capitale=capitale+(capitale*0.1);
		anno++;
		
	}
	cout<<anno<<endl<<capitale;
	
	
}

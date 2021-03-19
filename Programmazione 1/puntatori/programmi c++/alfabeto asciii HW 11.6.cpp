#include <iostream>

using namespace std;

int main()
{
	
	int i=98;
	while(i<122)
	{
	switch(i)
	{
	case 101:
	case 105:
    case 111:
    case 117:
    break;
    default:
    char result=static_cast<char>(i); 
	cout<<result;	
	break;
}
i++;
}
	
	
}

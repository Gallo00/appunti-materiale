#include <iostream>
#include <fstream>
using namespace std;		
			




unsigned long long fibonacci(int i)
{
  if (i == 1 || i==0) return 1;
  else return fibonacci(i-1) + fibonacci(i-2);
}


int main()
{
	ofstream outfile("output.txt");
	
	unsigned long long i=0;
    while(i<10)
	{
	    outfile<<fibonacci(i)<<endl;
		i++;
	}
}
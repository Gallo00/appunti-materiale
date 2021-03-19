#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;



int main()
{
	fstream miofile("input.txt",fstream::in);
	fstream outfile("output.txt",fstream::out);
	
	for(int riga=0; riga<100; riga++)
	{
		string num;
		miofile>>num;
		stringstream primo;
		primo<<num;
		int min;
		primo>>min;
		while(num!="STOP")
		{
			stringstream ss;
			ss<<num;
			int number;
			ss>>number;
			if(number<min)
				min=number;
			miofile>>num;
		}
		outfile<<min<<endl;
	}
	miofile.close();
	outfile.close();
	return 0;
}
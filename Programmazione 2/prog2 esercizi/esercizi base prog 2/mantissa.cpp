#include <iostream>
#include <fstream>

using namespace std;


int main()
{
	fstream miofile("input.txt", fstream::in);
	fstream outfile("output.txt",fstream::out);
	
	for(int riga=0; riga<100; riga++)
	{
		int lung;
		miofile>>lung;
		
		double arr[lung];
		for(int i=0; i<lung; i++)
		{
			double a;
			miofile>>a;
			arr[i]=a;
		}
		
		for(int i=0; i<lung; i++)
		{
			int parte_int=arr[i];
			double mantissa=arr[i]- (double)(parte_int);
			outfile<<mantissa<<" ";
		}
		outfile<<endl;
	}
	miofile.close();
	outfile.close();
	return 0;
}
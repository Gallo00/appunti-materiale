//TORRE DI HANOI
#include <iostream>
#include <fstream>

using namespace std;

bool stampato=false;
int counter=0;
void Hanoi(int palo1,int palo2,int palo3,int mossa,int dischi,ofstream& f)
{
	if(dischi==1)
	{
		counter++;
        if(counter==mossa)
	    {
		    
		    if(!stampato)
		    {
			    f<<palo1<<" "<<palo3<<endl;
			    stampato=true;
		    }
	    }
	}
    else
	{
		Hanoi(palo1,palo3,palo2,mossa,dischi-1, f);
		counter++;
		if(counter==mossa)
	    {
		    if(!stampato)
		    {
			    f<<palo1<<" "<<palo3<<endl;
			    stampato=true;
		    }
	    }
		Hanoi(palo2,palo1,palo3,mossa,dischi-1, f);
	}
}

int main()
{
	fstream miofile("input.txt",fstream::in);
	ofstream outfile("output.txt",fstream::out);
	
	for(int riga=0; riga<100; riga++)
	{
		int dischi;
		miofile>>dischi;
		int mossa;
		miofile>>mossa;
		Hanoi(1,2,3,mossa,dischi,outfile);
        stampato=false;
		counter=0;
	}
	miofile.close();
	outfile.close();
	return 0;
}
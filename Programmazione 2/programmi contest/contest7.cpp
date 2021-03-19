#include <iostream>
#include <fstream>
using namespace std;


void Stampa (int a[], int n) 
{
	cout<<"[";
	for (int i=0; i<n;i++) 	
		cout << a[i] << " ";
    cout<<"]";
	cout << endl;  
}



int combinazione(int arr[],int dim, int i,int grado,int counter)
{
	if(i>=dim-1)
	{	
        if(i>dim-1)
		{
			return counter;
		}
		
	    else
	    {
		    if(arr[i]>=grado)
		    {
			    return counter+1;
		    }
		    else
		    {
		        return counter;
		    }
		}
	}
	else
	{
		if(arr[i]>=grado)
		{
			int a=combinazione(arr,dim,i+2,arr[i],counter+1);
			int b=combinazione(arr,dim,i+1,grado,counter);
			if(a>b)
			{
			//	return combinazione(arr,dim,i+2,arr[i],counter+1);
			    return a;
			}
			else
			{
			//	return combinazione(arr,dim,i+1,grado,counter);
			    return b;
			}
		}
		else
		{
			return combinazione(arr,dim,i+1,grado,counter);
		}
	}
	
}
		
		
		
		







int main()
{
	fstream miofile("inputt.txt",fstream::in);
	fstream outfile("output.txt",fstream::out);
	
	for(int riga=1; riga<=100; riga++)
	{
//		bool nove=false;
//		if(riga==9)
//			nove=true;
		
		int x;
		miofile>>x;
		int vett[x];
		
		for(int i=0; i<x; i++)
		{
			int a;
			miofile>>a;
			vett[i]=a;
		}
/*		if(nove)
		{
			Stampa(vett,x);
		}  */
		
//		cout<<combinazione(vett,x,0,0,0)<<endl;
        outfile<<combinazione(vett,x,0,0,0)<<endl;
		
		
		/*
		int counter=1;
		int grado_alcolico=vett[0];
		if(nove)
		{
			cout<<grado_alcolico<<endl;
		}
		
		for(int i=2; i<x; i++)
		{
			if(grado_alcolico<=vett[i])
			{
				if(nove)
				{
					cout<<"grado="<<grado_alcolico<<", vett["<<i<<"]="<<vett[i]<<endl;
				}
				grado_alcolico=vett[i];
				counter++;
				i++;
			}
		}
		if(nove)
		{
			cout<<counter<<endl;
		}
		
		outfile<<counter<<endl;
		*/
	}
	miofile.close();
	outfile.close();
}

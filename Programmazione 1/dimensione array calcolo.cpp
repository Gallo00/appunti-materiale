#include <iostream>
#include <math.h>

using namespace std;

int main(){
	
	
	
	int arr[6][3][4]={2,4,3,6,7,5};
	
	int dimX=sizeof(arr)/sizeof(arr[0]);
	cout<<dimX<<endl;
	
	int dimY=sizeof(arr)/sizeof(arr[0][0]);
	dimY=dimY/dimX;
	cout<<dimY<<endl;
	
	int dimZ=sizeof(arr)/sizeof(arr[0][0][0]);
	dimZ=dimZ/(dimX*dimY);
	cout<<dimZ;
}

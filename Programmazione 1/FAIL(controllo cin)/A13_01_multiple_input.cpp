#include <iostream>
#include <string>
#include <limits>

using namespace std;

/* DUE Input (stringhe) di natura differente 
*  + Controllo errore
* - Controllo EOF 
* + Caratteri ``garbage'' vengono scartati  
*/ 

//Provare i seguenti input: 
//Pippo 
//Pippo pippo2 
int main(){
  
  string s; 

  //1.Primo input
  cout << "Insert a string: " << endl;
  cin >> s;
 
  //2.Controllo eventuali errori.
  if(cin.fail()){ //some IO error!
    cerr << "IO error: cin.fail()=" << cin.fail() << endl;
    //3.reset stato di errore dell'oggetto cin..
    cout << "Now clearing the error flags.." << endl;
    cin.clear();
    cout << "cin.fail()=" << cin.fail() << endl;
  }

  else
    cout << "You entered: " << s << endl;

  //scarta ulteriore input 
 
cin.ignore(numeric_limits<streamsize>::max(), '\n');
  //4. Now we are ready to take some more input and to check for
  //any error..
  cout << "Now let's take some more input for a different reason. Please insert another string:" << endl;
  cin >> s;

  //5.Notifica errore 
  if(cin.fail()){ //some IO error!
    cerr << "IO error: cin.fail()=" << cin.fail() << endl; 
  }

  else
    cout << "You entered:  " << s << endl;
  cout << "Exit!" << endl;
}

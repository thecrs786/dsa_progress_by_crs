// SINGLE LINE COMMENT

/* MULTIPLE
LINE
COMMENT

SELECT LINES AND USE CTRL+/ FOR COMMENTING OUT LINES
*/

#include<iostream>
using namespace std;  

int main(){

cout << "thecrs"; // OR std::cout << "thecrs";  if didn't use namepace std above
cout<<"\nHello World"<<endl;
cout<<"Dsa is fun"<<endl;
// cout << "thecrs" << endl;  --> to move to next line for next output
// or  cout << "thecrs" << "\n"; --> \n is faster
// or  cout << "thecrs\n"; --> \n is faster

return 0;
}

/*

TO COMPILE --> g++ 001_Output.cpp
TO RUN --> ./a.exe

TO DO BOTH AT ONCE --> g++ 001_Output.cpp ; ./a.exe

SHORTCURT BY ME to compile an run -> shift+spacebar (code runner extension)  --> SAVE -> COMPILES -> RUNS
*/

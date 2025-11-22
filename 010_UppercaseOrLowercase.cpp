// FIND CHARACTER UPPERCASE OR LOWERCASE

#include<iostream>
using namespace std;  

int main(){

char ch;

cout<<"Enter a character : ";
cin>> ch;

/* (1)

if(ch>='A' && ch<='Z'){
     cout<<"Uppercase";
}
else if(ch>='a' && ch<='z'){
    cout<<"Lowecase";
}
else{cout<<"Error : Enter between 'A' to 'Z' or 'a' to 'z' ";}
*/

// We used ascii values for this operation

/* (2)

if(ch>=65 && ch<=90){
    cout<<"Uppercase";
}
else if(ch>=97 && ch<=122){
    cout<<"Lowecase";
}
else{cout<<"Error : Enter between 'A' to 'Z' or 'a' to 'z' ";}
*/

// (3)

if(ch>=int('A') && ch<=int('Z')){
     cout<<"Uppercase";
}
else if(ch>=int('a') && ch<=int('z')){
    cout<<"Lowecase";
}
else{cout<<"Error : Enter between 'A' to 'Z' or 'a' to 'z' ";}


return 0;
}
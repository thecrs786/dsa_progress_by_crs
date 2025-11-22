// MARKS TO GRADE

#include<iostream>
using namespace std;  

int main(){

int marks;

cout<< "Enter marks : ";
cin>> marks;

if(marks>90 && marks <=100){
    cout<<"A"<<endl;
}

else if(marks>80 && marks <=90){
    cout<<"B";
}

else if(marks>70 && marks <=80){
    cout<<"C";
}
else if (marks>60 && marks <=70){
    cout<<"D";
}
else if (marks>50 && marks <=60){
    cout<<"E";
}
else if(marks >=0 && marks <=50){
    cout<<"Fail";
}

else{cout<<"Error : Enter marks between 0-100";}
return 0;
}
#include<iostream>
#include<vector>
#include<string>
#include"book.h"
using namespace std;




int main(){
    book b1;
    
    getline(cin,b1.title);
    getline(cin,b1.author);
    cout<<"the title of book is: "<<b1.title<<endl;
    cout<<"the author of the book is: "<<b1.author;

    return 0;

}
#include<iostream>
#include<string>
using namespace std;

void reverseString(string & s){
    int i=0, j=s.size()-1;
    
    while(i<j){
        swap(s[i++],s[j--]);

    }
}

int main(){
    string s="Hannah";
    reverseString(s);
    cout<<s;
    return 0;
}
#include<iostream>
#include<string>
using namespace std;

bool palindrome(string s, int i, int j){
    while(i<j){
        if(s[i]!=s[j]) return false;
        else{
            i++;
            j--;
        }
    }
    return true;
}

bool validPalindrome(string s){
    int i=0,j=s.size()-1;
    while(i<j){
        if(s[i]==s[j]){
            i++;
            j--;
        }
        else{
            return (palindrome(s,i+1,j) || palindrome(s,i,j-1));
        }
    }
    return true;
}


int main(){
    string s="abca";
    bool ans=validPalindrome(s);
    cout<<ans;
    return 0;
}
#include<iostream>
#include<string>
using namespace std;

string expandAroundCenter(string s, int left, int right){
    while(left>=0 && right<s.size() && s[left]==s[right]){
        left--;
        right++;
    }
    return s.substr(left+1, right-left-1);
}

string LongestPalindrome(string s){
    string longestString="";
    for(int i=0;i<s.size();i++){
        string oddString=expandAroundCenter(s,i,i);
        string even=expandAroundCenter(s,i,i+1);
        if(oddString.size()>longestString.size()) longestString=oddString;
        if(even.size()>longestString.size()) longestString=even;
    }
    return longestString;
}

int main(){
    string s="babad";
    cout<<LongestPalindrome(s);
    return 0;
}
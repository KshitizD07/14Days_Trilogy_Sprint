#include<iostream>
#include<string>
#include<unordered_set>
using namespace std;

int LengthOfLongestSubstring(string s){
    unordered_set<char> set;
    int maxLength=0;
    int i=0;
    int n=s.size();
    for(int j=0;j<n;j++){
        // while(j<n && !set.count(s[j])){
        //     set.insert(s[j]);
        //     j++;
        // }
        while(set.count(s[j])){
            set.erase(s[j]);
            i++;
        }
        set.insert(s[j]);
        maxLength=max(maxLength,j-i);
    }
    return maxLength;
}

int main(){
    string s="abcabcbb";
    cout<<LengthOfLongestSubstring(s);
    return 0;
}
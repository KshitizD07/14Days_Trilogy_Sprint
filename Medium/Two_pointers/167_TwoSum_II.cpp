#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

vector<int> twoSum(vector<int>& arr, int target){
    sort(arr.begin(),arr.end());
    int i=0,j=arr.size()-1;

    while(i<j){
        int sum=arr[i]+arr[j];
        if(sum<target) i++;
        else if(sum>target) j--;
        else return {i+1, j+1}; //If the size of vector is specified, we can return like this, otherwise we can push_back in a new vector.
    }
    return {};
}

int main(){
    vector<int> arr={2,7,11,15};
    int target=9;
    vector<int> ans=twoSum(arr,target);
    for(auto i:ans) cout<<i<<" ";
    return 0;
}
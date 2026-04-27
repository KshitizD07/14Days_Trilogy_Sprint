#include<iostream>
#include<vector>
using namespace std;

vector<int> sortedSquares(vector<int>& nums){
    int n=nums.size();
    vector<int> result(n);
    int i=0, j=n-1, k=n-1;
    while(i<=j){
        int left=nums[i]*nums[i];
        int right=nums[j]*nums[j];
        if(left>right){
            result[k--]=left;
            i++;
        }
        else{
            result[k--]=right;
            j--;
        }
    }
    return result;
}

int main(){
    vector<int> nums={-4,-1,0,3,10};
    vector<int> result=sortedSquares(nums);
    for(int x: result){
        cout<<x<<" ";
    }
    return 0;
}
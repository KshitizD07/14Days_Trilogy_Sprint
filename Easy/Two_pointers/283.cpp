// Given an integer array nums, move all 0's to the end of it while maintaining the relative order of the non-zero elements.

// Note that you must do this in-place without making a copy of the array.

#include<iostream>
#include<vector>
using namespace std;

void moveZeroes(vector<int>& nums){
    int i=0,j=0;
    while(j<nums.size()){
        if(nums[j]!=0){
            if(nums[i]==0){
                swap(nums[i],nums[j]);
            }
            i++;
        }
        j++;
    }
}

int main(){
    // vector<int> nums={0,1,0,3,12};
    vector<int> nums={1,0,1};
    moveZeroes(nums);
    for(int x:nums){
        cout<<x<<" ";
    }
    return 0;
}
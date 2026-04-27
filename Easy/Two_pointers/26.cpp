// Given an integer array nums sorted in non-decreasing order, remove the duplicates in-place such that each unique element appears only once. The relative order of the elements should be kept the same.

// Consider the number of unique elements in nums to be k​​​​​​​​​​​​​​. After removing duplicates, return the number of unique elements k.

// The first k elements of nums should contain the unique numbers in sorted order. The remaining elements beyond index k - 1 can be ignored.

#include<iostream>
#include<vector>
using namespace std;

int removingDuplicates(vector<int>& nums, int length){
    int i=0;
    for(int j=i+1;j<length;j++){
        if(nums[i]!=nums[j]){
            i++;
            nums[i]=nums[j];
        }
    }
    return i+1;
}

int main(){
    vector<int> nums={0,0,1,1,1,2,2,3,3,4};
    int k=removingDuplicates(nums, nums.size());
    cout<<"The number of unique elements is: "<<k<<endl;
    return 0;
}
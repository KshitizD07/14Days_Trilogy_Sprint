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
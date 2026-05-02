#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int threeSumClosest(vector<int>& nums, int target){
    sort(nums.begin(),nums.end());
    int size=nums.size();
    int closestSum=nums[0]+nums[1]+nums[2];

    for(int i=0;i<size-2;i++){
        int left=i+1;
        int right=size-1;

        while(left<right){
            int sum=nums[i]+nums[left]+nums[right];

            if(abs(sum-target)<abs(closestSum-target)){
                closestSum=sum;
            }
            if(sum==target) return sum;
            else if(sum<target) left++;
            else right--;
        }
    }
    return closestSum;
}

int main(){
    vector<int> nums={-1,2,1,-4};
    int target=1;
    int ans=threeSumClosest(nums,target);
    cout<<ans<<endl;
    return 0;
}
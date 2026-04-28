#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

vector<vector<int>> threesum(vector<int>& nums){
    vector<vector<int>> result;
    int n=nums.size();

    sort(nums.begin(),nums.end());

    for(int i=0;i<n-2;i++){
        int j=i+1, k=n-1;
        if(i>0 && nums[i]==nums[i-1]) continue; 
        while(j<k){
            int sum=nums[i]+nums[j]+nums[k];
            if(sum==0){
                result.push_back({nums[i],nums[j++],nums[k--]});
                while(j<k && nums[j]==nums[j-1]) j++;
                while(j<k && nums[k]==nums[k+1]) k--;
            }
            else if(sum<0){
                j++;
            }
            else{
                k--;
            }
        }
    }
    return result;
}

int main(){
    vector<int> nums={-1,0,1,2,-1,-4};
    vector<vector<int>> result=threesum(nums);
    for(const auto& triplet:result){
        cout<<"{ ";
        for(int x: triplet){
            cout<<x<<" ";
        }
        cout<<"}"<<endl;
    }
    return 0;
}
#include<iostream>
#include<vector>
using namespace std;

int trap(vector<int>& height){
    int n=height.size();
    int left=0, right=n-1;
    int leftmax=0, rightmax=0,water=0;
    while(left<right){
        if(height[left]<height[right]){
            if(height[left]>leftmax){
                leftmax=height[left];
            }
            else{
                water+=leftmax-height[left];
            }
            left++;
        } else {
            if(height[right]>rightmax){
                rightmax=height[right];
            }
            else{
                water+=rightmax-height[right];
            }
            right--;
        }
    }
    return water;
}

int main(){
    vector<int> height={0,1,0,2,1,0,1,3,2,1,2,1};
    int trappedWater=trap(height);
    cout<<"Trapped water: "<<trappedWater<<endl;
    return 0;
}
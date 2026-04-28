// You are given an integer array height of length n. There are n vertical lines drawn such that the two endpoints of the ith line are (i, 0) and (i, height[i]).

// Find two lines that together with the x-axis form a container, such that the container contains the most water.

// Return the maximum amount of water a container can store.

// Notice that you may not slant the container.


#include<iostream>
#include<vector>
using namespace std;

int C_W_M_W(vector<int>& height){
    int i=0, j=height.size()-1;
    int maxArea=0;
    while(i<j){
        int h=min(height[i],height[j]);
        maxArea=max(maxArea,h*(j-i));
        if(height[i]>height[j]){
            j--;
        }
        else{
            i++;
        }
    }
    return maxArea;
}

int main(){
    vector<int> height={1,8,6,2,5,4,8,3,7};
    int area=C_W_M_W(height);
    cout<<area;
    return 0;
}
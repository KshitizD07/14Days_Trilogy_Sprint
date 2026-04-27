// You are given two integer arrays nums1 and nums2, sorted in non-decreasing order, and two integers m and n, representing the number of elements in nums1 and nums2 respectively.

// Merge nums1 and nums2 into a single array sorted in non-decreasing order.

// The final sorted array should not be returned by the function, 
// but instead be stored inside the array nums1. To accommodate this, 
// nums1 has a length of m + n, where the first m elements denote the elements that should be merged, 
// and the last n elements are set to 0 and should be ignored. nums2 has a length of n.

#include<iostream>
#include<vector>
using namespace std;

void merge_sorted_arrays(vector<int>& n1, int m, vector<int>& n2, int n){
    int i=m-1;
    int j=n-1;
    int k=m+n-1;
    while(i>=0 && j>=0){
        if(n1[i]>n2[j]){
            n1[k--]=n1[i--];
        }
        else{
            n1[k--]=n2[j--];
        }
    }
    while(j>=0){
        n1[k--]=n2[j--];
    }
}

int main(){
    vector<int> n1={1,2,3,0,0,0};
    vector<int> n2={2,5,6};
    int count=0;
    for(int x:n1){
        if(x!=0){
            count++;
        }
    }
    merge_sorted_arrays(n1,count,n2,n2.size());
    cout<<"The merged array is: ";
    for(int x:n1){
        cout<<x<<" ";
    }
    return 0;
}
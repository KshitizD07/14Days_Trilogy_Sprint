#include<iostream>
#include<vector>
using namespace std;

void merge(vector<int>&arr, int low, int mid, int high, vector<int>&temp){
    int i=low, j=mid+1, k=low;
    while(i<=mid && j<=high){
        if(arr[i]<arr[j]){
            temp[k]=arr[i];
            i++;
            k++;
        }
        else{
            temp[k]=arr[j];
            j++;
            k++;
        }
    }
    while(i<=mid){
        temp[k++]=arr[i++];
    }
    while(j<=high){
        temp[k++]=arr[j++];
    }
    for(int i=low;i<=high;i++){
        arr[i]=temp[i];
    }
}

void merge_sort(vector<int>&arr, int low,int high, vector<int>&temp){
    if(low>=high) return;
    int mid=low+(high-low)/2;
    merge_sort(arr,low,mid,temp);
    merge_sort(arr,mid+1,high,temp);
    
    merge(arr,low, mid, high, temp);

}

int main(){
    vector<int> arr={1,7,5,2,3,9,4,6,7};
    vector<int> temp(arr.size());
    merge_sort(arr,0,arr.size()-1,temp);
    for(int x:arr) cout<<x<<" ";
    return 0;
}
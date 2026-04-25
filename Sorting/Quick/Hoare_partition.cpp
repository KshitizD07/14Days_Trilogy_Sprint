#include<iostream>
#include<vector>
using namespace std;

int partition(vector<int>&arr, int low, int high){
    int mid=low+(high-low)/2;
    
    if(arr[mid]<arr[low]){
        swap(arr[mid],arr[low]);
    }
    if(arr[mid]>arr[high]){
        swap(arr[mid],arr[high]);
    }
    if(arr[low]>arr[high]){
        swap(arr[low],arr[high]);
    }
    int pivot=arr[mid];
    int i=low-1, j=high+1;
    while(true){
        do{i++;}while(arr[i]<pivot);
        do{j--;}while(arr[j]>pivot);
        if(i>=j){
            return j;
        }
        swap(arr[i],arr[j]);
    }
}

void QS(vector<int>&arr, int low, int high){
    if(low>=high)return ;
    int q=partition(arr,low,high);
    QS(arr,low,q);
    QS(arr,q+1,high);
}

int main(){
    vector<int> arr={1,7,5,2,3,9,4,6,7,0};
    QS(arr,0,arr.size()-1);
    for(int x:arr) cout<<x<<" ";
    return 0;
}
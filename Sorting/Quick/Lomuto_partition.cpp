#include<iostream>
#include<vector>
using namespace std;

int partition(vector<int>&arr, int low, int high){
    int pivot=arr[high];
    int i=low-1;
    for(int j=low;j<high;j++){
        if(arr[j]<pivot){
            i++;
            swap(arr[i],arr[j]);
        }
    }
    swap(arr[i+1],arr[high]);
    return i+1;
}

void QS(vector<int>&arr, int low, int high){
    if(low>=high)return ;
    int q=partition(arr,low,high);
    QS(arr,low,q-1);
    QS(arr,q+1,high);
}

int main(){
    vector<int> arr={1,7,5,2,3,9,4,6,7};
    QS(arr,0,arr.size()-1);
    for(int x:arr) cout<<x<<" ";
    return 0;
}
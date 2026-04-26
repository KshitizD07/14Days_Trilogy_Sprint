#include<iostream>
#include<vector>
using namespace std;

class heap{
    public:
        int index=0;
        void insert(vector<int>&arr, int val){
            arr[index]=val;
            int i=index;
            while(i>0){
                int parent=(i-1)/2;
                if(arr[i]>arr[parent]){
                    swap(arr[i],arr[parent]);
                    i=parent;
                }
                else{
                    break;
                }
            }
            index++;
        } 
};

int main(){
    vector<int>arr(5);
    heap h;
    h.insert(arr,1);
    h.insert(arr,7);
    h.insert(arr,5);
    h.insert(arr,2);
    h.insert(arr,77);
    for(int x:arr)cout<<x<<" ";
    return 0;
}
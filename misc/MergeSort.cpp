#include<vector>
#include <iostream>
using namespace std;
template <typename T>

class MergeSort{
    public :
    void mergesort(vector<T>& arr, int start, int end, int(*compare)(T, T)){
        sort(arr, start, end, compare);
    }

    private: 

    void sort(vector<T>& arr, int start, int end, int (*compare)(T,T)){
        if (start >= end) return;
    
        int mid = start+ (end-start)/2;
    
        sort(arr, start, mid, compare);
        sort(arr, mid+1, end,  compare);
    
        merge (arr, start, mid, end, compare);
    }

    void merge(vector<T>& arr, int start, int mid, int end, int(*compare)(T,T)){
        vector<T> temp(end-start+1);
        int i = 0;
        int index2 = start;
        int index3 = mid+1;
    
        while (index2 <= mid && index3 <= end){
            if (compare(arr[index2], arr[index3]) < 0){
                    temp[i++] = arr[index2++];
            }else{
                temp[i++] = arr[index3++];        
            }
        }
    
        while (index2 <= mid){
            temp[i++] = arr [index2++];
        }
    
        while (index3 <= end){
            temp[i++] = arr[index3++];
        }
    
        for (int i = 0; i< temp.size(); i++){
            arr[i+start] = temp[i];
        }
        }
    };





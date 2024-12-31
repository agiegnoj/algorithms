#include<vector>
#include <iostream>
using namespace std;
template <typename T>

class MergeSort{
    public :
    void mergesort(vector<T>& arr, int start, int end){
        static_assert(std::is_arithmetic<T>::value, "Type T must be arithmetic.");
        sort(arr, start, end);
    }

    private: 
    void sort(vector<T>& arr, int start, int end){
        if (start >= end) return;

        int mid = start+ (end-start)/2;

        sort(arr, start, mid);
        sort(arr, mid+1, end);

        merge (arr, start, mid, end);

    }

    void merge(vector<T>& arr, int start, int mid, int end){
        vector<T> temp(end-start+1);
        int i = 0;
        int index2 = start;
        int index3 = mid+1;

        while (index2 <= mid && index3 <= end){
            if (arr[index2] < arr[index3]){
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



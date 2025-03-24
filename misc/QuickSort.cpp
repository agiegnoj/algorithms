#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
template <typename T>

class QuickSort{

    public :

    void quickSort(std::vector<T>& arr, int start, int end, int (*compare)(T, T)) {
        if (arr.size() == 0 || start >= end)
            return;
    
        int mid = start + (end - start) / 2;
        T pivot = arr[mid];
    
        swap(arr[mid], arr[end]);  
        int j = start - 1;
    
        for (int i = start; i < end; i++) {
            if (compare(arr[i], pivot) < 0) {
                j++;
                swap(arr[i], arr[j]);
            }
        }
    
        swap(arr[end], arr[j + 1]); 
    
        quickSort(arr, start, j, compare);     
        quickSort(arr, j + 2, end, compare);   
    }
};











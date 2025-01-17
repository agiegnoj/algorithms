#include <vector>

using namespace std;
template <typename T>

class QuickSort{

    public :

    void quickSortAscending(vector<T>& arr, int start, int end){
        static_assert(std::is_arithmetic<T>::value, "Type T must be arithmetic.");
        
        if (arr.size() == 0 || start >= end ) return;

        int mid = start + (end-start)/2;
        T pivot = arr[mid];

        swap(arr[mid], arr[end]);
       
        int j = start-1;

        for (int i = start; i < end; i++){
            if (arr[i] < pivot){
                j++;
                swap(arr[i], arr[j]);
            }
        }

        swap (arr[end], arr[j+1]);

        quickSortAscending(arr, start, j+1);
        quickSortAscending(arr, j+2, end);

    }

    void quickSortDescending(vector<T>& arr, int start, int end){
        static_assert(std::is_arithmetic<T>::value, "Type T must be arithmetic.");
        
        if (arr.size() == 0 || start >= end ) return;

        int mid = start + (end-start)/2;
        T pivot = arr[mid];

        swap(arr[mid], arr[end]);
        int j = start-1;

        for (int i = start; i < end; i++){
            if (arr[i] > pivot){
                j++;
                swap(arr[i], arr[j]);
            }
        }

        swap (arr[end], arr[j+1]);

        quickSortDescending(arr, start, j+1);
        quickSortDescending(arr, j+2, end);

    }

};





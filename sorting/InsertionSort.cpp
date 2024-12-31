#include <vector>
using namespace std;
template <typename T>

class InsertionSort{
    public:

    vector <T> insertionSortAscending(vector<T>& arr){
        static_assert(std::is_arithmetic<T>::value, "Type T must be arithmetic.");

        for (int i = 1; i<arr.size(); i++){
           
            int left = i-1;
            T temp = arr[i];

            while (left >= 0  && temp < arr[left]){
                arr[left+1] = arr [left];
                arr [left] = temp;
                left--;
            }
        }

        return arr;
    }

    vector <T> insertionSortDescending(vector<T>& arr){

        for (int i = 1; i < arr.size(); i++){
           
            int left = i-1;
            T temp = arr[i];

            while (left >= 0  && temp > arr[left]){
                arr[left+1] = arr [left];
                arr [left] = temp;
                left--;
            }
        }

        return arr;
    }

};


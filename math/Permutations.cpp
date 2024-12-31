#include <vector>
#include <iostream>
#include <iostream>
using namespace std;
template <typename T>

class Permutations{
    public:
    vector<vector<T>> permutations(vector<T>& arr){
        vector<vector<T>> res;

        getPermutations(arr, res, 0, arr.size());

        return res;
    }

    private:

    void getPermutations(vector<T>& arr, vector<vector<T>>& res, int index, int end){
       
        if (index == end){
            res.push_back(arr);
            return;
        }
        
        for(int i = index; i < end; i++){
            swap(arr[index], arr[i]);
            getPermutations(arr, res, index+1, end);
            swap(arr[index], arr[i]);
        }
    }
};



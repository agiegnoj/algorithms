#include <vector>
#include <iostream>
using namespace std;
template <typename T>

class NchooseK{
    public:

    vector<vector<T>> nChooseK(vector<T> arr, int k){
        if (k <= arr.size()){
            vector<T> temp;
            vector<vector<T>> res;
            getCombinations(arr, temp, res, 0, k);
            return res;
        }else{
           return {};
        }
    }

    private:

    void getCombinations(vector<T>& arr, vector<T>& temp, vector<vector<T>>& res, int index, int k ){
        if (temp.size() == k){
            res.push_back(temp);
            return;
        }

        if (index == arr.size())return;

        for (int i = index; i < arr.size(); i++){
            temp.push_back(arr[i]);
            getCombinations(arr, temp, res, i+1, k);
            temp.pop_back();
        }   
    }
};



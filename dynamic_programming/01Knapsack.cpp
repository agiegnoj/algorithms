#include <vector>
using namespace std;

class ZeroOneKnapsack{
    
    vector<int> ItemValueList(vector <int> value, vector<int> weight, int capacity){
        if (value.size()!= weight.size()) return {};

        int n = value.size();

        vector<vector<long>> tabulation (n+1, vector<long> (capacity+1, 0));
        vector<int> res;

        for (int i = 1; i <= n; i++){
            for (int j = 0; j <= capacity; j++){
                if (weight [i-1]  <= j) 
                tabulation[i][j] = max(value[i-1]+tabulation[i-1][j-weight[i-1]], tabulation[i-1][j] );
                else
                tabulation [i][j] = tabulation[i-1][j];

            }
        }

        int w = capacity;

        for (int i = n-1; i > 0; i--){
            if (tabulation[i][w] != tabulation[i-1][w]){
                res.push_back(value[i]);
                w -= weight[i];
            }  
        }

        return res;
        }

        long MaxValue(vector<int>& value, vector<int>& weight, int capacity  ){

            if (value.size() != weight.size())
            return -1;

            int n = value.size();

            vector <int> tabulation (capacity+1, 0);

            for (int i = 0; i < n; i++){
            for (int j = capacity; j >= weight[i]; j--){
                tabulation [j] = max (tabulation[j], tabulation[j-weight[i]] + value[i]);

            }
     
        }

        return tabulation[capacity];

        }

};
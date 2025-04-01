#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;

template<typename T>

class PolynomialInterpolation{

    public:

    vector <T> interpolate (vector<T>& x, vector<T>& y){
        if (x.size() != y.size())throw invalid_argument("false input");
        int n = x.size();

        vector<vector<T>> memo(x.size(), vector<T> (x.size(), 1e9));
     
        vector<T> polynomial (n);
        polynomial[0] = y[0];

        for (int i = 1; i< n; i++){
            polynomial[i] = dividedDifferences(x, y, 0, i, memo);
        }

        return polynomial;
    }

    private:

    T dividedDifferences(vector<T>& x, vector<T>& y, int indexOne, int indexTwo, vector<vector<T>>& memo){
        

        if (memo[indexOne][indexTwo]!= 1e9){
            return memo[indexOne][indexTwo];
        }

        if (indexTwo-indexOne == 1){
            T diff = (y[indexTwo]-y[indexOne])/(x[indexTwo]-x[indexOne]);
            memo[indexOne][indexTwo] = diff;
            return diff;
        }

        T diff = (dividedDifferences(x, y, indexOne+1, indexTwo, memo)
        -dividedDifferences(x, y, indexOne, indexTwo-1, memo)) / (x[indexTwo]-x[indexOne]);

        memo [indexOne][indexTwo] = diff;

        return diff;

    }

    };


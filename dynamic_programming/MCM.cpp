#include <vector>
#include <limits>

using namespace std;

template <typename T>
class MCM {
public:
    vector<vector<T>> optimalMultiplication(const vector<vector<vector<T>>>& matrices) {
        vector<int> dims = getDimensions(matrices);

        int size = matrices.size();
        vector<vector<long>> dpCost(size, vector<long>(size, 0));
        vector<vector<int>> dpSplit(size, vector<int>(size, 0));

        for (int l = 1; l < size; l++) {
            for (int i = 0; i < size - l; i++) {
                int j = i + l;
                dpCost[i][j] = numeric_limits<long>::max();

                for (int k = i; k < j; k++) {
                    long cost = dpCost[i][k] + dpCost[k + 1][j] + dims[i] * dims[k + 1] * dims[j + 1];
                    if (cost < dpCost[i][j]) {
                        dpCost[i][j] = cost;
                        dpSplit[i][j] = k;
                    }
                }
            }
        }

        return compute(matrices, dpSplit, 0, size - 1);
    }

private:
    vector<vector<T>> compute(const vector<vector<vector<T>>>& matrices, const vector<vector<int>>& dpSplit, int i, int j) {
        if (i < j) {
            int k = dpSplit[i][j];
            vector<vector<T>> m1 = compute(matrices, dpSplit, i, k);
            vector<vector<T>> m2 = compute(matrices, dpSplit, k + 1, j);
    
            return multiply(m1, m2);     
        } 
        return matrices[i];
    }

    vector<vector<T>> multiply(const vector<vector<T>>& m1, const vector<vector<T>>& m2) {
        if (m1[0].size() != m2.size())
        throw invalid_argument("Matrices are not valid.");

        int r = m1.size();
        int c = m2[0].size();
        int a = m2.size();  

        vector<vector<T>> res(r, vector<T>(c, 0));

        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                for (int l = 0; l < a; l++) {
                    res[i][j] += m1[i][l] * m2[l][j];
                }
            }
        }
        return res;
    }

    vector<int> getDimensions(const vector<vector<vector<T>>>& matrices) {
        vector<int> dims;
        dims.push_back(matrices[0].size()); 
        for (vector<vector<T>> m : matrices) {
            dims.push_back(m[0].size());  
        }
        return dims;
    }
};


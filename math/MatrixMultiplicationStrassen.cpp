#include <vector>
#include <type_traits> 
#include <iostream>
using namespace std;
template <typename T>

class MatrixMultiplication{
    public: 

    vector<vector<T>> multiplyMatrices(const vector<vector<T>> m1, vector<vector<T>> m2){
        static_assert(std::is_arithmetic<T>::value, "Type T must be arithmetic.");
  
        if (m1[0].size() != m2.size())
        throw invalid_argument("Matrices are not valid.");
        
       
            int temp = max (m1.size(), m2[0].size());
            int size = findNextPowerOfTwo(temp);
            
           vector <vector<T>> paddedResult = multiplyMatricesStrassen(padding(m1, size), padding(m2, size), 0, 0, 0, 0, size);
           
           return finalResult ( paddedResult, m1.size(), m2[0].size());
        
    }

   private: 

    vector<vector<T>> multiplyMatricesStrassen(vector<vector<T>> m1, vector<vector<T>> m2, int r1, int c1, int r2, int c2, int n) {
        vector<vector<T>> res(n, vector<T>(n, 0));
        
        if (n == 1) {
            res[0][0] = m1[r1][c1] * m2[r2][c2];
        } else {
            int mid = n / 2;

            vector<vector<T>> A11 = getSubmatrix(m1, r1, c1, mid);
            vector<vector<T>> A12 = getSubmatrix(m1, r1, c1 + mid, mid);
            vector<vector<T>> A21 = getSubmatrix(m1, r1 + mid, c1, mid);
            vector<vector<T>> A22 = getSubmatrix(m1, r1 + mid, c1 + mid, mid);

            vector<vector<T>> B11 = getSubmatrix(m2, r2, c2, mid);
            vector<vector<T>> B12 = getSubmatrix(m2, r2, c2 + mid, mid);
            vector<vector<T>> B21 = getSubmatrix(m2, r2 + mid, c2, mid);
            vector<vector<T>> B22 = getSubmatrix(m2, r2 + mid, c2 + mid, mid);

            vector<vector<T>> P1 = multiplyMatricesStrassen(A11, subtract(B12, B22, mid), 0, 0, 0, 0, mid);
            vector<vector<T>> P2 = multiplyMatricesStrassen(add(A11, A12, mid), B22, 0, 0, 0, 0, mid);
            vector<vector<T>> P3 = multiplyMatricesStrassen(add(A21, A22, mid), B11, 0, 0, 0, 0, mid);
            vector<vector<T>> P4 = multiplyMatricesStrassen(A22, subtract(B21, B11, mid), 0, 0, 0, 0, mid);
            vector<vector<T>> P5 = multiplyMatricesStrassen(add(A11, A22, mid), add(B11, B22, mid), 0, 0, 0, 0, mid);
            vector<vector<T>> P6 = multiplyMatricesStrassen(subtract(A12, A22, mid), add(B21, B22, mid), 0, 0, 0, 0, mid);
            vector<vector<T>> P7 = multiplyMatricesStrassen(subtract(A11, A21, mid), add(B11, B12, mid), 0, 0, 0, 0, mid);

            vector<vector<T>> C11 = add(subtract(add(P5, P4, mid), P2, mid), P6, mid);
            vector<vector<T>> C12 = add(P1, P2, mid);
            vector<vector<T>> C21 = add(P3, P4, mid);
            vector<vector<T>> C22 = subtract(subtract(add(P5, P1, mid), P3, mid), P7, mid);

            for (int i = 0; i < mid; i++) {
                for (int j = 0; j < mid; j++) {
                    res[i][j] = C11[i][j];
                    res[i][j + mid] = C12[i][j];
                    res[i + mid][j] = C21[i][j];
                    res[i + mid][j + mid] = C22[i][j];
                }
            }
        }
       return res;
    }

    vector<vector<T>> finalResult(vector<vector<T>> m1, int size1, int size2 ){
        vector<vector<T>> finalResult (size1, vector<T>(size2));

        for (int i = 0; i <size1; i++){
            for (int j = 0; j < size2; j++){
                finalResult[i][j] = m1[i][j];
            }
        }

        return finalResult;
    }



    vector<vector<T>> add(vector<vector<T>> m1, vector<vector<T>> m2, int n) {
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                 m1[i][j] += m2[i][j];
            }
        }
        return m1;
    }

    vector<vector<T>> subtract(vector<vector<T>> m1, vector<vector<T>> m2, int n) {       
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                m1[i][j] -= m2[i][j];
            }
        }
        return m1;
    }

    vector<vector<T>> getSubmatrix(vector<vector<T>> &matrix, int row, int col, int size) {
        vector<vector<T>> subM (size, vector<T>(size, 0));

        for (int i = 0; i< size; i++){
            for (int j = 0; j < size; j++){
                subM [i][j] = matrix[i+row][j+col];
            }
        }

        return subM;
    }

    int findNextPowerOfTwo(int size){
        int res = 1;
        while (res < size){
            res *= 2;
        }
        return res;
    }

    vector<vector<T>> padding(vector<vector<T>> m, int size){
        vector<vector<T>> newM (size, vector<T> (size, 0));
        for (int i = 0; i < m.size(); i++){
            for (int j = 0; j < m[0].size(); j++){
                newM[i][j] = m[i][j];
            }
        }
        return newM;
    }
    };



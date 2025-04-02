#include <vector>
#include <stdexcept>

using namespace std;

template <typename T>

class Gauss{

    public:

    int gaussianElimination(vector<vector<T>>& matrix){

        const T epsilon = 1e-9;

        int n = matrix.size();
        int m = matrix[0].size();
        int swaps = 0;

        for (int c = 0; c< n ; c++){
            int temp = c;
            T maxValue = abs(matrix[c][c]);

            for (int r= c+1; r < n; r++){
                if (abs(matrix[r][c]) > maxValue){
                    maxValue = abs(matrix[r][c]);
                    temp = r;
                }     
            }
            if (c!= temp){
                swap(matrix[c], matrix[temp]);
                swaps++;
            } 

            if (abs(matrix[c][c])< epsilon){
                return -1;
            }

            for (int r = c + 1; r < n; r++) {
                T factor = matrix[r][c] / matrix[c][c]; 
    
                for (int i = c; i < m; i++) {
                    matrix[r][i] -= factor * matrix[c][i]; 
                }
            }
        }

        return swaps;
    }

    vector<T> solveLinearEquationSystem(vector<vector<T>>& matrix){
        if (matrix.size()+1 != matrix[0].size()) {
            throw invalid_argument("invalid input");
        }

        int n = matrix.size();
        vector<T> res (n, 0);

        if (gaussianElimination(matrix) != -1){

            for (int r = n-1; r >= 0; r--){
                T sum = 0;
                for (int c = n-1; c > r; c--){
                    sum += matrix[r][c]*res[c];
                }
                res[r] = (matrix[r][n]-sum) / matrix[r][r] ;
            }       
        }else{
            throw invalid_argument("invalid input");
        }
        return res;
    }

    T determinant(vector<vector<T>> matrix){
        if (matrix.size() != matrix[0].size())
        throw invalid_argument("invalid input");

        T determinant = 1;

        int swaps = gaussianElimination(matrix);

        if (swaps != -1){
            for (int i = 0; i< matrix.size(); i++){
                determinant *= matrix[i][i];
            }  
            
            return swaps % 2 == 0 ? determinant : -determinant;
        }
        return 0;     
    }

    vector<vector<T>> inverse(vector<vector<T>> matrix){
        if(matrix.size() != matrix[0].size()){
            throw invalid_argument("invalid input");
        }

        int n = matrix.size();

        for (int i = 0; i < n; i++){
            matrix[i].resize(2*n);
            matrix[i][i+n] = 1;
        } 

        if (gaussianElimination(matrix) == -1){
            throw invalid_argument("matrix cannot be inverted");
        }

        for (int i = 0; i < n; i++){
            if (abs(matrix[i][i])< 1e-9)
            throw invalid_argument("matrix cannot be inverted");

            T coeff = 1/matrix[i][i];

            for (int j = 0; j < 2*n; j++){
                matrix[i][j] *= coeff;
            }
        }
        
        for (int i = n - 1; i >= 0; i--) {
            for (int j = 0; j < i; j++) {
                T factor = matrix[j][i];
                for (int k = 0; k < 2 * n; k++) {
                    matrix[j][k] -= factor * matrix[i][k];
                }
            }
        }
    
        vector<vector<T>> inverseMatrix(n, vector<T>(n, 0));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                inverseMatrix[i][j] = matrix[i][j + n];
            }
        }
    
        return inverseMatrix;
    }
};

template <typename T>

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

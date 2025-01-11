#include <vector>
#include <iostream>
using namespace std;
template <typename T>

class MaximumSquareArea{
    public: 

    vector<vector<int>> maxSquareCoordinates(vector<vector<T>> matrix, T squareComponent){
        
        int row = matrix.size();
        int col = matrix[0].size();

        vector<vector<int>> coordinates(4, vector<int>(2));

        int maxLength = 0;

        vector<vector<int>> dp (matrix.size(), vector<int> (matrix[0].size(), 0));

        for (int i = 0; i < row; i++){
            if (matrix[i][0] == squareComponent){
                 dp[i][0] = 1;
                 maxLength = 1;
            }
           
        }

        for (int i = 0; i < col; i++){
           if (matrix[0][i] == squareComponent){
                 dp[0][i] = 1;
                  maxLength = 1;
            }
        }

        for (int i = 1; i < row; i++){
            for (int j = 1; j < col; j++){
                if (matrix[i][j] == squareComponent){
                    dp[i][j] = min (min (dp[i-1][j], dp[i][j-1]), dp[i-1][j-1])+1;
                    maxLength = max (maxLength, dp[i][j] );

                    if (maxLength == dp[i][j]){
                        coordinates[0] = {i-maxLength+1, j-maxLength};
                        coordinates[1] = {i-maxLength+1, j};
                        coordinates[2] = {i, j};
                        coordinates[3] = {i, j-maxLength+1};
                    }

                }
            }
        }
        return coordinates;
    }

    long maxSquare(vector<vector<T>> matrix, T squareComponent){
        int row = matrix.size();
        int col = matrix[0].size();


        int maxLength = 0;

        vector<vector<int>> dp (matrix.size(), vector<int> (matrix[0].size(), 0));

        for (int i = 0; i < row; i++){
            if (matrix[i][0] == squareComponent){
                 dp[i][0] = 1;
                 maxLength = 1;
            }
           
        }

        for (int i = 0; i < col; i++){
           if (matrix[0][i] == squareComponent){
                 dp[0][i] = 1;
                  maxLength = 1;
            }
        }

        for (int i = 1; i < row; i++){
            for (int j = 1; j < col; j++){
                if (matrix[i][j] == squareComponent){
                    dp[i][j] = min (min (dp[i-1][j], dp[i][j-1]), dp[i-1][j-1])+1;
                    maxLength = max (maxLength, dp[i][j] );

                }
            }
        }
        return maxLength*maxLength;
    }


};





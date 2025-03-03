#include <vector>
#include <string>
using namespace std;

class LevenshteinDistance{
    public:
        int minDistance(string word1, string word2) {
            int r = word1.size();
            int c = word2.size();
    
            vector<vector<int>> dp (r+1, vector<int> (c+1, 0));
    
            for (int i = 1; i <= r; i++){
                dp[i][0] = i;
            }
    
            for (int i = 1; i <= c; i++){
                dp[0][i] = i;
            }
    
            for (int i = 1; i <= r; i++){
                for (int j = 1; j <= c; j++){
                    int cost = word1[i-1] == word2[j-1] ? 0 :1;
                    dp[i][j] = min(dp[i-1][j-1]+cost, min(dp[i-1][j]+1, dp[i][j-1]+1));            
                }
            }
    
            return dp[r][c];
            
        }
    };
#include <vector>
#include <algorithm>

using namespace std;
template <typename T>

class LCS {
    public:
        vector<T> longestCommonSubsequence(vector<T> s1, vector<T> s2) {
            int r = s1.size();
            int c = s2.size();
            vector<vector<int>> dp (r+1, vector<int> (c+1, 0));
    
            for (int i = 1; i<= r; i++){
                for (int j = 1; j <= c; j++){
                    if (s1[i-1] == s2[j-1]){
                        dp[i][j] = dp[i-1][j-1]+1;
                    }else{
                        dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
                    }
                }
            }

            vector<T> lcs;

            while (r != 0 && c != 0){
                if (s1[r-1]== s2[c-1]){
                    lcs.push_back(s1[r-1]);
                        r--;
                        c--;
                }else if (dp[r - 1][c] > dp[r][c - 1]) {
                    r--;
                } else {
                    c--;
                }
            }

            reverse(lcs.begin(), lcs.end());

            return lcs;
        }
    };

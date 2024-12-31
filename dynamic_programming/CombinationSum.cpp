#include <vector>
using namespace std;


class CombinationsSum{
    public:

    long noOfCombinationSums(vector<int>& nums, int target){

        vector<long> dp (target+1);
        dp[0] = 1;
        
        for (int i = 1; i <= target; i++){
            for (int num: nums){
                if (i-num >= 0)
                dp[i] += dp[i-num];

        }
        }
        return dp[target];
        
    }
};
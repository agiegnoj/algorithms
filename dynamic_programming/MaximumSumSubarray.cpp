#include <vector>
#include <climits>

using namespace std;

class MaxSumSubarray{

    public:

    long MaximumSumSubarray(vector <int> nums){

    if (nums.size() == 0) return 0;
    
       long currentMax = INT_MIN;
       long globalMax = INT_MIN;

        for (int i = 0; i < nums.size(); i++){
            currentMax = max (currentMax+nums[i], (long)nums[i]);
            globalMax = max (currentMax, (long)globalMax);

        }       
        return globalMax;
    }
    };

    
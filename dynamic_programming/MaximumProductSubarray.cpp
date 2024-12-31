#include <vector>

using namespace std;

class MaxProductSubarray{
    
    public:
    long long maxProduct(vector <int> nums){

        if (nums.size() == 0) return 0;

        long long currentMax = nums[0];
        long long currentMin = nums[0];
        long long globalMax = nums[0];

        for (int num :nums){
            long long temp = max (max(currentMin * num, (long long )num), currentMax*num);
            currentMin = min(min(temp *num, (long long )num), currentMin*num);
            currentMax = temp;
            globalMax = max (currentMax, globalMax);
        }       
        return  globalMax;
    }
    
    };
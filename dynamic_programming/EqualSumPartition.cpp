#include <vector>
#include <set>
#include <numeric>
#include <map>

using namespace std;

class EqualSumPartition{
    public: 
    
    bool EqualSumPartitionPossible(vector<int> nums){
        long target =  accumulate(nums.begin(), nums.end(), 0L);

        if (target %2 == 1) return false;
        target /= 2;

        set<long> dp;

        for (int num : nums){
            set<long> tempSums(dp);

            for (long sum : tempSums){
                long temp = sum+num;
                if (temp == target)
                return true;

                if (temp < target)
                dp.insert(temp);
            }

        }

        return false;
        }
        
vector<vector<int>> getEqualSumPartition(vector<int> nums) {
            long target = accumulate(nums.begin(), nums.end(), 0L);

    if (target % 2 == 1) return {};
    target /= 2;

    set<long> dp;
    map<long, set<int>> sumToIndexMap;
    sumToIndexMap[0] = {}; 

    for (int i = 0; i < nums.size(); i++) {
        set<long> tempSums(dp);
        for (long sum : tempSums) {
            long temp = sum + nums[i];
            if (temp == target) {
                set<int> indices = sumToIndexMap[sum];
                indices.insert(i);
                return getResult(indices, nums);
            }

            if (temp < target) {
                set<int> indices = sumToIndexMap[sum];
                indices.insert(i);
                sumToIndexMap[temp] = indices;
                dp.insert(temp);
               
            }
        }
        dp.insert(nums[i]); 
    }

    return {}; 
}


private: 

vector<vector<int>> getResult(set<int>& indices, vector<int>& nums) {
    vector<int> subset1, subset2;

    for (int index : indices) {
        subset1.push_back(nums[index]);
    }

    for (int i = 0; i < nums.size(); i++) {
        if (indices.find(i) == indices.end()) {
            subset2.push_back(nums[i]);
        }
    }

    return {subset1, subset2};
}
};



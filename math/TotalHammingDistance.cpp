#include <vector>
using namespace std;

class TotalHammingDistance{
    public: 

    int getTotalHammingDistance(vector<int> nums){
        if (nums.size()< 2) return 0;
        vector<int> bitCount(32, 0);
        int totalNums = nums.size();
        int res = 0;

        for (int num : nums){
            for (int i = 0; i< 32; i++){
                bitCount[i] += num%2;
                num /= 2;
            }
        }

        for (int count : bitCount){
            res += (count*(totalNums-count));
        }

        return res;

    }

}; 
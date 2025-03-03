#include <vector>
#include <iostream>

using namespace std;

template <typename T>

class Kadane{
    public:

       T maxProductSubarray(vector <T> nums){

        static_assert(std::is_arithmetic<T>::value, "Type T must be arithmetic.");

        if (nums.size() == 0) return 0;

        T currentMax = nums[0];
        T currentMin = nums[0];
        T globalMax = nums[0];

        for (int i = 1; i < nums.size(); i++){
            T num = nums[i];
            T temp = max (max(currentMin * num, num), currentMax*num);
            currentMin = min(min(currentMax *num, num), currentMin*num);
            currentMax = temp;
            globalMax = max (currentMax, globalMax);
        }       
        return  globalMax;
    }

    

    T maxSumSubarray(vector <T> nums){

        static_assert(std::is_arithmetic<T>::value, "Type T must be arithmetic.");

        if (nums.size() == 0) return 0;
        
           T currentMax = nums[0];
           T globalMax = nums[0];
    
            for (int i = 1; i < nums.size(); i++){
                currentMax = max (currentMax+nums[i], nums[i]);
                globalMax = max (currentMax, globalMax);
    
            }       
            return globalMax;
    }


};








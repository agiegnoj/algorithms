#include <vector>
using namespace std;
template <typename T>

class Floyd{
    public: 

    bool hasCycle(vector<int>& successorGraph, int start){
        int slow = start;
        int fast = start;

        while (fast != -1 && successorGraph[fast] != -1 ){
            slow = successorGraph[slow];
            fast = successorGraph[successorGraph[fast]];

            if (slow == fast) return true;

        }

        return false;


    }

    int getCycleBeginning(vector<int>& successorGraph, int start){
        int slow = start;
        int fast = start;

        while (fast != -1 && successorGraph[fast] != -1 ){
            slow = successorGraph[slow];
            fast = successorGraph[successorGraph[fast]];

            if (slow == fast){
                fast = start;
                while (fast != slow){
                    fast = successorGraph[fast];
                    slow = successorGraph[slow];
                }

                return slow;
            } 
        }

        return -1;
    }
};

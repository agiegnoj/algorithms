#include <vector>
using namespace std;
template <typename T>

class Floyd{
    public: 

    bool hasCycle(vector<pair<int,T>>& successorGraph, int start){ //<pointer, data>
        int slow = start;
        int fast = start;

        while (fast != -1 && successorGraph[fast].first != -1 ){
            slow = successorGraph[slow].first;
            fast = successorGraph[successorGraph[fast].first].first;

            if (slow == fast) return true;

        }

        return false;


    }

    pair<int, T> getCycleBeginning(vector<pair<int,T>>& successorGraph, int start){
        int slow = start;
        int fast = start;

        while (fast != -1 && successorGraph[fast].first != -1){
            slow = successorGraph[slow].first;
            fast = successorGraph[successorGraph[fast].first].first;

            if (slow == fast){
                fast = start;
                while (fast != slow){
                    fast = successorGraph[fast].first;
                    slow = successorGraph[slow].first;
                }

                return successorGraph[slow];
            } 
        }

        return {-1, T()};
    }

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

#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <unordered_set>
#include <algorithm>
using namespace std;

class CycleDetectionDirectedGraph {
public:
    bool hasCycle(const vector<vector<int>>& graphAdjList) {
        unordered_set<int> visited;
        unordered_set<int> finished;

        for (int i = 0; i < graphAdjList.size(); i++) {
            if (!visited.count(i)) {
                if (dfsUtilOne(i, graphAdjList, visited, finished))
                    return true;
            }
        }
        return false;
    }

    set<vector<int>> getCycles(const vector<vector<int>>& graphAdjList) {
        
        unordered_set<int> visited;
        unordered_set<int> finished;
        set<vector<int>> cycles;

        for (int i = 0; i < graphAdjList.size(); i++) {
            if (!visited.count(i)) {
                map<int, int> childParent;
                childParent[i] = -1; 
                dfsUtilTwo(i, graphAdjList, childParent, visited, finished, cycles);
            }
        }
        return cycles;
    }

private:
    bool dfsUtilOne(int current, const vector<vector<int>>& graph, unordered_set<int>& visited, unordered_set<int>& finished) {
        if (visited.count(current)) {
            return !finished.count(current); 
        }

        visited.insert(current);
        for (int nextNode : graph[current]) {
            if (dfsUtilOne(nextNode, graph, visited, finished))
                return true;
        }
        visited.erase(current);
        finished.insert(current); 
        return false;
    }

     void dfsUtilTwo(int current, const vector<vector<int>>& graph, map<int, int>& childParent, unordered_set<int>& visited, unordered_set<int>& finished, set<vector<int>>& cycles) {
        visited.insert(current);
        for (int nextNode : graph[current]) {
            if (!visited.count(nextNode)) {
                childParent[nextNode] = current;
                dfsUtilTwo(nextNode, graph, childParent, visited, finished, cycles);
            } else if (!finished.count(nextNode)) {
                
                vector<int> cycle = backtrack(nextNode, current, childParent);
                if (!cycle.empty()) {
                    rotate(cycle.begin(), min_element(cycle.begin(), cycle.end()), cycle.end());
                    cycles.insert(cycle);
                }
            }
        }
        visited.erase(current);
        finished.insert(current);
    }

    vector<int> backtrack(int start, int current, map<int, int>& childParent) {
        vector<int> cycle;
        cycle.push_back(current);
        int node = childParent[current];

        while (node != start && node != -1) {
            cycle.push_back(node);
            node = childParent[node];
        }

        if (node == start) {
            cycle.push_back(start);
            reverse(cycle.begin(), cycle.end());
            return cycle;
        }

        return {};
    }
};





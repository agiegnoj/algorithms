#include <vector>
#include <unordered_set>
#include <map>
#include <set>
#include <iostream>
#include <algorithm>
using namespace std;

class CycleDetectionUndirectedGraph{
    public:
    bool hasCycle(vector<vector<int>> graphAdjList){
        unordered_set<int> visited;
        unordered_set<int> finished;

         for (int i = 0; i< graphAdjList.size(); i++){
           int src = i;
           if (dfsUtilOne(src, -1, graphAdjList, visited, finished))
           return true;
           
    }

    return false;
    
    }

    set<vector<int>> getCycles(vector<vector<int>> graphAdjList){
        unordered_set<int> visited;
        unordered_set<int> finished;
        map<int,int> childParent;
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

    vector<int> getLargestCycle(vector<vector<int>> graph){
        set<vector<int>> cycles = getCycles(graph);
        if (cycles.size() == 0) return {};
        vector<int> maxCycle = {};
        for (vector<int> cycle : cycles){
            if (cycle.size() > maxCycle.size())
            maxCycle = cycle;
        }
        return maxCycle;
    }

    private: 

    bool dfsUtilOne(int current, int parent, const vector<vector<int>>& graph, unordered_set<int>& visited, unordered_set<int>& finished ){
        if (visited.count(current))
        return !finished.count(current);

        visited.insert(current);

        for (int nextVertex : graph[current]){
            if (nextVertex != parent){
                if (dfsUtilOne(nextVertex, current, graph, visited, finished))
                return true;
            }
        }

        finished.insert(current);

        return false;
        
    }

    void dfsUtilTwo(int current,  const vector<vector<int>>& graph, map<int, int>& childParent, unordered_set<int>& visited, unordered_set<int>& finished , set<vector<int>>& cycles){
        if (visited.count(current) && !finished.count(current) ){
            backtrack(graph, current, childParent, cycles);
            return;
        }
        
        visited.insert(current);

        for (int nextVertex : graph[current]){
             if (nextVertex != childParent[current]){ 
                childParent[nextVertex] = current;
                dfsUtilTwo(nextVertex, graph, childParent, visited, finished, cycles);
            }
        }

        finished.insert(current);
        
    }

    void backtrack(const vector<vector<int>>& graph, int first, map<int, int>& childParent, set<vector<int>>& cycles){
        
        vector<int> cycle;
        int current = childParent[first];

        while (current != first){
            cycle.push_back(current);
            current = childParent[current];
        }

        cycle.push_back(first);

        rotate(cycle.begin(), min_element(cycle.begin(), cycle.end()), cycle.end());

        cycles.insert(cycle);

    }
};









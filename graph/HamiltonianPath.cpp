#include<vector>
#include <iostream>
using namespace std;

class HamiltonianPath{
    public: 
    vector<int> getHamiltonianPath(vector<vector<int>>& graph){
        
        int n = graph.size();

        for (int vertex = 0; vertex < n;  vertex++){
            vector<bool> visited(n);
            vector<int> path;
            if (dfs(vertex, visited, graph, path, n)){
                return path;
            }             
        }
        return {};
    }

    private:

    bool dfs(int current, vector<bool>& visited, vector<vector<int>>& graph, vector<int>& path, int count){
        visited[current] = true;
        path.push_back(current);
        count--;

        if (count == 0)
        return true;

        for (int v : graph[current]){
            if (!visited[v]){
                if (dfs(v, visited, graph, path, count))
                return true;
            }
        }
        visited[current] = false;
        path.pop_back();
        return false;
    }
};










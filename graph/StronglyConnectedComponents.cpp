#include <vector>
#include <stack>

using namespace std;

class StronglyConnectedComponents{
    public:
    vector<vector<int>> SCCs(vector<vector<int>>& directedGraph){
        vector<vector<int>> SCCs;
        vector<vector<int>> tranposed = transpose(directedGraph);
        vector<bool> visited (directedGraph.size());
        stack <int> s;

        for (int vertex = 0; vertex< directedGraph.size(); vertex++){
            if (!visited[vertex]){
                dfsStack(directedGraph, vertex, s, visited);
            }
        }

        vector<bool> visitedTwo (directedGraph.size());

        while (!s.empty()){
            int vertex = s.top();
            s.pop();
            if (!visitedTwo[vertex]){
                vector<int> temp;
                dfsTransposed(tranposed, vertex,  temp, visitedTwo);
                SCCs.push_back(temp);
            }  
        }
        return SCCs;
    }

    private: 

    void dfsStack(vector<vector<int>>& graph, int curr, stack<int>& s, vector<bool>& visited){
          
        visited[curr] = true;

        for (int next : graph[curr]){
            if (!visited[next])
            dfsStack(graph, next,  s, visited);
        }

        s.push(curr);

    }

    void dfsTransposed(vector<vector<int>>& graph, int curr, vector<int>& temp, vector<bool>& visited){

            temp.push_back(curr);
            visited[curr] = true;

            for (int next : graph[curr]){
                if (!visited[next])
                dfsTransposed(graph, next, temp, visited);
            }

        }

    vector<vector<int>> transpose(vector<vector<int>>& graph){
        vector<vector<int>> t(graph.size());

        for(int i = 0; i < graph.size(); i++){
            for (int vertex : graph[i]){
                t[vertex].push_back(i);            
            }
        }
        return t;
    }
};


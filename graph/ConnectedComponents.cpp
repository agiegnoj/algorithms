#include <queue>
#include <vector>

using namespace std;

class ConnectedComponents{

    public:
    vector<vector<int>> CCs(vector<vector<int>>& graph){
        vector<vector<int>> CCs;
        vector<bool> visited(graph.size());

        for (int vertex = 0; vertex< graph.size(); vertex++){
            if (!visited[vertex]){
                vector<int> cc;
                bfs(graph, vertex, visited, cc);
                CCs.push_back(cc);
            }
        }
        return CCs;
    }

    private:
    void bfs(vector<vector<int>>& graph, int curr,vector<bool>& visited, vector <int>& cc){
        
        queue<int> q;
        q.emplace(curr);
        visited[curr] = true;

        while(!q.empty()){
            int v = q.front();
            q.pop();
            cc.push_back(v);
            for (int next : graph[v]){
                if (!visited[next]){
                    visited[next] = true;
                    q.emplace(next);
                }
            }
        }

    }
};


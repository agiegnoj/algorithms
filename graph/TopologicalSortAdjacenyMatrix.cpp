#include <queue>
#include <vector>
using namespace std;


class TopologicalSortAdjacenyMatrix{
    public:

    vector<int> sortedGraph(vector<vector<int>> graph){
        if (graph.empty() || graph.size() != graph[0].size() )
        return {};

        vector<int> inDegree(graph.size(), 0);
        vector<int> sortedGraph;
        vector<vector<int>> adjList(graph.size());

        for (int i = 0; i < graph.size(); i++ ) {
            for (int j = 0; j < graph.size(); j++){
                if (graph[i][j] != 0){
                inDegree[j]++;
                adjList[i].push_back(j);
                }
                
            }
        }

        queue<int> zeroEdgeNodes;

        for (int i = 0; i< inDegree.size(); i++){
            if (inDegree[i] == 0){
                zeroEdgeNodes.push(i);
            }
        }

        while (!zeroEdgeNodes.empty()){
            int node = zeroEdgeNodes.front();
            sortedGraph.push_back(node);
            zeroEdgeNodes.pop();
            
            for (int neighbor : adjList[node]){
                inDegree[neighbor]--;
                if (inDegree[neighbor] == 0){
                    zeroEdgeNodes.push(neighbor);
                }
            }
        }

        if (sortedGraph.size() != graph.size())
        return {};

        return sortedGraph;

    }

  
};
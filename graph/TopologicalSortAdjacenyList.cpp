#include <vector>
#include <queue>

using namespace std;

class TopologicalSortAdjacencyList{

    public:

    vector<int> sortedGraph(vector<vector<int>> graph){
    int numberOfNodes = graph.size();
    vector<int> sortedGraph;
    vector<int> inDegree (numberOfNodes, 0);

    for (int i = 0 ;i< numberOfNodes; i++){
        for (int j = 0; j< graph[i].size(); j++){
            inDegree[graph[i][j]]++;
        }
    }

    queue<int> zeroEdgeNodes;

    for (int i = 0; i< numberOfNodes; i++){
        if (inDegree[i] == 0){
            zeroEdgeNodes.push(i);
        }
    }

    while (!zeroEdgeNodes.empty()){
        int n = zeroEdgeNodes.front();
        zeroEdgeNodes.pop();
        sortedGraph.push_back(n);

        for (int i = 0; i < graph[n].size(); i++){
            int neighbor = graph[n][i];
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0){
                zeroEdgeNodes.push(neighbor);
            }
        }
 
    }

    if (sortedGraph.size() != numberOfNodes)
    return {};

    return sortedGraph;

}

};


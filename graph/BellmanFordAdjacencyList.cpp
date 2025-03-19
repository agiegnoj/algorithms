#include <vector>
#include <map>
#include <algorithm>
#include <limits>
using namespace std;

template <typename T>

class BellmanFordAdjacencyList{
    public: 
    map<int, int> prev;
    vector<T> distances;

    void shortestPath(int start, const vector<vector<pair<int, T>>>& graph) {
        int n = graph.size();
        distances.assign(n, numeric_limits<T>::max());
        distances[start] = 0;

        for (int j = 1; j < n; j++){
            for (int i = 0; i< graph.size(); i++){
                for(pair <int, T> neighbor : graph[i]){
                    if (distances[i] == numeric_limits<T>::max()) continue;
                    if (neighbor.first < 0 || neighbor.first >= n) continue;
                    
                    T distance = distances[i] + neighbor.second;
                    if (distances[neighbor.first] > distance){
                        distances[neighbor.first] = distance;
                        prev[neighbor.first] = i;
                    }
                }
            }
        }  
    }

    vector<int> getShortestPath(int start, int end, const vector<vector<pair<int, T>>>& graph) {
        shortestPath(start, graph);
        if (distances[end] == numeric_limits<T>::max()) return {}; 

        vector<int> res;
        for (int at = end; at != start; at = prev[at]) {
            if (prev.find(at) == prev.end()) return {};
            res.push_back(at);
        }
        res.push_back(start);
        std::reverse(res.begin(), res.end()); 
        return res;
    }

    T getShortestPathLength(int start, int end, const vector<vector<pair<int, T>>>& graph) {
        shortestPath(start, graph);
        return distances[end];
    }  

    bool hasNegativeCycle(int start, vector<vector<pair<int, T>>>& graph){
        shortestPath(start, graph);

            for (int i = 0; i< graph.size(); i++){
                for(pair <int, T> neighbor : graph[i]){
                    if (distances[i] == numeric_limits<T>::max()) continue;
                    if (neighbor.first < 0 || neighbor.first >= graph.size()) continue;
                    T distance = distances[i] + neighbor.second;
                    if (distances[neighbor.first] > distance){
                        return true;
                    }
                }
            }
            return false;
        }
};


#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <limits>
#include <algorithm>

using namespace std;
template<typename T>

class DijkstraAdjacencyList {
public:
    vector<T> distances;
    map<int, int> prev;

    void shortestPath(int start, const vector<vector<pair<int, T>>>& graph) {
        int n = graph.size();
        distances.assign(n, numeric_limits<T>::max());
        vector<bool> finished(n, false);
        
        auto compare = [&](int a, int b) { return distances[a] > distances[b]; };
        priority_queue<int, vector<int>, decltype(compare)> pq(compare);
        
        distances[start] = 0;
        pq.emplace(start);

        while (!pq.empty()) {
            int v = pq.top();
            pq.pop();

            if (finished[v]) continue;
            finished[v] = true;

            for (pair<int, int> p : graph[v]) {
                int neighbor = p.first;
                T weight = p.second;
                
                if (neighbor < 0 || neighbor >= n) continue;
                
                T newDist = distances[v] + weight;
                if (newDist < distances[neighbor]) {
                    distances[neighbor] = newDist;
                    pq.emplace(neighbor);
                    prev[neighbor] = v;
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
};





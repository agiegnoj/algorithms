#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;
template<typename T>

class MinSpanningTree{
    public:

    vector<vector<int>> mst(const vector<vector<T>>& undirectedGraph){
        int size = undirectedGraph.size();       
        vector<int> root(size);

        for (int i = 0; i < size; i++){
            root[i] = i;
        }

        auto compare = [&](pair<int, pair<int,int>> p1, pair<int,pair<int, int>> p2) {
            return p1.first < p2.first;
        };

        vector<pair<int, pair<int, int>>> edges;

        for (int i = 0; i< size; i++){
            for (int j = i+1; j< size; j++){
                if (undirectedGraph[i][j] != 0)
                edges.push_back({undirectedGraph[i][j],{i,j}});
            }
        }

        sort(edges.begin(), edges.end(), compare);

        vector<vector<int>> mst (size, vector<int> (size));
        int target = undirectedGraph.size()-1;
        int edgeCount = 0;

        for (auto edge : edges ){
            if (unionIfDifferent(edge.second.first, edge.second.second, root)){
                edgeCount++;
                mst[edge.second.first][ edge.second.second] = edge.first;
                mst[edge.second.second][ edge.second.first] = edge.first;
                if (edgeCount == target) break;
            }
        }

        return mst;
    }

    private:

    bool unionIfDifferent(int node1, int node2, vector<int>& root) {
        int root1 = find(node1, root);
        int root2 = find(node2, root);

        if (root1 == root2) return false;
        root[root1] = root2;

        return true;
    }

    int find(int node, vector<int>& root){
        if (root[node] != node){
            root[node] = find(root[node], root);
        }
        return root[node];
    }
};


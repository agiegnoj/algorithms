#include <vector>
#include <set>
#include <queue>
using namespace std;

class BipartiteGraphTest{
    public:
      bool isBipartite(vector<vector<int>> graphAdjList){
        int s = graphAdjList.size();
        vector<int> color (s, -1);

        for (int i = 0; i< s; i++){
            if (color[i] == -1){
                if (!bfs(i, graphAdjList, color))
                return false;
            }
        }
       return true;
      }

      private:

      bool bfs(int currentNode, vector<vector<int>>& graph, vector<int>& color){
        queue<int> q;
        q.push(currentNode);
        color[currentNode] = 0;

        while (!q.empty()){
            int current = q.front();
            q.pop();
            int currentColor  =  1- color[current] ;

            for (int n : graph[current]){          
                if (color[n] == -1){
                    q.push(n); 
                    color[n] = currentColor; 
                }else if (color[n] != currentColor){
                    return false; 
                }           
            }                    
        }
        return true;
    }
};





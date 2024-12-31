#include <vector>
#include <climits>
#include <cmath>
#include <queue>
#include <iostream>
using namespace std;

template <typename T>

class ShortestPathInMazeAStar{
    public:
    
    vector<vector<T>> maze;
    T blockingObject;
    vector<pair<int, int>> shortestPath;
    int destinationX;
    int destinationY;

    ShortestPathInMazeAStar(vector<vector<T>> m, T obj, int startX, int destX, int startY, int destY)
    : maze(m), blockingObject(obj), destinationX(destX), destinationY(destY){
      

        aStar(startX, startY);
    }

    vector<pair<int, int>> getShortestPath(){
        return shortestPath;
    }

    long getShortestPathLength(){
        return shortestPath.empty() ? -1 : shortestPath.size();
    }

    private:
    
    struct ComparePath {
        int destinationX, destinationY;
        
        ComparePath(int destX, int destY) : destinationX(destX), destinationY(destY) {}

        bool operator()(const vector<pair<int, int>>& path1, const vector<pair<int, int>>& path2) {
           
            int cost1 = path1.size()-1;
            int cost2 = path2.size()-1;
            
            long dist1 = abs(destinationX - path1.back().first) + abs(destinationY - path1.back().second);
            long dist2 = abs(destinationX - path2.back().first) + abs(destinationY - path2.back().second);
            
            return (cost1+dist1) > (cost2+dist2);  
        }
    };



    void aStar(int startX, int startY){
      
        priority_queue<vector<pair<int, int>>, vector<vector<pair<int, int>>>, ComparePath> paths(ComparePath(destinationX, destinationY));
        vector<vector<long>> memoization(maze.size(), vector<long>(maze[0].size(), LONG_MAX));
        vector<pair<int, int>> path;
        path.push_back(make_pair(startX, startY));
        paths.push(path);


        while (!paths.empty()){
            vector<pair<int, int>> toCheck = paths.top();
            paths.pop();

            int cX = toCheck.back().first;
            int cY = toCheck.back().second;

            long steps = toCheck.size();

            if (cX == destinationX && cY == destinationY){
                shortestPath = toCheck;
                return;
            }

            if (cX < 0 || cX >= maze.size() 
             || cY < 0 || cY >= maze[0].size()
             || maze[cX][cY] == blockingObject)
                continue;

            if (memoization[cX][cY] <= steps )
                continue;

            memoization[cX][cY] = steps;

            vector<pair<int, int>> newCoordinates = 
            {
                {cX+1, cY}, {cX-1, cY},{cX, cY+1}, {cX, cY-1}
            };

            for (int i = 0; i< 4; i++){
                int x = newCoordinates[i].first;
                int y = newCoordinates[i].second;

                vector<pair<int, int>> newPath = toCheck; 
                newPath.push_back(make_pair(x, y));
                paths.push(newPath);
            }
        }
    }
};


int main() {
    // Test case 1
    vector<vector<int>> maze = {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };

    int blockingObject = 1; // 1 represents a blocking object (obstacle)
    int startX = 0, startY = 0;
    int destX = 4, destY = 4;

    // Create an instance of the ShortestPathInMazeBFS class
    ShortestPathInMazeAStar<int> solver(maze, blockingObject, startX, destX, startY, destY);

    // Get the shortest path
    vector<pair<int, int>> path = solver.getShortestPath();
    long pathLength = solver.getShortestPathLength();

    // Output the result
    cout << "Shortest Path Length: " << pathLength << endl;
    if (pathLength != -1) {
        cout << "Path: ";
        for (auto& p : path) {
            cout << "(" << p.first << "," << p.second << ") ";
        }
        cout << endl;
    } else {
        cout << "No path found." << endl;
    }

    return 0;
}
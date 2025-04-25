#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class GraphIsomorphism{

    public:
    vector<int> getIsomorphism(vector<vector<int>>& graphOne, vector<vector<int>>& graphTwo, bool undirected){
        if (graphOne.size() != graphTwo.size()) return {};
        int s = graphOne.size();
        vector<vector<int>> candidates(s);
        setCandidates(candidates,graphOne, graphTwo);
        vector<int>indices; 
        for (int i = 0; i < s; i++){
            indices.push_back(i);
            if (candidates[i].empty())return{};
        }

        auto compare = [&](int a, int b) { return candidates[a].size() < candidates[b].size(); };

        sort(indices.begin(), indices.end(), compare);

        vector<vector<int>> permutations;
        vector<int> perm(s);
        vector<bool> used(s);

        validPermutations(permutations, perm, candidates, 0, used, indices);

        for(vector<int> perm : permutations){
            if (isIsomorphism(perm, graphOne, graphTwo, undirected))
            return perm;
        }

        return {};       
    }

    bool isomorphic(vector<vector<int>>& graphOne, vector<vector<int>>& graphTwo, bool undirected){
        return !getIsomorphism(graphOne, graphTwo, undirected).empty();
    }

    private: 

    bool isIsomorphism(vector<int>& bijection, vector<vector<int>>& graphOne, vector<vector<int>>& graphTwo, bool undirected){
        int s = graphOne.size();
        for (int i = 0; i < s; i++){
            for (int j = 0; j < s; j++){
                if (undirected) {
                    if (graphOne[i][j] != graphTwo[bijection[i]][bijection[j]] &&
                        graphOne[i][j] != graphTwo[bijection[j]][bijection[i]])
                        return false;
                } else {
                    if (graphOne[i][j] != graphTwo[bijection[i]][bijection[j]])
                        return false;
                }
            }
        }
        return true; 
    }

    void validPermutations(vector<vector<int>>& permutations, vector<int>& currentPerm, vector<vector<int>>& candidates, int currentIndex, vector<bool>& used, vector<int>& indices){
        if (currentIndex == currentPerm.size()){
            permutations.push_back(currentPerm);
            return;
        }
        
        for (int n : candidates[indices[currentIndex]]){
            if (!used[n]){
                currentPerm[indices[currentIndex]] = n;
                used[n] = true;
                validPermutations(permutations, currentPerm, candidates, currentIndex+1, used, indices);
                used[n] = false;
            }
        }
    }

    void setCandidates(vector<vector<int>>& candidates, vector<vector<int>>& graphOne, vector<vector<int>>& graphTwo ){
        int s = graphOne.size();
        vector<int> inDegreeOne(s), inDegreeTwo(s), outDegreeOne(s), outDegreeTwo(s);
        vector<vector<int>>  neighborsOne(s), neighborsTwo(s);

        for (int i = 0; i< s; i++){
            for (int j = 0; j < s; j++){
                if (graphOne[i][j] != 0){
                    outDegreeOne[i]++;
                    inDegreeOne[j]++;
                    neighborsOne[i].push_back(j);
                }

                if (graphTwo[i][j] != 0){
                    outDegreeTwo[i]++;
                    inDegreeTwo[j]++;
                    neighborsTwo[i].push_back(j);
                }
            }
        }

        for (int i = 0; i< s; i++){
            for (int j = 0; j < s; j++){
               if (inDegreeOne[i] == inDegreeTwo[j] && outDegreeOne[i] == outDegreeTwo[j]){
                if (invariantNeighbors(neighborsOne, neighborsTwo, 
                    inDegreeOne, inDegreeTwo, outDegreeOne, outDegreeTwo, i, j))
                    candidates[i].push_back(j);            
               }
            }
        }
    }

        bool invariantNeighbors(vector<vector<int>>&  neighborsOne, vector<vector<int>>&  neighborsTwo,
        vector<int>& inDegreeOne, vector<int>& inDegreeTwo, vector<int>& outDegreeOne, vector<int>& outDegreeTwo,
        int firstNode, int secondNode){
            
            for (int n : neighborsOne[firstNode]){
                bool invariant = false;
                for (int n2 : neighborsTwo[secondNode]){
                    if (inDegreeOne[n] == inDegreeTwo[n2] &&  outDegreeOne[n] == outDegreeTwo[n2]){
                        for (int n3 : neighborsOne[n]){
                            bool invariant2 = false;
                            for (int n4 : neighborsTwo[n2]){
                                if (inDegreeOne[n3] == inDegreeTwo[n4] &&  outDegreeOne[n3] == outDegreeTwo[n4]){
                                    
                                    invariant2 = true;
                                    break;
                                }          
                            }
                            if (!invariant2) return false;
                        }
                        invariant = true;
                        break;
                    }          
                }
                if (!invariant) return false;
            }

            return true;
        }
    };

    

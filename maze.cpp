#include <iostream>
#include <random>
#include <ctime>
#include <vector>
#include <cmath>

using namespace std;

void BFS(const vector<vector<int>>& mazeAdj, vector<bool>& visited, vector<int>& parent, vector<vector<int>>& availableNodes);
vector<int> findPath(vector<int>& parent, int end, int start);

int main(){

    //                               1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16
    vector<vector<int>> mazeAdj = { {0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                    {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                                    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                    {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0},
                                    {0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                                    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0}
                            };
    
    int size = mazeAdj.size();

    vector<bool> visited(size, false); //set size of visited to amnt nodes, set all unvisited
    vector<int> parent(size, -1);
    vector<vector<int>> availableNodes(size);

    int start = sqrt(size) - 1;
    int end = size - start;

    availableNodes[0].push_back(start);
    BFS(mazeAdj, visited, parent, availableNodes);
    vector<int> path = findPath(parent, end, start);
    
    for(int i : path){
        cout << " " << i;
    }
    
    return 0;
}

void BFS(const vector<vector<int>>& mazeAdj, vector<bool>& visited, vector<int>& parent, vector<vector<int>>& availableNodes){
    int unvisited = 0;
    visited[availableNodes[0][0]] = true; //set starting node as visited

    //loop through every node
    for(int i = 0; i < mazeAdj.size(); i++){
        if(availableNodes.empty()){
            break;
        }

        //check all avaiable neighbors
        while(!availableNodes.empty()){
            unvisited = availableNodes[i][0]; //set unvisited to next unvisited node
            availableNodes[i].erase(availableNodes[i].begin()); //erase node due to visitation

            
            //add neighbor to available nodes, mark visited, set parent
            for(int j = 0; j < mazeAdj.size(); j++){
                
                //if is neighbor and if not visited
                if(mazeAdj[unvisited][j] == 1 && visited[j] == false){
                    visited[j] = true;
                    availableNodes[i+1].push_back(j);
                    parent[j] = unvisited;
                }
            }
        }
    }
}

vector<int> findPath(vector<int>& parent, int end, int start){
    int currNode = end;
    vector<int> path;

    while(parent[currNode] != -1){
        path.insert(path.begin(), currNode);
        
        if(currNode == start) return path;

        currNode = parent[currNode];
    }

    return {-1};
}
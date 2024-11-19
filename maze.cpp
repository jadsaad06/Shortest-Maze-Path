#include <iostream>
#include <random>
#include <ctime>
#include <vector>
#include <cmath>

using namespace std;

void BFS(const vector<vector<int>>& mazeAdj, vector<bool>& visited, vector<int>& parent, vector<int>& availableNodes);
vector<int> findPath(vector<int>& parent, int end, int start);
vector<vector<int>> genMaze();

int main(){
    srand(time(0));
    int counter = 0;
    
    for(int i = 0; i < 1000; i++){
        vector<vector<int>> mazeAdj = genMaze();    
        size_t size = mazeAdj.size();

        vector<bool> visited(size, false); //set size of visited to amnt nodes, set all unvisited
        vector<int> parent(size, -1);
        vector<int> availableNodes(size);

        int start = sqrt(size) - 1;
        int end = size - start;

        availableNodes.push_back(start);
        BFS(mazeAdj, visited, parent, availableNodes);
        vector<int> path = findPath(parent, end, start);

        if(path[0] != -1){
            counter++;
        }
    }
        
    cout << counter;
    
    return 0;
}

void BFS(const vector<vector<int>>& mazeAdj, vector<bool>& visited, vector<int>& parent, vector<int>& availableNodes) {
    int unvisited = 0;
    visited[availableNodes[0]] = true; // set starting node as visited

    while (!availableNodes.empty()) {
        unvisited = availableNodes[0]; // set unvisited to next unvisited node
        availableNodes.erase(availableNodes.begin()); // erase node due to visitation

        for (size_t j = 0; j < mazeAdj.size(); j++) {
            // if is neighbor and if not visited
            if (mazeAdj[unvisited][j] == 1 && !visited[j]) {
                visited[j] = true;
                availableNodes.push_back(j);
                parent[j] = unvisited;
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

vector<vector<int>> genMaze() {
    vector<vector<int>> maze(25, vector<int>(25, 0));

    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 25; j++) {
            if (i != j) { // Skip self-loop

                if (i / 5 == j / 5 && abs(i - j) == 1) { //horizontal adjacent
                    int random = rand() % 2;
                    maze[i][j] = random;
                    maze[j][i] = random;
                }
                else if (abs(i - j) == 5) { //vertical adjacent
                    int random = rand() % 2;
                    maze[i][j] = random;
                    maze[j][i] = random;
                }
            }
        }
    }

    return maze;
}

//
// Created by mihan on 25.09.2021.
//

#include <queue>

#ifndef LABA_1_GRAPH_MATRIX_H
#define LABA_1_GRAPH_MATRIX_H

#endif //LABA_1_GRAPH_MATRIX_H

const int MAX_VERTICES = 100;

class GraphMatrix {
    int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES];
    int vertices;
    bool oriented = false;
public:
    explicit GraphMatrix(int vert_count, bool oriented = false) {
        for (int i = 0; i < vertices; i++) {
            for(int j = 0; j < vertices; j++) {
                adjacencyMatrix[i][j] = 0;
            }
        }
    }

    int getEdge (int v1, int v2) {
        return adjacencyMatrix[v1][v2];
    }

    void printGraph () {
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                std::cout<<adjacencyMatrix[i][j]<<"  ";
            }
            std::cout<<"\n";
        }
    }

    void addEdge (int v1, int v2, int weight = 1) {
        adjacencyMatrix[v1][v2] = weight;
        if (!oriented) {
            adjacencyMatrix[v2][v1] = weight;
        }
    }

    void deleteEdge (int v1, int v2) {
        adjacencyMatrix[v1][v2] = 0;
        if (!oriented)
            adjacencyMatrix[v2][v1] = 0;
    }

    void BFS(int source) {
        std::vector <bool> visited;
        visited[source] = true;
        std::queue<int> q;
        q.push(source);
        while (!q.empty()) {
            source = q.front()+1;
            q.pop();
            for (int i = 0; i < vertices; i++) {
                if (!visited[i]) {
                    visited[i] = true;
                    q.push(i);
                }
            }
            std::cout << source <<" ";
        }
    }

    void DFS (int st, bool *visited)
    {
        int r;
        std::cout<<st+1<<" ";
        visited[st] = true;
        for (r=0; r<vertices; r++)
            if ((adjacencyMatrix[st][r]!=0) && (!visited[r]))
                DFS(r, visited);
    }

    bool isConnected () {
        int source = 0;
        bool visited[vertices];
        for (int i=0; i<vertices; i++)
            visited[i] = false;

        DFS(source, visited);

        for (int i=1; i<vertices; i++)
            if (!visited[i])
                return false;
        return true;
    }

    void PrimAlgorithm (int u) {
        std::vector<bool> visited;
        int tree[vertices][vertices];
        for (int i=0; i<vertices; i++)
            for (int j=0; j<vertices; j++)
                tree[i][j] = 0;
        int edges = 0;
        visited[u] = true;
        short int x, y;
        while (edges < vertices - 1) {
            int min = INT_MAX;
            x = 0;
            y = 0;

            for (short int i = 0; i < vertices; i++) {
                if (visited[i]) {
                    for (short int j = 0; j < vertices; j++) {
                        if (!visited[j] && adjacencyMatrix[i][j] > 0) {
                            if (min > adjacencyMatrix[i][j]) {
                                min = adjacencyMatrix[i][j];
                                x = i;
                                y = j;
                            }
                        }
                    }
                }
            }
            tree[x][y] = adjacencyMatrix[x][y];
            tree[y][x] = adjacencyMatrix[y][x];
            visited[y] = true;
            edges++;
        }
        for (auto &i : tree) {
            visited.push_back(false);
            for (int j : i)
                std::cout << " " << j;
            std::cout << '\n';
        }
    }
};
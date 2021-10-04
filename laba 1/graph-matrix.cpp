#ifndef LABA_1_GRAPH_MATRIX_CPP
#define LABA_1_GRAPH_MATRIX_CPP

#include "graph-matrix.h"

#include <iostream>
#include <vector>

template<typename Edge, typename Vertice>
Edge GraphMatrix<Edge, Vertice>::getEdge (Vertice v1, Vertice v2) {
    return adjacencyMatrix[v1][v2];
}

template<typename Edge, typename Vertice>
void GraphMatrix<Edge, Vertice>::printGraph () {
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            std::cout<<adjacencyMatrix[i][j]<<"  ";
        }
        std::cout<<"\n";
    }
}

template<typename Edge, typename Vertice>
void GraphMatrix<Edge, Vertice>::addEdge (Vertice v1, Vertice v2, Edge weight) {
    adjacencyMatrix[v1][v2] = weight;
    if (!oriented) {
        adjacencyMatrix[v2][v1] = weight;
    }
}

template<typename Edge, typename Vertice>
void GraphMatrix<Edge, Vertice>::deleteEdge (Vertice v1, Vertice v2) {
    adjacencyMatrix[v1][v2] = 0;
    if (!oriented)
        adjacencyMatrix[v2][v1] = 0;
}

template<typename Edge, typename Vertice>
void GraphMatrix<Edge, Vertice>::BFS(Vertice source) {
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

template<typename Edge, typename Vertice>
void GraphMatrix<Edge, Vertice>::DFS (Vertice st, bool *visited)
{
    int r;
    std::cout<<st+1<<" ";
    visited[st] = true;
    for (r=0; r<vertices; r++)
        if ((adjacencyMatrix[st][r]!=0) && (!visited[r]))
            DFS(r, visited);
}

template<typename Edge, typename Vertice>
bool GraphMatrix<Edge, Vertice>::isConnected () {
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

template<typename Edge, typename Vertice>
std::vector<Vertice> GraphMatrix<Edge, Vertice>::Dijkstra (Vertice start, Vertice finish, int N) {
    int dist[vertices];

    bool sptSet[vertices];

    // Parent array to store
    // shortest path tree
    std::vector<Vertice> path;
    path.resize(vertices);

    // Initialize all distances as
    // INFINITE and stpSet[] as false
    for (int i = 0; i < vertices; i++)
    {
        path[0] = -1;
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    dist[start] = 0;

    for (int count = 0; count < vertices - 1; count++) {
        int u = minDistance(dist, sptSet);

        sptSet[u] = true;

        for (int v = 0; v < vertices; v++)

            if (!sptSet[v] && adjacencyMatrix[u][v] &&
                dist[u] + adjacencyMatrix[u][v] < dist[v])
            {
                path[v] = u;
                dist[v] = dist[u] + adjacencyMatrix[u][v];
            }
    }
    return path;
}

template<typename Edge, typename Vertice>
void GraphMatrix<Edge, Vertice>::PrimAlgorithm (Vertice u) {
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


#endif //LABA_1_GRAPH_MATRIX_CPP
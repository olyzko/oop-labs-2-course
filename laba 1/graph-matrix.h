//
// Created by mihan on 25.09.2021.
//

#include <queue>
#include <iostream>

#ifndef LABA_1_GRAPH_MATRIX_H
#define LABA_1_GRAPH_MATRIX_H

#endif //LABA_1_GRAPH_MATRIX_H

const int MAX_VERTICES = 100;

template<typename Edge, typename Vertice>
class GraphMatrix {
    Vertice adjacencyMatrix[MAX_VERTICES][MAX_VERTICES];
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

    Edge getEdge (Vertice v1, Vertice v2);

    void printGraph ();

    void addEdge (Vertice v1, Vertice v2, Edge weight);

    void deleteEdge (Vertice v1, Vertice v2);

    void BFS(Vertice source);

    void DFS (Vertice st, bool *visited);

    bool isConnected ();

    void PrimAlgorithm (Vertice u);
};

#include "graph.h"
#include <queue>
#include <iostream>

#ifndef LABA_1_GRAPH_MATRIX_H
#define LABA_1_GRAPH_MATRIX_H


template<typename Edge, typename Vertice>
class GraphMatrix : public Graph<Edge, Vertice> {
private:
    std::vector<GraphVertice<Vertice> *> nodes;
    std::vector<std::vector<std::pair<bool, GraphEdge<Edge> *>>> edges;
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

    std::vector<Vertice> Dijkstra (Vertice start, Vertice finish, int N);

    void PrimAlgorithm (Vertice u);
};

#endif //LABA_1_GRAPH_MATRIX_H
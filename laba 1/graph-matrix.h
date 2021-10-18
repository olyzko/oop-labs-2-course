
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
    int vertices{};
public:
    bool oriented;
    explicit GraphMatrix(bool Oriented);

    ~GraphMatrix();

    void printGraph () override;

    void addEdge (int v1, int v2, Edge weight) override;

    void deleteEdge (int v1, int v2) override;

    void addVertice(Vertice data) override;

    bool deleteVertice(int num) override;

    void BFS(int source)override;

    void DFS (int st, bool *visited) override;

    bool isConnected () override;

    Edge min_distance(int v1, int v2) override;

    //void PrimAlgorithm (int u) override;
};

#endif //LABA_1_GRAPH_MATRIX_H
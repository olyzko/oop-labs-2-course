
#include "graph.h"
#include <vector>
#include <iostream>
#include <algorithm>

#ifndef LABA_1_GRAPH_STRUCT_H
#define LABA_1_GRAPH_STRUCT_H

template<typename Edge, typename Vertice>
class GraphStructVertice : public GraphVertice<Vertice> {
public:
    std::vector<std::pair<int, GraphEdge<Edge> *>> adjacent_nodes;

    explicit GraphStructVertice(Vertice Data) {
        this->data = Data;
    }
};

template<typename Edge, typename Vertice>
class GraphStruct : public Graph<Edge, Vertice>{                                                   //weighted non-oriented graph
private:
    std::vector<GraphStructVertice<Edge, Vertice> *> adjacencyList;
    unsigned short int vertices{};
    bool oriented = false;
public:
    explicit GraphStruct (int n) {
        vertices = n;
        adjacencyList.resize(n);
    }

    ~GraphStruct() { for (auto &node:adjacencyList) delete node; }

    GraphStruct () = default;

    void printGraph () override;

    void addEdge (int v1, int v2, Edge weight) override;

    void deleteEdge (int v1, int v2) override;

    void addVertice () override;

    void deleteVertice (int num) override;

    bool isConnected () override;

    void DFS (int source, bool *visited) override;

    void BFS(int source) override;

    std::vector<Vertice> Dijkstra (int start, int finish, int N)override;

    void PrimAlgorithm (int u) override;
};

#include "graph-struct.cpp"
#endif //LABA_1_GRAPH_STRUCT_H
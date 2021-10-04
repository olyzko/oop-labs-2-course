//
// Created by mihan on 25.09.2021.
//

#include <vector>
#include <iostream>
#include <algorithm>

#ifndef LABA_1_GRAPH_STRUCT_H
#define LABA_1_GRAPH_STRUCT_H


template<typename Edge, typename Vertice>
class GraphStruct {                                                   //weighted non-oriented graph
    std::vector<std::vector<std::pair<int, Edge>>> adjacencyList;
    unsigned short int vertices{};
    bool oriented = false;
public:
    explicit GraphStruct (int n) {
        vertices = n;
        adjacencyList.resize(n);
    }

    GraphStruct () = default;

    void printGraph ();

    void addEdge (Vertice v1, Vertice v2, Edge weight);

    void deleteEdge (Vertice v1, Vertice v2);

    void addVertice ();

    void deleteVertice (Vertice num);

    bool isConnected ();

    void DFS (Vertice source, bool *visited);

    void BFS(int source);

    std::vector<Vertice> Dijkstra (Vertice start, Vertice finish, int N);

    void PrimAlgorithm (Vertice u);
};

#include "graph-struct.cpp"
#endif //LABA_1_GRAPH_STRUCT_H
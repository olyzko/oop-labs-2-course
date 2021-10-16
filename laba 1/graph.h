
#ifndef LABA_1_GRAPH_H
#define LABA_1_GRAPH_H

#include <vector>

template<typename Edge, typename Vertice>
class Graph {
public:
    virtual void printGraph () = 0;

    virtual void addEdge (int v1, int v2, Edge weight) = 0;

    virtual void deleteEdge (int v1, int v2) = 0;

    virtual void addVertice () = 0;

    virtual void deleteVertice (int num) = 0;

    virtual bool isConnected () = 0;

    virtual void DFS (int source, bool *visited) = 0;

    virtual void BFS(int source) = 0;

    virtual std::vector<Vertice> Dijkstra (int start, int finish, int N) = 0;

    virtual void PrimAlgorithm (int u) = 0;
};

template<typename Vertice>
class GraphVertice {
public:
    Vertice data;
    GraphVertice() = default;
    explicit GraphVertice(const Vertice c_data){
        data = c_data;
    }
};

template<typename Edge>
class GraphEdge {
public:
    Edge data;
    GraphEdge() = default;
    explicit GraphEdge(const Edge c_data){
        data = c_data;
    }
};

#endif //LABA_1_GRAPH_H

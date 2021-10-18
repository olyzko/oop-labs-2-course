
#ifndef LABA_1_GRAPH_H
#define LABA_1_GRAPH_H

#include <string>
#include <vector>
#include "datatime.h"

template<typename Edge, typename Vertice>
class Graph {
public:
    virtual void printGraph () = 0;

    virtual void addEdge (int v1, int v2, Edge weight) = 0;

    virtual void deleteEdge (int v1, int v2) = 0;

    virtual void addVertice (Vertice data) = 0;

    virtual bool deleteVertice (int num) = 0;

    virtual bool isConnected () = 0;

    virtual void DFS (int source, bool *visited) = 0;

    virtual void BFS(int source) = 0;

    virtual Edge min_distance(int v1, int v2) = 0;

   // virtual void PrimAlgorithm (int u) = 0;
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

template<typename T>
struct inf;

template<>
struct inf<int> {
    static constexpr int value = INT_MAX;
};

template<>
struct inf<double> {
    static constexpr double value = INT_MAX;
};

template<>
struct inf<std::string> {
    const std::string value = {CHAR_MAX};
};

template<typename T>
struct inf<std::vector<T>> {
    static constexpr std::vector<T> value = {inf<T>::value};
};

template<>
struct inf<DataTime> {
    const DataTime value = {INT_MAX, SHRT_MAX, SHRT_MAX, SHRT_MAX, SHRT_MAX, SHRT_MAX};
};

template<typename T>
struct null;

template<>
struct null<int> {
    static constexpr int value = 0;
};

template<>
struct null<double> {
    static constexpr double value = 0;
};

template<>
struct null<std::string> {
    const std::string value = "";
};

template<typename T>
struct null<std::vector<T>> {
    static constexpr std::vector<T> value = {};
};

template<>
struct null<DataTime> {
    const DataTime value = {0, 0, 0, 0, 0, 0};
};


#endif //LABA_1_GRAPH_H

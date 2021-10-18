#include <iostream>
#include <vector>
#include "graph.h"
#include "graph-struct.h"
#include "graph-matrix.h"
#include "datatime.h"

template<typename T>
bool operator<(std::vector<T> &vec1, std::vector<T> &vec2) {
    int i = 0;
    while (vec1[i] == vec2[i]) {
        i++;
    }
    return vec1[i] < vec2[i];
}

template<typename T>
bool operator>(std::vector<T> &vec1, std::vector<T> &vec2) {
    return vec2 < vec1;
}

template<typename T>
bool operator<=(std::vector<T> &vec1, std::vector<T> &vec2) {
    return !(vec1 > vec2);
}

template<typename T>
bool operator>=(std::vector<T> &vec1, std::vector<T> &vec2) {
    return !(vec1 < vec2);
}

template<typename T>
bool operator==(std::vector<T> &vec1, std::vector<T> &vec2) {
    return !(vec1 < vec2) && !(vec1 > vec2);
}

template<typename T>
bool operator!=(std::vector<T> &vec1, std::vector<T> &vec2) {
    return !(vec1 == vec2);
}

template<typename T>
std::vector<T> operator+(std::vector<T> &vec1, std::vector<T> &vec2) {
    std::vector<T> res;
    int size = (vec1.size() < vec2.size()) ? vec2.size() : vec1.size();
    res.reserve(size);
    for (int i = 0; i < size; i++) {
        res.emplace_back(vec1[i] + vec2[i]);
    }
    return res;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, std::vector<T> &vec) {
    for (auto &e:vec) {
        os << e << ' ';
    }
    os << std::endl;
    return os;
}

int main() {
    GraphStruct<DataTime, std::string> graph(5);
    DataTime d1 = {0, 0, 0, 5, 45, 0};
    DataTime d2 = {0, 0, 0, 3, 10, 0};
    DataTime d3 = {0, 0, 0, 4, 40, 0};
    DataTime d4 = {0, 0, 0, 1, 20, 0};
    DataTime d5 = {0, 0, 0, 2, 5, 0};
    DataTime d6 = {0, 0, 0, 5, 30, 0};
    graph.addVertice("Kyiv");
    graph.addVertice("Kharkiv");
    graph.addVertice("Lviv");
    graph.addVertice("Odesa");
    graph.addVertice("Dnipro");
    graph.addVertice("Poltava");
    graph.addEdge(0, 2, d1);
    graph.addEdge(0, 5, d2);
    graph.addEdge(0, 3, d3);
    graph.addEdge(1, 5, d4);
    graph.addEdge(1, 4, d5);
    graph.addEdge(0, 4, d6);

    DataTime way = graph.min_distance(2, 4);
    std::cout<<way<<std::endl;

    graph.printGraph();

    //graph.deleteEdge(0, 2);
    //graph.deleteVertice(3);

    graph.printGraph();

    system("pause");
    return 0;
}

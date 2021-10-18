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
    //graph.addEdge("thtf", "ihdvjk", 4);
    DataTime d1 = {0, 0, 0, 5, 45, 0};
    graph.addEdge(0, 2, d1);
    /*graph.addEdge(0, 3, 6);
    graph.addEdge(1, 2, 2);
    graph.addEdge(1, 4, 4);
    graph.addEdge(2, 3, 5);*/

    graph.printGraph();

    //graph.deleteEdge(0, 2);
    //graph.deleteVertice(3);

    graph.printGraph();

    system("pause");
    return 0;
}

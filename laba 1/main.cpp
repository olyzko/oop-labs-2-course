#include <iostream>
#include <vector>
#include <algorithm>
#include "graph-struct.h"
#include "graph-matrix.h"


int main() {
    GraphStruct graph(5);
    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 3);
    graph.addEdge(0, 3, 6);
    graph.addEdge(1, 2, 2);
    graph.addEdge(1, 4, 4);
    graph.addEdge(2, 3, 5);

    graph.printGraph();

    graph.deleteEdge(0, 2);
    graph.deleteVertice(3);

    graph.printGraph();

    system("pause");
    return 0;
}

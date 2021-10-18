#ifndef LABA_1_GRAPH_STRUCT_CPP
#define LABA_1_GRAPH_STRUCT_CPP

#include "graph-struct.h"
#include "graph.h"
#include "datatime.h"

#include <iostream>
#include <vector>
#include <list>

template<typename Edge, typename Vertice>
void GraphStruct<Edge, Vertice>::printGraph () {
    for (int i=0; i<vertices; i++) {
        std::cout << "Adjacency list of vertex " << i << "\n";
        for (int j=0; j<adjacencyList.size(); j++)
            std::cout << adjacencyList[i]->adjacent_nodes[j].first <<" "<< adjacencyList[i]->adjacent_nodes[j].second << "\n";
        std::cout << "\n";
    }
}

template<typename Edge, typename Vertice>
void GraphStruct<Edge, Vertice>::addEdge (int v1, int v2, Edge data) {
    auto edge = new GraphEdge<Edge>(data);
    adjacencyList[v1]->adjacent_nodes.emplace_back(v2, edge);
    if (!oriented && v1 != v2)
        adjacencyList[v2]->adjacent_nodes.emplace_back(v1, edge);

}

template<typename Edge, typename Vertice>
void GraphStruct<Edge, Vertice>::deleteEdge (int v1, int v2) {
    for (int i=0; i<adjacencyList[v1]->adjacent_nodes.size(); i++) {
        if (adjacencyList[v1]->adjacent_nodes[i].first == v2) {
            adjacencyList.erase(adjacencyList.begin() + i);
            break;
        }
    }
    if (!oriented)
        for (int i=0; i<adjacencyList[v1]->adjacent_nodes.size(); i++) {
            if (adjacencyList[v2]->adjacent_nodes[i].first == v1) {
                adjacencyList.erase(adjacencyList.begin() + i);
                break;
            }
        }
}

template<typename Edge, typename Vertice>
void GraphStruct<Edge, Vertice>::addVertice (Vertice data) {
    vertices++;
    adjacencyList.push_back(new GraphStructVertice<Edge, Vertice>(data));
}

template<typename Edge, typename Vertice>
bool GraphStruct<Edge, Vertice>::deleteVertice (int num) {
    if (num >= adjacencyList.size()) return false;

    int i = 0;
    for (auto &e:adjacencyList) {
        while (i < e->adjacent_nodes.size()) {
            if (e->adjacent_nodes[i].first == num) {
                delete e->adjacent_nodes[i].second;
                e->adjacent_nodes.erase(e->adjacent_nodes.begin() + i);
            } else {
                if (e->adjacent_nodes[i].first > num) e->adjacent_nodes[i].first--;
                i++;
            }
        }
        i = 0;
    }
    for (auto &e:adjacencyList[num]->adjacent_nodes) {
        delete e.second;
    }
    adjacencyList.erase(adjacencyList.begin() + num);
    return true;
}

template<typename Edge, typename Vertice>
bool GraphStruct<Edge, Vertice>::isConnected () {
    int source = 0;
    bool visited[vertices];
    for (int i=0; i<vertices; i++)
        visited[i] = false;

    DFS(source, visited);

    for (int i=1; i<vertices; i++)
        if (!visited[i])
            return false;
    return true;
}

template<typename Edge, typename Vertice>
void GraphStruct<Edge, Vertice>::DFS (int source, bool *visited) {
    visited[source] = true;
    std::cout << source << " ";
    for (int i=0; i<vertices; ++i)
        if (!visited[i])
            DFS(i, visited);
}

template<typename Edge, typename Vertice>
void GraphStruct<Edge, Vertice>::BFS(int source) {
    bool *visited = new bool[vertices];
    for(int i = 0; i < vertices; i++)
        visited[i] = false;

    std::list<int> queue;
    std::vector<int> int_vertices;
    for(int i = 0; i < vertices; i++)
        int_vertices.push_back(i);

    visited[source] = true;
    queue.push_back(source);

    typename std::vector<int>::iterator i;

    while(!queue.empty()) {
        source = queue.front();
        std::cout << source << " ";
        queue.pop_front();

        for (i = int_vertices.begin(); i != int_vertices.end(); ++i) {
            if (!visited[*i]) {
                visited[*i] = true;
                queue.push_back(*i);
            }
        }
    }
}

template<typename Edge, typename Vertice>
Edge GraphStruct<Edge, Vertice>::min_distance(int v1, int v2) {
    if (!(v1 < adjacencyList.size() && v2 < adjacencyList.size())) return null<Edge>::value;
    std::vector<std::vector<Edge>> dist;
    std::vector<Edge> tmp;

    Edge m_null = null<Edge>::value;

    for (auto &e:adjacencyList) {
        tmp.push_back(m_null);
    }

    for (auto &e:adjacencyList) {
        dist.push_back(tmp);
    }

    for (unsigned int i = 0; i < adjacencyList.size(); i++) {
        for (auto &e:adjacencyList[i]->adjacent_nodes) {
            dist[i][e.first] = e.second->data;
        }
    }

    for (unsigned int i = 0; i < adjacencyList.size(); i++) {
        for (unsigned int j = 0; j < adjacencyList.size(); j++) {
            if ((i != j) && (dist[i][j] == m_null)) dist[i][j] = inf<Edge>::value;
            if (i == j) dist[i][j] = m_null;
        }
    }

    for (unsigned int k = 0; k < adjacencyList.size(); k++) {
        for (unsigned int i = 0; i < adjacencyList.size(); i++) {
            for (unsigned int j = 0; j < adjacencyList.size(); j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    return dist[v1][v2];
}


/*template<typename Edge, typename Vertice>
void GraphStruct<Edge, Vertice>::PrimAlgorithm (int u) {
    std::priority_queue< std::pair<int, Edge>, std::vector <std::pair<int, Edge>> , std::greater<std::pair<int, Edge>> > pq;
    int src = 0;

    std::vector<int> key(vertices, INT_MAX);
    std::vector<int> parent(vertices, -1);
    std::vector<bool> inMST(vertices, false);

    std::list<std::pair<int, Edge>> int_vertices;
    for(int i = 0; i < vertices; i++)
        for (int j = 0; j < adjacencyList[i]->adjacent_nodes.size(); j++)
             int_vertices.push_back(std::make_pair(i, adjacencyList[i]->adjacent_nodes[j].second));

    pq.push(std::make_pair(0, src));
    key[src] = 0;
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        if(inMST[u]){
            continue;
        }
        inMST[u] = true;  // Include vertex in MST
        typename std::list< std::pair<int, Edge> >::iterator i;
        for (i = int_vertices.begin(); i != int_vertices.end(); ++i) {
            int v = (*i).first;
            Edge weight = (*i).second;

            if (!inMST[v] && key[v] > weight) {
                // Updating key of v
                key[v] = weight;
                pq.push(std::make_pair(key[v], v));
                parent[v] = u;
            }
        }
    }

    for (int i = 1; i < vertices; ++i)
        printf("%d - %d\n", parent[i], i);

}*/

#endif //LABA_1_GRAPH_STRUCT_CPP
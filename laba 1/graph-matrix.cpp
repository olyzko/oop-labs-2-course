#ifndef LABA_1_GRAPH_MATRIX_CPP
#define LABA_1_GRAPH_MATRIX_CPP

#include "graph-matrix.h"

#include <iostream>
#include <vector>

template<typename Edge, typename Vertice>
void GraphMatrix<Edge, Vertice>::printGraph () {
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            std::cout<<edges[i][j].second<<"  ";
        }
        std::cout<<"\n";
    }
}

template<typename Edge, typename Vertice>
void GraphMatrix<Edge, Vertice>::addEdge (int v1, int v2, Edge weight) {
    edges[v1][v2].second = weight;
    if (!oriented) {
        edges[v2][v1].second = weight;
    }
}

template<typename Edge, typename Vertice>
void GraphMatrix<Edge, Vertice>::deleteEdge (int v1, int v2) {
    edges[v1][v2].second = 0;
    if (!oriented)
        edges[v2][v1].second = 0;
}

template<typename Edge, typename Vertice>
void GraphMatrix<Edge, Vertice>::addVertice(Vertice data) {
    static const std::pair<bool, GraphEdge<Edge> *> temp = {false, nullptr};
    static const std::vector<std::pair<bool, GraphEdge<Edge> *>> temp_vec = {temp};
    nodes.push_back(new GraphMatrix<Edge, Vertice>(data));
    if (edges.empty()) {
        edges.emplace_back(temp_vec);
    } else {
        edges.emplace_back();
        for (unsigned int i = 0; i < edges.size(); i++) {
            edges[i].emplace_back(temp);
            edges[edges.size() - 1].emplace_back(temp);
        }
    }
}

template<typename Edge, typename Vertice>
bool GraphMatrix<Edge, Vertice>::deleteVertice(int num) {
    if (num >= nodes.size()) return false;

    int i = 0;
    for (auto &e:edges) {
        delete e[num].second;
        e.erase(e.begin() + num);
    }
    for (auto &e:edges[num]) {
        delete e.second;
    }
    edges.erase(edges.begin() + num);
    nodes.erase(nodes.begin() + num);
    return true;
}

template<typename Edge, typename Vertice>
void GraphMatrix<Edge, Vertice>::BFS(int source) {
    std::vector <bool> visited;
    visited[source] = true;
    std::queue<int> q;
    q.push(source);
    while (!q.empty()) {
        source = q.front()+1;
        q.pop();
        for (int i = 0; i < vertices; i++) {
            if (!visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
        std::cout << source <<" ";
    }
}

template<typename Edge, typename Vertice>
void GraphMatrix<Edge, Vertice>::DFS (int st, bool *visited)
{
    int r;
    std::cout<<st+1<<" ";
    visited[st] = true;
    for (r=0; r<vertices; r++)
        if ((edges[st][r].first) && (!visited[r]))
            DFS(r, visited);
}

template<typename Edge, typename Vertice>
bool GraphMatrix<Edge, Vertice>::isConnected () {
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
Edge GraphMatrix<Edge, Vertice>::min_distance(int v1, int v2) {
    if (!(v1 < nodes.size() && v2 < nodes.size())) return -1;
    std::vector<std::vector<Edge>> dist;
    std::vector<Edge> tmp;

    Edge m_null = null<Edge>::value;

    for (auto &e:nodes) {
        tmp.push_back(m_null);
    }

    for (auto &e:nodes) {
        dist.push_back(tmp);
    }

    for (unsigned int i = 0; i < nodes.size(); i++) {
        for (unsigned int j = 0; j < nodes.size(); j++) {
            if (i == j) dist[i][j] = m_null;
            else if (edges[i][j].first) dist[i][j] = edges[i][j].second->data;
            else dist[i][j] = inf<Edge>::value;
        }
    }

    for (unsigned int k = 0; k < nodes.size(); k++) {
        for (unsigned int i = 0; i < nodes.size(); i++) {
            for (unsigned int j = 0; j < nodes.size(); j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    return dist[v1][v2];
}
/*
template<typename Edge, typename Vertice>
void GraphMatrix<Edge, Vertice>::PrimAlgorithm (int u) {
    std::vector<bool> visited;
    int tree[vertices][vertices];
    for (int i=0; i<vertices; i++)
        for (int j=0; j<vertices; j++)
            tree[i][j] = 0;
    int edges_num = 0;
    visited[u] = true;
    short int x, y;
    while (edges < vertices - 1) {
        int min = INT_MAX;
        x = 0;
        y = 0;

        for (short int i = 0; i < vertices; i++) {
            if (visited[i]) {
                for (short int j = 0; j < vertices; j++) {
                    if (!visited[j] && edges[i][j].first) {
                        if (min > edges[i][j].second) {
                            min = edges[i][j];
                            x = i;
                            y = j;
                        }
                    }
                }
            }
        }
        tree[x][y] = edges[x][y];
        tree[y][x] = edges[y][x];
        visited[y] = true;
        edges++;
    }
    for (auto &i : tree) {
        visited.push_back(false);
        for (int j : i)
            std::cout << " " << j;
        std::cout << '\n';
    }
}*/


#endif //LABA_1_GRAPH_MATRIX_CPP
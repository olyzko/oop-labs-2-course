//
// Created by mihan on 25.09.2021.
//

#ifndef LABA_1_GRAPH_STRUCT_H
#define LABA_1_GRAPH_STRUCT_H

#endif //LABA_1_GRAPH_STRUCT_H

class GraphStruct {                                                   //weighted non-oriented graph
    std::vector<std::vector<std::pair<int, int>>> adjacencyList;
    unsigned short int vertices{};
    bool oriented = false;
public:
    explicit GraphStruct (int n) {
        vertices = n;
        adjacencyList.resize(n);
    }

    GraphStruct () = default;

    void printGraph () {
        for (int i=0; i<vertices; i++) {
            std::cout << "Adjacency list of vertex of vertex " << i << std::endl;
            for (int j=0; j<adjacencyList[i].size(); j++)
                std::cout << adjacencyList[i][j].first <<" "<< adjacencyList[i][j].second << "\n";
            std::cout << std::endl;
        }
    }

    void addEdge (int v1, int v2, int weight) {
        bool already_in_graph = false;
        for (int edge = 0; edge < adjacencyList[v1].size(); edge++) {
            if (adjacencyList[v1][edge].first == v2) {
                already_in_graph = true;
                adjacencyList[v1][edge].second = weight;
                if (!oriented)
                    for (int i = 0; i < adjacencyList[v2].size(); i++)
                        if (adjacencyList[v2][i].first == v1)
                            adjacencyList[v2][i].second = weight;
            }
        }
        if (!already_in_graph) {
            adjacencyList[v1].push_back(std::make_pair(v2, weight));
            if (!oriented)
                adjacencyList[v2].push_back(std::make_pair(v1, weight));
        }
    }

    void deleteEdge (int v1, int v2) {
        for (int i=0; i<adjacencyList[v1].size(); i++) {
            if (adjacencyList[v1][i].first == v2) {
                adjacencyList[v1].erase(adjacencyList[v1].begin() + i);
                break;
            }
        }
        if (!oriented)
            for (int i=0; i<adjacencyList[v2].size(); i++) {
                if (adjacencyList[v2][i].first == v1) {
                    adjacencyList[v2].erase(adjacencyList[v2].begin() + i);
                    break;
                }
            }
    }

    void addVertice () {
        vertices++;
        adjacencyList.resize(vertices);
    }

    void deleteVertice (int num) {
        for (int i=0; i<adjacencyList[num].size(); i++)
            deleteEdge(num, i);
        adjacencyList.erase(adjacencyList.begin() + num);
        vertices--;
    }



    bool isConnected () {
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

    void DFS (int source, bool *visited) {
        visited[source] = true;
        for (int i=0; i<vertices; ++i)
            if (!visited[i])
                DFS(i, visited);
    }

    std::vector<int> Dijkstra (int start, int finish, int N) {
        std::vector<int> d (N, INT_MAX),  p (N);
        d[start] = 0;
        std::vector<char> u (N);
        for (int i=0; i<N; ++i) {
            int v = -1;
            for (int j=0; j<N; ++j)
                if (!u[j] && (v == -1 || d[j] < d[v]))
                    v = j;
            if (d[v] == INT_MAX)
                break;
            u[v] = true;

            for (size_t j=0; j<adjacencyList[v].size(); ++j) {
                int to = adjacencyList[v][j].first,
                        len = adjacencyList[v][j].second;
                if (d[v] + len < d[to]) {
                    d[to] = d[v] + len;
                    p[to] = v;
                }
            }
        }
        std::vector<int> path;
        path.push_back (finish);
        for (int v=finish; v!=start;) {v=p[v];
            path.push_back (v);}
        std::reverse (path.begin(), path.end());
        path.push_back(d[finish]);

        return path;
    }
};


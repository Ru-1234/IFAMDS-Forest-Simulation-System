
#ifndef GRAPH_H
#define GRAPH_H

#include "data.h"
#include <iostream>
using namespace std;

class Graph {
private:
    int adjMatrix[10][10];
    int size;

public:
    Graph(int n);

    void addEdge(int u, int v);
    void showMatrix();

    void bfs(int start);
    void dfs(int start, bool visited[]);
    void startDFS(int start);
};

#endif
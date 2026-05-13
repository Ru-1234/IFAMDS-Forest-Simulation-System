#ifndef GRAPH_H
#define GRAPH_H

#include "data.h"
#include <iostream>
using namespace std;

// G1: Adjacency List node - stores destination + nexr node addr
struct AdjNode {
    int dest;
    AdjNode* next;

    AdjNode(int d) { dest = d; next = NULL;}
};

// G1: Adjacency List Graph - used when each zone has few nearby connections
class GraphList {
    private:
        AdjNode* adjList[10];
        int size;

    public:
        GraphList(int n);

        void addEdge(int u, int v);
        void display();

        void bfs(int start);
        void dfs(int start, bool visited[]);
        void startDFS(int start);

        int pathCost(int u, int v, int distance, int danger);       // Path Cost = Distance + Danger
        void updateFireCost(int u, int v, int distance, float fireLevel);   // Updated Cost = distanc * (1 + FireLevel)
};

// G2: Adjacency Matrix Graph - used when every zone checked against all others
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

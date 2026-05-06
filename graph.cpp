
#include "graph.h"

Graph::Graph(int n) {
    size = n;

    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
            adjMatrix[i][j] = 0;
}

void Graph::addEdge(int u, int v) {
    adjMatrix[u][v] = 1;
    adjMatrix[v][u] = 1;

    cout << "G: Edge Added (" << u << " - " << v << ")" << endl;
}

void Graph::showMatrix() {
    cout << "G: Graph Matrix" << endl;

    for(int i=0;i<size;i++) {
        for(int j=0;j<size;j++) {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

void Graph::bfs(int start) {
    int queue[10], front=0, rear=0;
    bool visited[10] = {false};

    queue[rear++] = start;
    visited[start] = true;

    cout << "G BFS: ";

    while(front < rear) {
        int node = queue[front++];
        cout << node << " ";

        for(int i=0;i<size;i++) {
            if(adjMatrix[node][i] == 1 && !visited[i]) {
                queue[rear++] = i;
                visited[i] = true;
            }
        }
    }
    cout << endl;
}

void Graph::dfs(int start, bool visited[]) {
    visited[start] = true;
    cout << start << " ";

    for(int i=0;i<size;i++) {
        if(adjMatrix[start][i] == 1 && !visited[i]) {
            dfs(i, visited);
        }
    }
}

void Graph::startDFS(int start) {
    bool visited[10] = {false};
    cout << "G DFS: ";
    dfs(start, visited);
    cout << endl;
}
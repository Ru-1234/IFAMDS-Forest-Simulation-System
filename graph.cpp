#include "graph.h"

//G1: ADJACENCY LIST GRAPH, time complexity: O(V)
GraphList::GraphList(int n) {
    size = n;
    for(int i=0;i<size;i++)
        adjList[i] = NULL;
}

// Time Complexity: O(1)
void GraphList::addEdge(int u, int v) {
    AdjNode* nn1 = new AdjNode(v);
    nn1->next = adjList[u];
    adjList[u] = nn1;

    AdjNode* nn2 = new AdjNode(u);
    nn2->next = adjList[v];
    adjList[v] = nn2;

    cout << "G1: Edge Added (" << u << " - " << v << ")" << endl;
}

// Time Complexity: O(V + E)
void GraphList::display() {
    cout << "G1: Adjacency List" << endl;

    for(int i=0;i<size;i++) {
        cout << i << " -> ";
        AdjNode* temp = adjList[i];
        while(temp != NULL) {
            cout << temp->dest << " ";
            temp = temp->next;
        }
        cout << endl;
    }
}

// BFS: check all nearby zones step by step - shows fire spread level by level
// Time Complexity: O(V + E)
void GraphList::bfs(int start) {
    int queue[10], front=0, rear=0;
    bool visited[10] = {false};

    queue[rear++] = start;
    visited[start] = true;

    cout << "G1 BFS: ";

    while(front < rear) {
        int node = queue[front++];
        cout << node << " ";

        AdjNode* temp = adjList[node];
        while(temp != NULL) {
            if(!visited[temp->dest]) {
                queue[rear++] = temp->dest;
                visited[temp->dest] = true;
            }
            temp = temp->next;
        }
    }
    cout << endl;
}

// DFS: follow one path deeply before trying others
// Time Complexity: O(V + E)
void GraphList::dfs(int start, bool visited[]) {
    visited[start] = true;
    cout << start << " ";

    AdjNode* temp = adjList[start];
    while(temp != NULL) {
        if(!visited[temp->dest])
            dfs(temp->dest, visited);
        temp = temp->next;
    }
}

// Time Complexity: O(V + E)
void GraphList::startDFS(int start) {
    bool visited[10] = {false};
    cout << "G1 DFS: ";
    dfs(start, visited);
    cout << endl;
}

// Time Complexity: O(1), Path Cost = Distance + Danger
int GraphList::pathCost(int u, int v, int distance, int danger) {
    int cost = distance + danger;
    cout << "G1: Path (" << u << "->" << v << ") Cost=" << cost << endl;
    return cost;
}

// fire-aware path, e.g.,  Updated Cost = Distance * (1 + FireLevel), if cost > 1.5x distance, route is blocked
// Time Complexity: O(1)
void GraphList::updateFireCost(int u, int v, int distance, float fireLevel) {
    float updatedCost = distance * (1.0f + fireLevel);
    cout << "G1: Fire Path (" << u << "->" << v << ") Updated Cost=" << updatedCost << endl;

    if(updatedCost > distance * 1.5)
        cout << "G1: Route (" << u << "->" << v << ") BLOCKED by fire!" << endl;
}


// G2: ADJACENCY MATRIX GRAPH 
// O(V^2)
Graph::Graph(int n) {
    size = n;

    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
            adjMatrix[i][j] = 0;
}

// Time Complexity: O(1)
void Graph::addEdge(int u, int v) {
    adjMatrix[u][v] = 1;
    adjMatrix[v][u] = 1;

    cout << "G: Edge Added (" << u << " - " << v << ")" << endl;
}

// Time Complexity: O(V^2)
void Graph::showMatrix() {
    cout << "G: Graph Matrix" << endl;

    for(int i=0;i<size;i++) {
        for(int j=0;j<size;j++) {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

// BFS from matrix - fire spread level by level
// Time Complexity: O(V^2)
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

// DFS from matrix - deep path analysis
// Time Complexity: O(V^2)
void Graph::dfs(int start, bool visited[]) {
    visited[start] = true;
    cout << start << " ";

    for(int i=0;i<size;i++) {
        if(adjMatrix[start][i] == 1 && !visited[i]) {
            dfs(i, visited);
        }
    }
}

// Time Complexity: O(V^2)
void Graph::startDFS(int start) {
    bool visited[10] = {false};
    cout << "G DFS: ";
    dfs(start, visited);
    cout << endl;
}

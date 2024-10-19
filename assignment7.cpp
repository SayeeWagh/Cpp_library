#include<iostream>
using namespace std;

const int V = 5;
const int MAX_EDGES = V * (V - 1) / 2;


struct Edge {
    int src, dest, weight;
};

int find(int parent[], int i) {
    if (parent[i] != i)
        parent[i] = find(parent, parent[i]);
    return parent[i];
}

void Union(int parent[], int rank[], int x, int y) {
    int xroot = find(parent, x);
    int yroot = find(parent, y);

    if (rank[xroot] < rank[yroot]) {
        parent[xroot] = yroot;
    } else if (rank[xroot] > rank[yroot]) {
        parent[yroot] = xroot;
    } else {
        parent[yroot] = xroot;
        rank[xroot]++;
    }
}

void sortEdges(Edge edges[], int E) {
    for (int i = 0; i < E - 1; i++) {
        for (int j = 0; j < E - i - 1; j++) {
            if (edges[j].weight > edges[j + 1].weight) {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
}

void kruskalMST(Edge edges[], int E) {
    Edge result[V - 1];
    int parent[V], rank[V];

    for (int v = 0; v < V; v++) {
        parent[v] = v;
        rank[v] = 0;
    }

    sortEdges(edges, E);

    int e = 0;
    for (int i = 0; e < V - 1 && i < E; i++) {
        int x = find(parent, edges[i].src);
        int y = find(parent, edges[i].dest);

        if (x != y) {
            result[e++] = edges[i];
            Union(parent, rank, x, y);
        }
    }

    cout << "\nMinimum Spanning Tree (Kruskal):\nEdge \tWeight\n";
    for (int i = 0; i < e; i++) {
        cout << result[i].src << " - " << result[i].dest << "\t" << result[i].weight << "\n";
    }
}

int minKey(int key[], bool inMST[]) {
    int min = 999999;
    int min_index;
    for (int v = 0; v < V; v++) {
        if (!inMST[v] && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

void primMST(int graph[V][V]) {
    int parent[V], key[V];
    bool inMST[V] = {false};
    for (int i = 0; i < V; i++) {
        key[i] = 999999;
        parent[i] = -1;
    }
    key[0] = 0;
    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, inMST);
        inMST[u] = true;
        for (int v = 0; v < V; v++) {
            if (graph[u][v] && !inMST[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }
    cout << "Minimum Spanning Tree (Prim):\nEdge \tWeight\n";
    for (int i = 1; i < V; i++) {
        cout << parent[i] << " - " << i << "\t" << graph[i][parent[i]] << "\n";
    }
}

void inputGraph(int graph[V][V], Edge edges[], int &E) {
    cout << "Enter the (5,5) adjacency matrix (0 for no connection): \n";
    E = 0;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            cin >> graph[i][j];
            if (graph[i][j] != 0 && i < j) {
                edges[E++] = {i, j, graph[i][j]};
            }
        }
    }
}

int main() {
    int graph[V][V];
    Edge edges[MAX_EDGES];
    int E;

    inputGraph(graph, edges, E);

    cout << "\nRunning Prim's Algorithm...";
    primMST(graph);

    cout << "\nRunning Kruskal's Algorithm...";
    kruskalMST(edges, E);

    return 0;
}


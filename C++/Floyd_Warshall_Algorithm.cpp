// Floyd-Warshall Algorithm

// It is a Dynamic Programming Based Algorithm

// It is used to find the shortest path between all the pairs of vertices in a weighted graph
// It works for both directed and undirected graphs, and it can handle negative edge weights as long as there are no negative weight cycles in the graph.

// Time Complexity: O(V^3), where V is the number of vertices in the graph

#include <iostream>
#include <vector>

using namespace std;

class Graph{
    int V; // Number of vertices
    vector<vector<pair<int, int>>> adj; // Adjacency list representation of the graph

    public:
    Graph(int V){
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v, int w){
        adj[u].push_back({v, w});
    }

    void floydWarshall(int src){
        vector<vector<int>> dist(V, vector<int>(V, INT_MAX));
        dist[src][src] = 0;

        // mark 0 dist for itself
        for(int i = 0; i < V; i++){
            dist[i][i] = 0;
        }

        // Mark the direct edges distances
        for(int u = 0; u < V; u++){
            for(auto edge : adj[u]){
                int v = edge.first;
                int w = edge.second;
                dist[u][v] = w;
            }
        }

        // Core of the Floyd-Warshall Algorithm
        for(int k = 0; k < V; k++){
            for(int i = 0; i < V; i++){
                for(int j = 0; j < V; j++){
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }

        // Print the shortest path matrix
        cout << "Shortest Path Matrix:" << endl;
        for(int i = 0; i < V; i++){
            for(int j = 0; j < V; j++){
                cout << dist[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    int V = 4; // Number of vertices
    Graph g(V);

    // Adding edges to the graph
    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 4);
    g.addEdge(1, 2, 1);
    g.addEdge(2, 3, 3);
    g.addEdge(3, 3, 5);

    // The implementation of Floyd-Warshall algorithm would go here
    g.floydWarshall(0);

    return 0;
}
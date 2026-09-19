// Kosaraju's algorithm for finding strongly connected components in a directed graph

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Graph {
    int V; // Number of vertices
    vector<vector<int>> adj; // Adjacency list representation of the graph

    public:
    Graph(int V){
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v){
        adj[u].push_back(v);
    }

    void topoSort(int u, vector<bool>& vis, stack<int>& topo){
        vis[u] = true;

        for(int v : adj[u]){
            if(!vis[v]){
                topoSort(v, vis, topo);
            }
        }

        topo.push(u);
    }

    void dfs(int u, vector<bool>& vis, vector<vector<int>>& Transpose){
        vis[u] = true;
        cout << u << " ";

        for(int v : Transpose[u]){
            if(!vis[v]){
                dfs(v, vis, Transpose);
            }
        }
    }

    void Kosaraju(){
        // Step 1: Find the Topological Sort of the graph
        stack<int> topo;
        vector<bool> vis(V, false);

        for(int i = 0; i < V; i++){
            if(!vis[i]){
                topoSort(i, vis, topo);
            }
        }

        // Step 2: Transpose the graph
        vector<vector<int>> Transpose(V);

        for(int u = 0; u < V; u++){ // u --> v
            vis[u] = false;
            for(int v : adj[u]){
                Transpose[v].push_back(u); // v --> u
            }
        }

        cout << "Strongly Connected Components:" << endl;

        // Step 3: Find the strongly connected components
        // DFS on the transposed graph in the order of the topological sort
        
        while(!topo.empty()){
            int u = topo.top();
            topo.pop();

            if(!vis[u]){
                // Perform DFS on the transposed graph starting from u
                dfs(u, vis, Transpose);
                cout << endl; // New line for the next strongly connected component
            }
        }
    }
};

int main() {
    int V = 5; // Number of vertices
    Graph g(V);

    // Adding edges to the graph
    g.addEdge(0, 2);
    g.addEdge(0, 3);
    g.addEdge(1, 0);
    g.addEdge(2, 1);
    g.addEdge(3, 4);

    // The implementation of Kosaraju's algorithm would go here
    g.Kosaraju();

    return 0;
}
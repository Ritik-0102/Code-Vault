#include<iostream>
#include<vector>

using namespace std;

class DisjointSetUnion{
    int n;
    vector<int> parent;
    vector<int> rank;

    public:
    DisjointSetUnion(int n){
        this->n = n;
        parent.resize(n);
        rank.resize(n);
        for(int i = 0; i < n; i++){
            parent[i] = i;
            rank[i] = 0;
        }
    }

    void unionByRank(int a, int b){
        int parentA = findParent(a);
        int parentB = findParent(b);

        if(parentA == parentB){
            return;
        }

        if(rank[parentA] < rank[parentB]){
            parent[parentA] = parentB;
        }
        else if(rank[parentA] > rank[parentB]){
            parent[parentB] = parentA;
        }
        else{
            parent[parentB] = parentA;
            rank[parentA]++;
        }
    }

    int findParent(int x){
        if(parent[x] == x){
            return x;
        }
        return parent[x] = findParent(parent[x]);
    }
}
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class DSU {
    vector<int> parent, rank;

public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);

        for(int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int x) {
        if(parent[x] != x)
            parent[x] = find(parent[x]); // Path compression
        return parent[x];
    }

    void unionSet(int x, int y) {
        int xroot = find(x);
        int yroot = find(y);

        if(xroot == yroot) return;

        // Union by rank
        if(rank[xroot] < rank[yroot])
            parent[xroot] = yroot;
        else if(rank[xroot] > rank[yroot])
            parent[yroot] = xroot;
        else {
            parent[yroot] = xroot;
            rank[xroot]++;
        }
    }
};

struct Edge {
    int u, v, weight;
};

bool compare(Edge a, Edge b) {
    return a.weight < b.weight;
}

int main() {
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    vector<Edge> edges(E);

    cout << "Enter edges (u v weight): " << endl;
    for(int i = 0; i < E; i++)
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;

    sort(edges.begin(), edges.end(), compare);

    DSU dsu(V);

    vector<Edge> mst;
    int mst_weight = 0;

    for(auto &edge : edges) {
        if(dsu.find(edge.u) != dsu.find(edge.v)) {
            mst.push_back(edge);
            mst_weight += edge.weight;
            dsu.unionSet(edge.u, edge.v);
        }
    }

    cout << "\nMinimum Spanning Tree edges:\n";
    for(auto &edge : mst)
        cout << edge.u << " -- " << edge.v << " == " << edge.weight << endl;

    cout << "\nTotal weight of MST: " << mst_weight << endl;

    return 0;
}

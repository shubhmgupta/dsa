#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// ------------- DSU / UNION-FIND -------------
int findParent(int node, vector<int> &parent) {
    if (parent[node] == node) return node;
    return parent[node] = findParent(parent[node], parent); // path compression
}

void unionSet(int u, int v, vector<int> &parent, vector<int> &rank) {
    u = findParent(u, parent);
    v = findParent(v, parent);

    if (u == v) return;

    if (rank[u] < rank[v]) parent[u] = v;
    else if (rank[v] < rank[u]) parent[v] = u;
    else {
        parent[v] = u;
        rank[u]++;
    }
}

// ------------- KRUSKAL FUNCTION -------------
int kruskal(int V, vector<vector<int>> &edges) {
    // edges[i] = {weight, u, v}

    // Sort edges by weight
    sort(edges.begin(), edges.end());

    vector<int> parent(V);
    vector<int> rank(V, 0);

    for (int i = 0; i < V; i++) parent[i] = i;

    int mst_weight = 0;
    cout << "Edges in MST:\n";

    for (auto &e : edges) {
        int w = e[0];
        int u = e[1];
        int v = e[2];

        if (findParent(u, parent) != findParent(v, parent)) {
            cout << u << " -- " << v << "  (weight = " << w << ")\n";
            mst_weight += w;
            unionSet(u, v, parent, rank);
        }
    }

    return mst_weight;
}

// ------------- MAIN FUNCTION -------------
int main() {

    // ----------- HARDCODED INPUT -----------
    int V = 5;
    vector<vector<int>> edges = {
        {1, 0, 1},
        {3, 0, 2},
        {2, 1, 2},
        {4, 1, 3},
        {5, 2, 3},
        {7, 3, 4},
        {6, 2, 4}
    };

    // ----------- INPUT METHOD (UNCOMMENT) -----------
    /*
    int V, E;
    cin >> V >> E;
    vector<vector<int>> edges(E, vector<int>(3));
    for(int i = 0; i < E; i++){
        cin >> edges[i][0] >> edges[i][1] >> edges[i][2]; // weight, u, v
    }
    */

    int mstCost = kruskal(V, edges);

    cout << "\nTotal MST cost = " << mstCost << endl;

    return 0;
}

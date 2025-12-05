#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

int findParent(int u, vector<int> &parent) {
    if (u == parent[u]) return u;
    return parent[u] = findParent(parent[u], parent); // path compression
}

void unionByRank(int u, int v, vector<int> &parent, vector<int> &rank) {
    int pu = findParent(u, parent);
    int pv = findParent(v, parent);

    if (pu == pv) return; // same component

    if (rank[pu] > rank[pv]) {
        parent[pv] = pu;
    } 
    else if (rank[pv] > rank[pu]) {
        parent[pu] = pv;
    } 
    else {
        parent[pu] = pv;
        rank[pv]++;  // rank of new parent increases
    }
}

int spanningTree(int V, vector<vector<int>> adj[]) {

    vector<int> parent(V), rank(V, 0);
    for (int i = 0; i < V; i++) parent[i] = i;

    // priority queue storing edges {wt , {u , v}}
    priority_queue<
        pair<int, pair<int, int>>,
        vector<pair<int, pair<int, int>>>,
        greater<pair<int, pair<int, int>>> 
    > pq;

    // push all edges into PQ
    for (int u = 0; u < V; u++) {
        for (auto &it : adj[u]) { 
            int v = it[0];
            int wt = it[1];
            pq.push({wt, {u, v}});
        }
    }

    int cost = 0;
    int edges = 0;

    while (!pq.empty()) {
        auto it = pq.top();
        pq.pop();

        int wt = it.first;
        int u = it.second.first;
        int v = it.second.second;

        if (findParent(u, parent) != findParent(v, parent)) {
            cost += wt;
            unionByRank(u, v, parent, rank);
            edges++;
        }

        if (edges == V - 1) break;
    }

    return cost;
}

int main() {

    // ***** Hard Coded Graph (Undirected Weighted) *****
    // Graph: 0 --1-- 1
    //        1 --2-- 2
    //        0 --4-- 2
    int V = 3;
    vector<vector<int>> adj[V];

    adj[0].push_back({1,1});
    adj[1].push_back({0,1});

    adj[1].push_back({2,2});
    adj[2].push_back({1,2});

    adj[0].push_back({2,4});
    adj[2].push_back({0,4});

    cout << "MST Cost = " << spanningTree(V, adj) << endl;


    // ****** OPTIONAL: INPUT FORM ********
    /*
    cin >> V;
    int E;
    cin >> E;
    vector<vector<int>> adj[V];

    for (int i = 0; i < E; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        adj[u].push_back({v, wt});
        adj[v].push_back({u, wt});
    }

    cout << "MST Cost = " << spanningTree(V, adj) << endl;
    */

    return 0;
}

#include<iostream>
#include<vector>
using namespace std;

vector<int> balleman_ford(int V, vector<vector<int>>& edges, int S){
    // Step 1: distance array
    vector<int> dist(V, 1e9);
    dist[S] = 0;

    // Step 2: Relax all edges V-1 times
    for(int i = 1; i <= V-1; i++){
        bool changed = false; // optimization: stop early if no update
        for(auto &e : edges){
            int u = e[0];
            int v = e[1];
            int w = e[2];

            if(dist[u] != 1e9 && dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
                changed = true;
            }
        }
        if(!changed) break; // no update → already optimal
    }

    // Step 3: Check for negative cycle
    for(auto &e : edges){
        int u = e[0];
        int v = e[1];
        int w = e[2];

        if(dist[u] != 1e9 && dist[u] + w < dist[v]){
            cout << "Negative cycle detected\n";
            return {}; // return empty
        }
    }

    return dist;
}


int main(){

    // ---------- HARD CODED INPUT ----------
    int V = 5;
    vector<vector<int>> edges = {
        {0,1,-1},
        {0,2,4},
        {1,2,3},
        {1,3,2},
        {1,4,2},
        {3,2,5},
        {3,1,1},
        {4,3,-3}
    };
    int S = 0;


    // ---------- INPUT METHOD (UNCOMMENT IF NEEDED) ----------
    /*
    int V, E;
    cin >> V >> E;
    vector<vector<int>> edges(E, vector<int>(3));
    for(int i = 0; i < E; i++){
        cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
    }
    int S;
    cin >> S;
    */

    vector<int> ans = balleman_ford(V, edges, S);

    if(ans.size() == 0) return 0; // negative cycle

    for(int i = 0; i < V; i++){
        if(ans[i] == 1e9) cout << "INF ";
        else cout << ans[i] << " ";
    }

    return 0;
}

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int shortestPathLength(vector<vector<int>>& graph) {
        int n = graph.size();
        queue<pair<int, int>> q;

        vector<vector<bool>> vis(n, vector<bool> (1<<n, false));

        // punem in coada toate nodurile si marcam cu 1 viz[i][1<<i]
        // la inceput stim ca traseele cu un singur nod sunt vizitate deci pentru nodul i stim traaseul curent ca fiind 1<<i
        for(int i=0; i<n; i++) {
            q.push({i, 1<<i});
            vis[i][1<<i] = 1;
        }
        // facem un bfs in care matricea viz va fi actualizat pentru fiecare path
        // spre exemplu daca prin bfs parcurgem nodul 0 si nodul 2 masca de biti va arata sub forma 000...101
        // ne vom opri cand masca de biti va fi 111...11 adica 1<<n
        // fiecare traseu va avea o codificare unica de aceea viz depinde si de nodul x dar si de traseul curent pana in nodul x,
        // adica masca de biti curenta
        int ans = 0;
        while(q.size()) {
            for(int k = q.size(); k; k--) {
                auto [i, mask] = q.front();
                q.pop();
                if(mask == (1<<n)-1) return ans;
                for(auto x: graph[i]) {
                    if(!vis[x][mask | (1 << x)]) {
                        q.push({x, mask | (1 << x)});
                        vis[x][mask | (1 << x)] = 1;
                    }
                }
            }
            ans++;
        }
        return ans;
    }
};
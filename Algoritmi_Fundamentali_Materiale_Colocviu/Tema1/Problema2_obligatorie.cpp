#include <bits/stdc++.h>
#include <fstream>

using namespace std;
vector<vector<int>> graph;
vector<int> order_given;
vector<int> viz;
vector<int> dfs_order;
vector<int> positions;

bool cmp(int a, int b){
    return positions[a] < positions[b];
}



void DFS2(vector<vector<int>> &graph, int n, int x){
    viz[x]=1;
    dfs_order.push_back(x);
    for(int i=0;i<graph[x].size();i++){
        if(viz[graph[x][i]]==0){
            DFS2(graph,n,graph[x][i]);
        }
    }
}

int main() {

    int n,m;
    ifstream f;
    f.open("graf.in");
    f>>n>>m;
    graph.resize(n+1);
    viz.resize(n+1);
    positions.resize(n+1);
    for(int i=0;i<n;i++){
        int x;
        f>>x;
        order_given.push_back(x);
        positions[x]=i;
    }
    for(int i=0;i<m;i++){
        int x,y;
        f>>x>>y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
//    DFS(graph,n,1);
//    for(int i : dfs_order){
//        cout<<i<<" ";
//    }

    for(int i=1;i<=n;i++){
        sort(graph[i].begin(), graph[i].end(), cmp);
    }

    DFS2(graph,n,1);
    cout<<(order_given==dfs_order);

    return 0;
}

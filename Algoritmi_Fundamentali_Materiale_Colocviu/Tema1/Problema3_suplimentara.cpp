#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> graph;
vector<int> viz;
vector<int> dist;
vector<vector<int>> distanta_nod(7510);

void BFS(int i){
    queue <int> q;
    dist[i]=0;
    q.push(i);
    while(!q.empty()){
        int cur=q.front();
        q.pop();
        for(int & j : graph[cur]){
            if(dist[j] > dist[cur]+1){
                dist[j]=dist[cur]+1;
                q.push(j);
            }
        }
    }
}

void DFS(int i){
    viz[i]=1;
    distanta_nod[dist[i]].push_back(i);
    for(int & j : graph[i]){
        if(!viz[j] && dist[j] < dist[i]){
            DFS(j);
        }
    }
}

int main() {

    ifstream f("graf.in");
    ofstream g("graf.out");
    int n,m,x,y;
    f>>n>>m>>x>>y;
    viz.resize(n+1);
    graph.resize(n+1);
    dist.resize(n+1, 999999);
    for(int i=0;i<m;i++){
        int a,b;
        f>>a>>b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    vector<int> sol;
    BFS(x);
    DFS(y);
    for(int i=0;i<=n;i++){
        if(distanta_nod[i].size()==1){
            sol.push_back(distanta_nod[i][0]);
        }
    }
    g<<sol.size()<<"\n";
    sort(sol.begin(), sol.end());
    for(int i=0;i<sol.size();i++){
        g<<sol[i]<<" ";
    }


    return 0;
}

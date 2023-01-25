#include <bits/stdc++.h>
using namespace std;
ifstream f("cuplaj.in");
ofstream g("cuplaj.out");

int nodes, edges, s, t, leftt, rightt;
vector<int> father;
vector<vector<int>> capacity;
vector<vector<int>> graph;
vector<vector<int>> edg;
long cost_minn=0;


void read(){
    f>>leftt>>rightt>>edges;
    nodes=leftt+rightt+2;

    graph.resize(nodes+1);
    father.resize(nodes+1);
    capacity.resize(nodes+1, vector<int>(nodes+1));

    for(int i=0;i<edges;i++){
        int x,y;
        f>>x>>y;
        graph[x].push_back(y+leftt);
        graph[y+leftt].push_back(x);
        capacity[x][y+leftt]=1;
    }

    for(int i=1;i<=leftt;i++){
        graph[0].push_back(i);
        graph[i].push_back(0);
        capacity[0][i]=1;
    }

    for(int i=leftt+1;i<=leftt+rightt;i++) {
        graph[i].push_back(nodes - 1);
        graph[nodes - 1].push_back(i);
        capacity[i][nodes - 1] = 1;
    }
    s=0;
    t=nodes-1;

}

bool bfs(){
    vector <bool> viz(nodes+1);
    queue<int> q;
    q.push(s);
    viz[s]=true;
    father[s]=-1;
    while(!q.empty()){
        int current_node = q.front();
        q.pop();
        for(auto adj: graph[current_node]){
            if(!viz[adj] && capacity[current_node][adj]){
                father[adj]=current_node;
                if(adj==t){
                    return true;
                }
                viz[adj]=true;
                q.push(adj);
            }
        }
    }
    return false;
}

int edmondsKarp(){
    long flux_max=0;
    while(bfs()){
        int x, y, path_min=INT_MAX;
        for(x=t;x!=s;x=father[x]){
            y=father[x];
            if(capacity[y][x] < path_min){
                path_min=capacity[y][x];
            }
        }
        for(x=t;x!=s;x=father[x]){
            y=father[x];
            capacity[y][x] -= path_min;
            capacity[x][y] += path_min;
        }
        flux_max += path_min;

    }
    return flux_max;
}


int main(){
    read();
    g<<edmondsKarp()<<"\n";
    for(int i=1;i<=leftt;i++){
        for(auto node: graph[i]){
            if(node!=s && capacity[i][node]==0 && node!=t){
                g<<i<<" "<<node-leftt<<"\n";
            }
        }
    }
    return 0;
}
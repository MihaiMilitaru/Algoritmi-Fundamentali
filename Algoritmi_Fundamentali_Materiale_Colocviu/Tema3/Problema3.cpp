#include <bits/stdc++.h>
using namespace std;
ifstream f("harta.in");
ofstream g("harta.out");

int nodes, edges, s, t;
vector<int> father;
vector<vector<int>> capacity;
vector<vector<int>> graph;
vector<vector<int>> edg;
long cost_minn=0;

void read(){
    f>>nodes;
    s=0;
    t=2*nodes+1;

    graph.resize(2*nodes+2);
    father.resize(2*nodes+2);

    capacity.resize(2*nodes+2, vector<int>(2*nodes+2));
    for(int i=1;i<=nodes;i++){
        int x,y;
        f>>x>>y;
        // x - gradul de intrare
        // y - gradul de iesire
        // construim muchiile (s, i) si punem capacitatile gradele de intrare
        graph[s].push_back(i);
        graph[i].push_back(s);
        capacity[s][i]=x;

        // construim muchiile (i, t) si punem capacitatile gradele de iesire
        graph[nodes+i].push_back(t);
        graph[t].push_back(nodes+i);
        capacity[nodes+i][t]=y;

    }
    // punem restul capacitatilor 1
    for(int i=1;i<=nodes;i++){
        for(int j=1;j<=nodes;j++){
            if(i!=j){
                graph[i].push_back(nodes+j);
                graph[nodes+j].push_back(i);
                capacity[i][nodes+j]=1;
            }
        }
    }

}

bool bfs(){
    vector <bool> viz(2*nodes+2);
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
    for(int i=1;i<=nodes;i++){
        for(auto node: graph[i]){
            if(node!=s && capacity[i][node]==0 && node!=t){
                g<<i<<" "<<node-nodes<<"\n";
            }
        }
    }
    return 0;
}
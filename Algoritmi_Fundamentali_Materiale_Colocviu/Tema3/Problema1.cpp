#include <iostream>
#include <fstream>
#include <climits>
#include <vector>
#include <queue>

using namespace std;

ifstream fin("maxflow.in");
ofstream fout("maxflow.out");

int nodes, edges, s, t;
vector<int> father;
vector<vector<int>> capacity;
vector<vector<int>> graphh;
vector<vector<int>> graph;
vector<vector<int>> edg;



void read(){
    fin>>nodes>>edges;
    s=1;
    t=nodes;
    graph.resize(nodes+1);
    father.resize(nodes+1);
    capacity.resize(nodes+1, vector<int>(nodes+1));
    graphh.resize(nodes+1,  vector<int>(nodes+1));
    for(int i=0;i<edges;i++){
        int x, y;
        long cost;
        fin>>x>>y>>cost;

        graphh[x][y]=cost;
        edg.push_back({x,y,cost});
        graph[x].push_back(y);
        graph[y].push_back(x);
        // folosim graf rezidual si retinem capacitatea arcului x y in matricea apacity[x][y]
        capacity[x][y]=cost;
    }

}

// gasim un drum de ameliorare printr o parcurgere bfs
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

void dfs(vector<vector<int>> graphh, int s, vector<bool> &vizz){

    vizz[s]=true;
    for(int i=1;i<=nodes;i++){
        if(graphh[s][i] && !vizz[i]){
            dfs(graphh, i, vizz);
        }
    }
}

int edmondsKarp(){
    long flux_max=0;
    // cat timp exista drum de ameliorare gasim capacitatea reziduala minima si actualizam noile capacitati
    // daca am arc direct atunci scad din capacitatea arcului capacitatea reziduala minima
    // pentru arcele inverse crestem capacitatea cu capacitatea reziduala minima

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

    // facem o parcurgere dfs si vedem pe ce arce apar intreruperi adica daca am arcul (u,v) si nodul u a fost vizitat
    // iar nodul v nu a fost vizitat atunci arcul (u, v) face parte din min-cut
    vector<bool> vizz(nodes+1,false);
    dfs(capacity,s,vizz);
    for(int i=1;i<=nodes;i++){
        for(int j=1;j<=nodes;j++){
            if(vizz[i] && !vizz[j] && graphh[i][j]){
                cout<<i<<" - "<<j<<"\n";
            }
        }

    }

    return flux_max;
}

int main(){
    read();
    fout<<edmondsKarp();

    return 0;
}


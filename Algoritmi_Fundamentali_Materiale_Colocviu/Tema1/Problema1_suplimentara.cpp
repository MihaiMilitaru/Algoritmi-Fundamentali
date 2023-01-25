#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> graph;
vector<int> viz;
vector<int> nivel;
vector<int> nivel_min;

vector<vector<int>> muchii;


void dfs(int i){
    viz[i]=1;
    nivel_min[i] = nivel[i];
    for(int j=0;j<graph[i].size();j++){
        if(viz[graph[i][j]]==0){        // muchie de avansare
            nivel[graph[i][j]] = nivel[i] + 1;
            dfs(graph[i][j]);

            nivel_min[i] = min(nivel_min[i], nivel_min[graph[i][j]]);

            if(nivel_min[graph[i][j]] > nivel[i]){
                muchii.push_back({i, graph[i][j]});

                cout<<"[ "<<i<<" "<<graph[i][j]<<" ]\n";
            }
        }else{
            if(nivel[graph[i][j]] < nivel[i]-1){  // muchie de intoarcere
                nivel_min[i] = min(nivel_min[i], nivel[graph[i][j]]);
            }
        }
    }
}

//vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
//    graph.resize(n+1);
//    for(int i=0;i<connections.size();i++){
//        graph[connections[i][0]].push_back(connections[i][1]);
//        graph[connections[i][1]].push_back(connections[i][0]);
//    }
//    viz.resize(n+1);
//    nivel.resize(n+1);
//    nivel_min.resize(n+1);
//    nivel[0]=1;
//    dfs(0);
//    return muchii;
//
//}

int main() {
    int n,m;
    ifstream f("graf.in");
    f>>n>>m;
    viz.resize(n+1);
    graph.resize(n+1);
    nivel.resize(n+1);
    nivel_min.resize(n+1);
    nivel[1]=1;

    for(int i=0;i<m;i++){
        int x,y;
        f>>x>>y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    dfs(0);

}

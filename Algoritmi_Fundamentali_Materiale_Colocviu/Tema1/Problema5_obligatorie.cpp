#include <bits/stdc++.h>
# include <fstream>
using namespace std;
int n, ctr1,ctr2,m;

vector<vector<int>> graph ;


//int distanta(vector<vector<int>> graph, int n, int start, int end){
//    queue<int> coada;
//    vector <int> dist(n+1, -1);
//    dist[start]=0;
//    coada.push(start);
//    while(coada.size()){
//        int st=coada.front();
//        coada.pop();
//        for(int i=0;i<graph[st].size();i++){
//            if(dist[graph[st][i]]==-1){
//                coada.push(graph[st][i]);
//                dist[graph[st][i]]=dist[st]+1;
//            }
//        }
//    }
//    return dist[end];
//
//}


void distanta_2(vector<vector<int>> graph, int n, int start, vector<int>& v){
    queue<int> coada;
    vector <int> dist(n+1, -1);
    v[start]=0;
    coada.push(start);
    while(coada.size()){
        int st=coada.front();
        coada.pop();
        for(int i=0;i<graph[st].size();i++){
            if(v[graph[st][i]]==-1){
                coada.push(graph[st][i]);
                v[graph[st][i]]=v[st]+1;
            }
        }
    }


}

int main() {

    ifstream f;
    f.open("graf.in");
    ofstream g;
    g.open("graf.out");

    f>>n>>m;

    graph.resize(n+1);
    for(int i=0;i<m;i++){
        int x,y;
        f>>x>>y;
        graph[x].push_back(y);
        graph[y].push_back(x);

    }


    f>>ctr1>>ctr2;
    vector<int> real_dist_first;
    real_dist_first.resize(n+1, -1);

    vector<int> real_dist_second;
    real_dist_second.resize(n+1, -1);

    distanta_2(graph, n, ctr1, real_dist_first);
    distanta_2(graph, n, ctr2, real_dist_second);

    for(int i=1;i<=n;i++){

        if(real_dist_first[i]==-1 && real_dist_second[i]==-1){
            cout<<-1<<" ";
        }
        if(real_dist_first[i]==-1 && real_dist_second[i]!=-1){
            cout<<real_dist_second[i]<<" ";
        }else{
            if(real_dist_first[i]!=-1 && real_dist_second[i]==-1){
                cout<<real_dist_first[i]<<" ";
            }else{
                cout<<min(real_dist_first[i],real_dist_second[i])<<" ";
            }

        }

    }

//    for(int i=1;i<=n;i++){
//        int a=distanta(graph,n,i,ctr1);
//        int b=distanta(graph,n,i,ctr2);
//        if(a==-1 && b==-1){
//            cout<<-1<<" ";
//        }
//        if(a==-1 && b!=-1){
//            cout<<b<<" ";
//        }else{
//            if(a!=-1 && b==-1){
//                cout<<a<<" ";
//            }else{
//                cout<<min(a,b)<<" ";
//            }
//
//        }
//
//    }

    return 0;
}

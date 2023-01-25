#include <bits/stdc++.h>

using namespace std;
int n,rules;
vector<vector<int>> courses;
vector <int> fin;
vector <int> viz;
vector <int> father;
vector<int> cycle;
// 1 - inca vizitat
// 2 - vizitat deja


bool dfs(vector<vector<int>> &graph, int index, vector<int> &sol, vector<int> &stari){
    // functia dfs da true cand gaseste un ciclu
    if (stari[index]==1){
        return true;
    }

    if (stari[index]==2){
        return false;
    }

    stari[index]=1;
    for (const int adj : graph[index])
        if (dfs(graph, adj,sol, stari))
            return true;

    stari[index]=2;
    sol.push_back(index);

    return false;
}

vector<int> order(int n, vector<vector<int>>& courses){
    vector<int>sol;
    vector<vector<int>> graph(n);
    vector<int> stari(n);
    graph.resize(n+1);
    stari.resize(n+1);

    for (const auto& c : courses)
        graph[c[1]].push_back(c[0]);

    for (int i=0;i<n;i++)
        if (dfs(graph, i, sol, stari))
            return {};

    reverse(begin(sol), end(sol));
    return sol;
}

void DFS2(vector<vector<int>> &graph, int index, vector<int> &viz, vector <int> &fin, vector<int> &father){
    viz[index]=1;
    for(int i=0;i<graph[index].size();i++){
        if(viz[graph[index][i]]==0){
            father[graph[index][i]]=index;
            DFS2(graph, graph[index][i], viz, fin,father);
        }else{
            if(fin[graph[index][i]]==0){
                int v=index;
                while(v!=graph[index][i]){
                    cycle.push_back(v);
                    v=father[v];
                }
                cycle.push_back(graph[index][i]);
                cycle.push_back(index);
            }
        }
    }
    fin[index]=1;

}


vector<int> order2(){

    vector<vector<int>> graph(n+1);


    for (const auto& c : courses)
        graph[c[1]].push_back(c[0]);

    viz.resize(n+1);
    father.resize(n+1);
    fin.resize(n+1);

    for(int i=0;i<n;i++){
        if(viz[i]==0){
            DFS2(graph, i, viz, fin, father);
            if(!cycle.empty()){
                return cycle;

            }
        }
    }

    return {};

}



int main() {

    ifstream f("graf.in");
    f>>n>>rules;
    for(int i=0;i<rules;i++){
        int x,y;
        f>>x>>y;
        vector<int> curs;
        curs.push_back(x);
        curs.push_back(y);
        courses.push_back(curs);
    }

//    // Cerinta a.
//    vector<int > solutie=order(courses,n);
//    for(auto& c: solutie){
//        cout<<c<<" ";
//    }

    //Cerinta b.

    vector<int> soll = order2();
    for(int i : soll){
        cout<<i<<" ";
    }
}



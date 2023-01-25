#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void hierholzer(stack<int>&path,unordered_map<int,vector<int>>&graph,unordered_map<int,int>&out,int vertex){
        while(out[vertex]){
            hierholzer(path, graph, out, graph[vertex][--out[vertex]]);

        }
        path.push(vertex);
    }
    vector<vector<int>> validArrangement(vector<vector<int>>& pairs) {
        unordered_map<int,vector<int>>graph;
        unordered_map<int,int>out,in;
        // memoram in out si in gradele de iesire si intrare pentru fiecare nod
        for (auto pr : pairs){
            graph[pr[0]].push_back(pr[1]);
            out[pr[0]]++;
            in[pr[1]]++;
        }
        int start=-1;
        for(auto d : out){
            // daca numarul gradelor de iesire este mai mare decat numarul gradelor de intrare il alegem ca nod de start pe d.first
            if(d.second-in[d.first]==1){
                start=d.first;
            }else{
                if(d.second == in[d.first] && start==-1){
                    start=d.first;
                }
            }

        }

        stack<int>path;
        vector<int>vpath;

        hierholzer(path,graph,out,start);

        while(path.size()){
            vpath.push_back(path.top());
            path.pop();
        }

        vector<vector<int>>solution;

        for(int i=0;i<vpath.size()-1;i++){
            solution.push_back({vpath[i], vpath[i+1]});
        }

        return solution;
    }
};

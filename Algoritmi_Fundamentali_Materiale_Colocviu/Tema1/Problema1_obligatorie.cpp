#include <iostream>
#include <vector>
using namespace std;
int n, nr_dis;

bool DFS(int n, vector<vector<int>>& graph,   vector<int>& group, int current_index, int group_index){
    group[current_index]=group_index;
    for(int i=1;i<=n;i++){
        if(graph[i][current_index]==1){
            if(group[i]==group_index){
                return false;
            }
            if(group[i]==0 && !DFS(n, graph,group, i, -group_index)){
                return false;
            }
        }
    }
    return true;

}


bool PossibleBiPartition(int n,vector<vector<int>> &dislikes){
    vector<vector<int>> graph(n+1, vector<int>(n+1));
    for(auto & dislike : dislikes){
        graph[dislike[0]][dislike[1]]=1;
        graph[dislike[1]][dislike[0]]=1;

    }
    vector<int> group(n+1, 0);
    for(int i=1;i<=n;i++){
        if(group[i]==0 && !DFS(n, graph, group, i, 1)){
            return false;
        }
    }

    return true;

}

vector<vector<int>> PossibleBiPartition_b(int n,vector<vector<int>> &dislikes){
    vector<vector<int>> graph(n+1, vector<int>(n+1));
    for(auto & dislike : dislikes){
        graph[dislike[0]][dislike[1]]=1;
        graph[dislike[1]][dislike[0]]=1;

    }
    vector<int> group(n+1, 0);
    for(int i=1;i<=n;i++){
        if(group[i]==0 && !DFS(n, graph, group, i, 1)){
            return {};
        }
    }
    // return the two partitions
    vector<vector<int>> new_array;
    vector<int> first_partition;
    vector<int> second_partition;

    for(int i=0;i<=n;i++){
        if(group[i]==-1){
            second_partition.push_back(i);
        }
        if(group[i]==1){
            first_partition.push_back(i);
        }
    }
    new_array.push_back(first_partition);
    new_array.push_back(second_partition);

    return new_array;



}



int main() {
    cin>>n>>nr_dis;
    vector<vector<int>> dislikes;
    int x,y;
    for(int i=0;i<nr_dis;i++){
        cin>>x>>y;
        vector<int> dislike;
        dislike.push_back(x);
        dislike.push_back(y);
        dislikes.push_back(dislike);

    }

    vector<vector<int>> bipart = PossibleBiPartition_b(n,dislikes);
    if(bipart.empty()){
        cout<<"Nu se poate face partitia.";
    }else{
        for(int i=0;i<2;i++){
            for(int j : bipart[i]){
                cout<<j<<" ";
            }
            cout<<"\n";
        }
    }

    return 0;
}

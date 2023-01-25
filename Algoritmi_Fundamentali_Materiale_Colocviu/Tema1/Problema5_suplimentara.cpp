#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> grid;
vector<vector<int>>viz;

int area(int r, int c){
    if(r<0 or r>=grid.size() or c<0 or c>=grid[0].size() or viz[r][c] or grid[r][c]==0){
        return 0;
    }
    viz[r][c]=1;
    return (1+ area(r-1,c) + area(r+1, c) + area(r, c+1) + area(r, c-1));
}

int solution(){
    int zone=0;
    for(int r=0;r<grid.size();r++){
        for(int c=0;c<grid[0].size();c++){
            zone=max(zone, area(r,c));

        }
    }
    return zone;
}

int main() {
    ifstream f("grid.in");
    int n,m;
    f>>n>>m;
    grid.resize(n);
    viz.resize(n);
    for(int i=0;i<n;i++){
        grid[i].resize(m);
        viz[i].resize(m);
    }
    grid = {{0,0,1,0,0,0,0,1,0,0,0,0,0},{0,0,0,0,0,0,0,1,1,1,0,0,0},{0,1,1,0,1,0,0,0,0,0,0,0,0},{0,1,0,0,1,1,0,0,1,0,1,0,0},{0,1,0,0,1,1,0,0,1,1,1,0,0},{0,0,0,0,0,0,0,0,0,0,1,0,0},{0,0,0,0,0,0,0,1,1,1,0,0,0},{0,0,0,0,0,0,0,1,1,0,0,0,0}};


    cout<<solution();


    return 0;
}

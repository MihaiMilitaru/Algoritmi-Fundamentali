#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

ifstream fin("easygraph.in");
ofstream fout("easygraph.out");

const long long oo = 2e9;
int n, m, t;
long long sum;
vector <vector <int>> v;
vector <long long> dp, val;
vector <bool> visited;

void init() {
    v = vector <vector <int>> (n + 1);
    visited = vector <bool> (n + 1);
    val = vector <long long> (n + 1);
    dp = vector <long long> (n + 1, -oo);
    sum = -oo;
}



void dfs(int node) {
    visited[node] = true;
    dp[node] = val[node];
    for(const auto& neighbor : v[node]) {
        if(!visited[neighbor])
            dfs(neighbor);
        dp[node] = max(dp[node], dp[neighbor] + val[node]);
    }
    sum = max(sum, dp[node]);
}

int main() {
    fin >> t;
    for(int test = 1; test <= t; ++test) {
        fin >> n >> m;
        init();
        for(int i = 1; i <= n; i ++)
            fin >> val[i];
        int x, y;
        for(int i = 1; i <= m; i ++) {
            fin >> x >> y;
            v[x].push_back(y);
        }

        for(int i = 1; i <= n; i ++)
            if(!visited[i])
                dfs(i);

        fout << sum << '\n';
        v.clear();
        visited.clear();
        val.clear();
        dp.clear();
    }
    return 0;

}
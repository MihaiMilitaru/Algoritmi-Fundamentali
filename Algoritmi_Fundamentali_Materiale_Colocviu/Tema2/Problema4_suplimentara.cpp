#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

ifstream fin("apm2.in");
ofstream fout("apm2.out");

struct edge {
    int x, y, cost;

    bool operator <(const edge& other) const{
        return cost < other.cost;
    }
};

vector <edge> v, apm;
vector <int> h, t;
int n, m, q, totalCost;

void init() {
    h = vector <int> (n + 1);
    t = vector <int> (n + 1);
    for(int i = 1; i <= n; ++i)
        t[i] = i;
}


void read() {
    fin >> n >> m >> q;
    init();
    int x, y, cost;
    for(int i = 1; i <= m; ++i) {
        fin >> x >> y >> cost;
        v.push_back({x, y, cost});
    }
}

int getRoot(int node) {
    if(t[node] == node) {
        return node;
    }
    return (t[node] = getRoot(t[node]));
}

bool sameConnectedComponents(int x, int y) {
    return getRoot(x) == getRoot(y);
}

void unite(int x, int y) {
    int rootX = getRoot(x);
    int rootY = getRoot(y);
    if(h[rootX] < h[rootY]) {
        t[rootX] = rootY;
    }
    else {
        if(h[rootX] == h[rootY])
            ++h[rootX];
        t[rootY] = rootX;
    }
}

void kruskal() {
    int x, y, cost;
    for(const auto& p : v) {
        x = p.x;
        y = p.y;
        cost = p.cost;
        if(sameConnectedComponents(x, y))
            continue;
        unite(x, y);
        totalCost += cost;
        apm.push_back({x, y, cost});
    }
}

void solve() {
    sort(v.begin(), v.end());
    kruskal();
//    for(int i=0;i<apm.size();i++){
//        cout<<apm[i].cost<<"\n";
//    }
    int x, y, c;
    for(int i = 1; i <= q; i ++) {
        c = 0;
        init();
        fin >> x >> y;
        unite(x, y);
        for(const auto& p : apm) {
            if(getRoot(p.x) != getRoot(p.y)) {
                unite(p.x, p.y);
                c += p.cost;
            }
        }
        fout << totalCost - c - 1 << '\n';
    }
}

int main()
{
    read();
    solve();
}
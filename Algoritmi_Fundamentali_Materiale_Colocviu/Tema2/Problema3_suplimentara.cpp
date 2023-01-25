#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

ifstream fin("online.in");
ofstream fout("online.out");

// definim o muchie ca avand un nod x de unde pleaca, un nod y unde se duce si costul ei
struct edge {
    int x, y, cost;

    bool operator<(const edge& other) const {
        return cost < other.cost;
    }
};

vector <edge> v;
vector <int> t, h;
int n, m, sum, k;


// initializam vectorii h de la height si t de la tata si initial tata de i este tot i
void init() {
    h = vector <int> (n + 1);
    t = vector <int> (n + 1);
    for(int i = 1; i <= n; ++i)
        t[i] = i;
}

// mergem din tata in tata pana gasim reprezentantul aka stramosul nodului
int getRoot(int node) {
    if(node == t[node])
        return node;
    return (t[node] = getRoot(t[node]));
}

// verificam daca doua noduri au acelasi stramos aka reprezentant
bool sameConnectedComponents(int x, int y) {
    return getRoot(x) == getRoot(y);
}

// gasim radacina lui x si a lui y si facem reuniune de arbori disjuncti
void unite(int x, int y) {
    int rootX = getRoot(x);
    int rootY = getRoot(y);
    if(rootX == rootY)
        return;
    if(h[rootX] < h[rootY])
        t[rootX] = rootY;
    else {
        if(h[rootX] == h[rootY])
            ++h[rootX];
        t[rootY] = rootX;
    }
}

void kruskal() {
    int x, y, c;
    sum = 0;
    vector <edge> apm;
    init();
    // sortam muchiile din vectorul v

    for(const auto& p : v) {
        x = p.x;
        y = p.y;
        c = p.cost;
        // daca sunt din aceeasi componenta dam skip
        if(sameConnectedComponents(x, y))
            continue;

        // altfel facem reuniune de arbori disjuncti
        unite(x, y);
        sum += c;
        apm.push_back({x, y, c});
    }
    v = apm;
    apm.clear();
    h.clear();
    t.clear();
    fout << sum << '\n';
}

void read() {
    fin >> n >> m;
    init();
    int x, y, c;
    for(int i = 1; i <= m; ++i) {
        fin >> x >> y >> c;
        v.push_back({x, y, c});
    }
}

void solve() {
    sort(v.begin(), v.end());
    kruskal();
    fin >> k;
    int x, y, c;
    for(int i = 1; i <= k; i ++) {
        fin >> x >> y >> c;
        v.push_back({x, y, c});
        sort(v.begin(), v.end());
        kruskal();
    }
}

int main()
{
    read();
    solve();
}
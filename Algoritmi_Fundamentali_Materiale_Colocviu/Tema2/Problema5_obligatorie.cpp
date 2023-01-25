#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

ifstream f("catun.in");
ofstream g("catun.out");

int result[36001];
int minim[36001];
vector<pair<int, int>> graf[36001];
priority_queue<pair<int, int>> q;
int n, m, k;

void dijkstra() {

    // retinem perechi de forma (cost_sa_ajung_la_nod, nod)

    while (!q.empty()) {

        // extragem primul nod din coada cu costul cel mai mic deoarece va fi cu minus
        int nod = q.top().second;
        q.pop();
        for (auto& v : graf[nod]) {

            // parcurgem lista de adiacenta si relaxam muchiile

            if (minim[nod] + v.second < minim[v.first]) {

                // actualizam vectorul minim si bagam in coada perechea (cost_sa_ajung_la v, nod v)

                minim[v.first] = minim[nod] + v.second;
                q.push(make_pair(-minim[v.first], v.first ));

                // stramosul lui v va fi stramosul lui nod
                result[v.first] = result[nod];
            }

            // daca relaxarea muchiei are acelasi efect ca pastrarea valorii curente atunci alegem fortareata cu indexul minim
            else if (minim[nod] + v.second == minim[v.first]) {
                result[v.first] = min(result[v.first], result[nod]);
            }
        }
    }
}

int main() {

    f >> n >> m >> k;

    for (int i = 1; i <= n; i++)
        minim[i] = INT_MAX;

    for (int i = 1; i <= k; i++) {
        int x; f >> x;
        result[x] = x;
        q.push({ 0, x });
        minim[x] = 0;
    }
    for (int i = 1; i <= m; i++) {
        int x, y, z;
        f >> x >> y >> z;
        graf[x].push_back(make_pair(y, z));
        graf[y].push_back(make_pair(x, z));
    }
    dijkstra();
    // daca stramosul nodului i este tot i atunci e fortareata altfel e cocioaba ordinara
    for (int i = 1; i <= n; i++)
        if (result[i] == i)
            g << 0 << " ";
        else
            g << result[i] << " ";
    cout<<"Fortarete care nu se leaga de nicio asezare:\n";
    for(int i=0;i<=n;i++){
        if(minim[i]==INT_MAX && result[i]==i){
            cout<<i<<" ";
        }
    }
    return 0;
}

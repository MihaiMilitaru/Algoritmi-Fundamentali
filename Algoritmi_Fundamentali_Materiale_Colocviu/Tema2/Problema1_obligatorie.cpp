//#include <iostream>
//#include <fstream>
//#include <cmath>
//using namespace std;
//ifstream f("retea2.in");
//struct punct{
//    double x, y;
//};
//const int NMAX = 2000;
//const int MMAX = 2000;
//
//int n, m;
//punct poz[NMAX + MMAX + 5];
//bool vizitat[NMAX + MMAX + 5];
//long long dmin[NMAX + MMAX + 5];
//
//int update(int idx) {
//    int d_dmin = -1;
//    for(int i = n+1; i <= n + m; i++) {
//
//        if(vizitat[i])
//            continue;
//
//        long long d = 1LL * (poz[idx].x - poz[i].x) * (poz[idx].x- poz[i].x) +
//                      1LL * (poz[idx].y - poz[i].y) * (poz[idx].y - poz[i].y);
//
//        if(dmin[i] == -1 || d < dmin[i])
//            dmin[i] = d;
//
//        if(d_dmin == -1 || dmin[i] < dmin[d_dmin])
//            d_dmin = i;
//    }
//
//    return d_dmin;
//}
//
//int main() {
//    freopen("retea2.out", "w", stdout);
//    f>>n>>m;
//    for(int i=1; i<=n+m; i++) {
//        double x, y;
//        f >> x >> y;
//        poz[i] = {x, y};
//        dmin[i] = -1;
//    }
//
//    int nod = -1;
//    for(int i = 1; i <= n; i++) {
//        vizitat[i] = true;
//        nod = update(i);
//    }
//
//    double dtotal = 0;
//    for(int j = 1; j <= m; j++) {
//        vizitat[nod] = true;
//        dtotal += sqrt(dmin[nod]);
//        nod = update(nod);
//    }
//
//    printf("%.6lf", dtotal);
//
//    return 0;
//}




#include <bits/stdc++.h>
#include <fstream>

using namespace std;
ifstream f("retea2.in");


map< pair<int, int>, pair<int, int>> parent;
map< pair<int, int>, int> height;
vector<vector<int>> points;
map<pair<int, int>, bool> check_centrala;

//comparam costurile unui tuplu ca sa le sortam crescator
bool cmp(tuple<pair<int, int>, pair<int, int>, int> &a, tuple<pair<int, int>, pair<int, int>, int> &b){
    return get<2>(a) < get<2>(b);
}

//gasim stramosul nodului x prin vectori de tati; cazul default e cel cand nodul x e radacina adica e propriul lui stramos
pair<int, int> reprez(pair<int, int> x){
    if(parent[x]==x){
        return x;
    }
    parent[x]=reprez(parent[x]);
    return parent[x];
}

//unim arborii nodurilor x si y cautandu-le reprezentantii si in functie de inaltime legam arborele mai mic la cel mai mare
void unite(pair<int, int> x, pair<int, int> y){
    x=reprez(x);
    y=reprez(y);
    if(height[x]<height[y]){
        parent[x]=y;
    }else{
        if(height[x]==height[y]){
            ++height[x];
        }
        parent[y]=x;
    }
}


int minCostConnectPoints(vector<vector<int>>& points) {
    double costt=0;
    vector <tuple<pair<int, int>, pair<int, int>, int>> perechi;

    // calculam fiecare muchie si costul ei, adica distanta de la nodul i la nodul j
    for(int i=0;i<points.size()-1;i++){
        for(int j=i+1;j<points.size();j++){

            long long distt = 1LL * (points[i][0] - points[j][0]) * (points[i][0]- points[j][0])  +  1LL * (points[i][1] - points[j][1]) * (points[i][1]- points[j][1]) ;

            tuple<pair<int, int>, pair<int, int>, long long> pereche={make_pair(points[i][0], points[i][1]), make_pair(points[j][0], points[j][1]),distt };

            perechi.push_back(pereche);
        }
    }
    sort(perechi.begin(), perechi.end(),cmp);

    int m= perechi.size();
    int n=points.size();

    // parinte de i va fi i
    for(int i=0;i<n;i++){
        parent[make_pair(points[i][0], points[i][1])]=make_pair(points[i][0], points[i][1]);
    }

    // daca reprezentantii sunt egali sau ambii reprezentanti sunt centrale dam skip altfel facem reuniune de arbori
    for(int i=0;i<m;i++){
        if(reprez(get<0>(perechi[i])) == reprez(get<1>(perechi[i])) or (check_centrala[reprez(get<0>(perechi[i]))] and check_centrala[reprez(get<1>(perechi[i]))] )){
            continue;
        }
        unite(get<0>(perechi[i]), get<1>(perechi[i]));


        costt+=sqrt(get<2>(perechi[i]));
    }

    return costt;

}


int main(){

    int nn,mm;
    freopen("retea2.out", "w", stdout);
    f>>nn>>mm;

    for(int i=0;i<nn;i++){
        int x,y;
        f>>x>>y;
        points.push_back({x,y});
        check_centrala[make_pair(x,y)]=true;
    }

    for(int i=0;i<mm;i++){
        int x,y;
        f>>x>>y;
        points.push_back({x,y});
        check_centrala[make_pair(x,y)]=false;
    }
    double dtotal = minCostConnectPoints(points);
    printf("%.6lf", dtotal);

}

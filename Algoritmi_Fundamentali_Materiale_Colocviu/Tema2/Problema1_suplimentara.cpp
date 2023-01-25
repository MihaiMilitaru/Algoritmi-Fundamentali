#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    map< pair<int, int>, pair<int, int>> parent;
    map< pair<int, int>, int> height;

    // comparam tuplurile de forma (nod1, nod2, distanta_de_la_nod1_la_nod2) dupa a 3-a componenta din tuplu
    static bool cmp(tuple<pair<int, int>, pair<int, int>, int> &a, tuple<pair<int, int>, pair<int, int>, int> &b){
        return get<2>(a) < get<2>(b);
    }


    // cautam stramosul perechei x
    pair<int, int> reprez(pair<int, int> x){
        if(parent[x]==x){
            return x;
        }
        parent[x]=reprez(parent[x]);
        return parent[x];
    }

    // facem reuniune de arbori dupa reprezentantii perechiilor x si y
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
        int costt=0;
        vector <tuple<pair<int, int>, pair<int, int>, int>> perechi;

        // punem in vectorul perechi tuplurile de forma (nod1, nod2, distanta_de_la_nod1_la_nod2)

        for(int i=0;i<points.size()-1;i++){
            for(int j=i+1;j<points.size();j++){
                int dist = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
                tuple<pair<int, int>, pair<int, int>, int> pereche={make_pair(points[i][0], points[i][1]), make_pair(points[j][0], points[j][1]),dist };
                perechi.push_back(pereche);
            }
        }

        // sortam crescator dupa distanta
        sort(perechi.begin(), perechi.end(),cmp);

        int m= perechi.size();
        int n=points.size();

        // initializam prima data vectorul de tati aka stramosi cu aceleasi valori
        for(int i=0;i<n;i++){
            parent[make_pair(points[i][0], points[i][1])]=make_pair(points[i][0], points[i][1]);
        }

        for(int i=0;i<m;i++){

            // daca avem acelasi stramos dam skip
            if(reprez(get<0>(perechi[i])) == reprez(get<1>(perechi[i]))){
                continue;
            }

            // altfel facem reuniune de arbori disjuncti si actualizam costul
            unite(get<0>(perechi[i]), get<1>(perechi[i]));
            costt+=get<2>(perechi[i]);
        }

        return costt;

    }
};

int main(){
    vector<vector<int>> points = {{0,0},{2,2},{3,10},{5,2},{7,0}};
    Solution s;
    cout<<s.minCostConnectPoints(points);
}
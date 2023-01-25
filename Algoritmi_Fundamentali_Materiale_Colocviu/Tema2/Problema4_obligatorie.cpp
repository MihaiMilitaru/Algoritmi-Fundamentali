#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // retinem perechi de forma (nod, cost_ca_sa_ajung_la_nod)
    double dijkstra(vector<vector<pair<int,double>>> graph, int start, int end)
    {
        // vector de distante pentru fiecare nod
        vector<double> dist(graph.size(),0);

        // coada de prioritati in care bagam perechi de forma (nod, cost_ca_sa_ajung_la_nod)
        priority_queue<pair<int, double>> pq;

        // punem in coada nodul de start cu costul 1; elementul neutru ptr inmultire
        pq.push({ start,1 });

        // distanta ca sa ajungem in nodul de start este tot 1; elementul neutru ptr inmultire
        dist[start] = 1;
        while (pq.size()) {

            //scoatem din coada primul nod
            int node = pq.top().first;
            pq.pop();
            for (auto x : graph[node])
                // mergem prin lista de adiacenta a nodului scos din coada si relaxam muchiile
                // daca se poate relaxa muchia atunci bagam nodul adiacent in coada
                if (dist[node] * x.second > dist[x.first])
                {
                    dist[x.first] = dist[node] * x.second;
                    pq.push({ x.first,dist[x.first] });
                }
        }
        return dist[end];
    }

    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int endd) {
        vector<vector<pair<int, double>>> graph(n, vector<pair<int,double>>(0));
        for (int i = 0; i < edges.size(); i++)
        {
            pair<int, double> x, y;
            x.first = edges[i][1];
            x.second = succProb[i];
            y.first = edges[i][0];
            y.second = succProb[i];
            graph[edges[i][0]].push_back(x);
            graph[edges[i][1]].push_back(y);
        }
        return dijkstra(graph, start, endd);
    }
};

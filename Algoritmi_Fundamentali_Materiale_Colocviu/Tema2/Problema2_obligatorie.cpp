#include <iostream>
#include <fstream>
using namespace std;
ifstream f("disjoint.in");
ofstream g("disjoint.out");
int N, M;
int* tata;
int* h;

//gasim stramosul aka reprezentantul nodului nod

int Find(int nod)
{
    if(tata[nod] == 0) {
        return nod;
    }
    return tata[nod] = Find(tata[nod]);

}

// gasim stramosii lui x si y si reunim arborii

void Union(int x, int y) {

    int tataX = Find(x);
    int tataY = Find(y);

    if(h[tataX] > h[tataY]) {
        tata[tataY] = tataX;
    } else if(h[tataX] < h[tataY]) {
        tata[tataX] = tataY;
    } else {
        tata[tataY] = tataX;
        h[tataX]++;
    }
}
int main()
{
    f>>N>>M;

    tata = new int[N+1];
    h = new int[N+1];

    for(int i = 0; i<= N; i++) {
        tata[i] = 0;
        h[i] = 1;
    }
    int ctr =N;

    for(int i = 1; i <= M; i++) {
        int cod, x, y;
        f>> cod >> x >> y;
        if(cod == 1) {
            Union(x, y);
            ctr--;
            cout<<ctr<<" multimi ramase"<<"\n";
        }
        else if(cod == 2) {
            if (Find(x)== Find(y))
                g<<"DA\n";
            else{
                g<<"NU\n";

            }

        }
    }

    return 0;
}

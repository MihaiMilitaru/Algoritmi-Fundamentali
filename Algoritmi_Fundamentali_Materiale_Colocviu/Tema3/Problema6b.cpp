#include <bits/stdc++.h>

using namespace std;

string shortestCommonSupersequence(string str1, string str2) {
    int n=str1.size();
    int m=str2.size();
    vector<vector<int>> t(n+1,vector<int>(m+1,0));
    // ne construim matricea in care gasim lungimea celui mai mare substring dintre cele doua cuvinte

    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(str1[i-1]==str2[j-1])
            {
                t[i][j] = 1 + t[i-1][j-1];
            }
            else {
                t[i][j] = max(t[i-1][j],t[i][j-1]);
            }
        }
    }

    string res="";
    int i=n,j=m;
    // plecam de la finalul cuvintelor si verificam cat de similare sunt cuvintele elimind pe rand ultima litera de la fiecare cuvant
    // unde exista similaritate maxima inseamna ca litera eliminata pentru acel caz va fi pastrata in noul string
    // continuam procesul pana eliminam fiecare litera
    // daca s-au eliminat toate literele unui cuvant se vor copia direct literele ramase de la celalalt cuvant
    while(i>0 && j>0)
    {
        if(str1[i-1]==str2[j-1])
        {
            res+=str1[i-1];
            i--;
            j--;
        }

        else if(t[i-1][j]>t[i][j-1])
        {
            res+=str1[i-1];
            i--;
        }
        else {
            res+=str2[j-1];
            j--;
        }
    }

    while(i>0)
    {
        res+=str1[i-1];
        i--;
    }
    while(j>0)
    {
        res+=str2[j-1];
        j--;
    }
    reverse(res.begin(),res.end());
    return res;
}

int main() {
    string str1 = "abac";
    string str2 = "cab";
    cout << shortestCommonSupersequence(str1, str2) << endl;
    return 0;
}
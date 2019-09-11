//PT07Z - Sol by Taku

#include <bits/stdc++.h>

using namespace std;

const int N = 10005;

int d[N], n;
bool ok[N];
vector <int> a[N];

void DFS(int u){
    int ma1 = 0, ma2= 0;
    ok[u] = 1;
    d[u] = 1;
    for (int i = 0; i<a[u].size(); i++){
        int v = a[u][i], t = 0;
        if (!ok[v]){
            DFS(v);
            t += d[v];
            if (t >= ma1) {
                ma2 = ma1;
                ma1 = t;
            }
            else ma2 = max(t, ma2);
        }
    }
    d[u] =
}

int main(){
    cin>>n;
    for (int i = 1; i<n;i++){
        int u, v;
        cin>>u>>v;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    DFS(1);
}

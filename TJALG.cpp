// Tim thanh phan lien thong manh - Sol by Taku
// 05.09.2019

#include <bits/stdc++.h>

using namespace std;

const int N = 1e4 + 5;

vector <int> a[N];

int cnt = 0, low[N], child = 0, num[N], m, n, kk1 = 0, kk2 = 0, parent[N], root;
bool onstack[N];
stack <int> pq;

void DFS(int u){
    pq.push(u);
    low[u] = ++cnt;
    num[u]= low[u];
    onstack[u] = true;
    for (int i = 0; i<a[u].size(); i++){
        int v = a[u][i];
        if (num[v] == 0) DFS(v);
        if (onstack[v]) low[u] = min(low[u], low[v]);
    }
    if (num[u] == low[u]){
        ++kk1;
        while (true){
            int v = pq.top();
            onstack[v] = false;
            pq.pop();
            if ( v == u) break;
        }
    }
}

int main(){
    cin>>n>>m;
    for (int i = 1; i<=m; i++){
        int u, v;
        cin>>u>>v;
        a[u].push_back(v);
     //   a[v].push_back(u);
    }
    for (int i = 1; i<=n; i++)
        if (num[i] == 0) DFS(i);
    cout<<kk1;
}

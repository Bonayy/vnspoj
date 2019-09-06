// Tim khop va cau - Sol by Taku
// 05.09.2019

#include <bits/stdc++.h>

using namespace std;

const int N = 1e4 + 5;

vector <int> a[N];

int cnt = 0, low[N], child = 0, num[N], m, n, kk1 = 0, kk2 = 0, parent[N], root;

void DFS(int u){
    low[u] = ++cnt;
    num[u]= low[u];
    for (int i = 0; i<a[u].size(); i++){
        int v = a[u][i];
        if (num[v] != 0){
            if (parent[u] != v) low[u] = min(low[u], num[v]);
        }
        else{
            parent[v] = u;
            if (u == root) child++;
            DFS(v);
            low[u] = min(low[u], low[v]);
            if (low[v] >= num[u]) kk1 ++;
            if (low[v] > num[u]) kk2++;
        }
    }
}

int main(){
    cin>>n>>m;
    for (int i = 1; i<=m; i++){
        int u, v;
        cin>>u>>v;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    for (int i = 1; i<=n; i++){
        if (num[i] == 0){
            root = i;
            child = 0;
            DFS(i);
            if (child > 1) kk1 ++;
        }
    }
    cout<<kk1<<" "<<kk2;
}

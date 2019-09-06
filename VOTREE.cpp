// VOTREE - Sol by Taku
// 04.09.2019

#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 7;

int h[N], cha[N], n, q, u, v;
int F[N][20], it[4 * N];

vector <int> a[N];

void DFS(int i){
    for (int j = 0; j < a[i].size(); j++){
        if (cha[a[i][j]] == -1){
            cha[a[i][j]] = i;
            h[a[i][j]] = h[i] + 1;
            DFS(a[i][j]);
        }
    }
}

void buildlca(){
    for (int i = 1; i<=n; i++) F[i][0] = cha[i];
    for (int j = 1; j <= 17; j++)
        for (int i = 1; i<=n; i++)
            if (F[i][j - 1] != -1){
                F[i][j] = F[F[i][j-1]][j-1];
            }
}

int LCA(int u, int v){
    if (h[u] < h[v]) swap(u, v);
    for (int i = 17; i >= 0; i--)
        if ((h[u] - (1 << i)) >= h[v]) u = F[u][i];
    if (u == v) return u;
    for (int i = 17; i >= 0; i--)
        if (F[u][i] != -1 && F[u][i] != F[v][i]){
            u = F[u][i];
            v = F[v][i];
        }
    return cha[u];
}

void build (int id, int l, int r){
    if (l == r){
        it[id] = l;
        return;
    }
    int mid = (l+ r)/2;
    build (id* 2, l , mid);
    build (id * 2+ 1, mid +1, r);
    it[id] = LCA(it[id*2], it[id*2+1]);
}

int get(int id, int l, int r, int u, int v){
    if (v < l || r <u) return -1;
    if (u <=l && r <=v) return it[id];
    int mid = (l + r)/2;
    int t1 = get(id*2 , l, mid, u, v);
    int t2 = get(id*2 + 1 , mid + 1, r, u, v);
    if (t1 !=-1 && t2 !=-1) return LCA (t1, t2);
    if (t1 !=-1) return LCA(t1);
    if (t2 !=-1) return LCA(t2);
}

int main(){
    cin>>n>>q;
    for (int i = 1; i<n; i++){
        cin>>u>>v;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    memset(cha, -1, sizeof(cha));
    memset(F, -1, sizeof(F));
    cha[1] = 1;
    h[1] = 1;
    DFS(1);
    buildlca();
    build(1, 1, n);
    for (int i = 1; i<=q; i++){
        cin>>u>>v;
        cout<<get(1, 1, n, u, v)<<"\n";
    }
}

// KBUILD - Sol by Taku
// 05.09.2019

#include <bits/stdc++.h>

using namespace std;

const int N = 200005;
vector <int> a[N];

struct Td{
    int val;
    int lazy;
};

int h[N], nChild[N], nChain = 1, chain[N], pos[N], chainhead[N],kk = 0 , p = 0;
int n, q, F[N][30];
Td it[4 * N];

void DFS(int u){
    nChild[u] = 1;
    for (int j = 0; j < a[u].size(); j++){
        int v = a[u][j];
          if (v != F[u][0]){
            h[v] = h[u] + 1;
            F[v][0] = u;
            DFS(v);
            nChild[u] += nChild[v];
        }
    }
}

void HLD(int u){
    if (chainhead[nChain] == 0) chainhead[nChain] = u;
    chain[u] = nChain;
    pos[u] = ++kk;
    int MaxV = -1;
    for (int i = 0; i < a[u].size(); i++){
        int v = a[u][i];
        if (v != F[u][0]){
            if (MaxV == -1 || nChild[v] > nChild[MaxV]) MaxV = v;
        }
    }
    if (MaxV > -1) HLD (MaxV);
    for (int i = 0; i< a[u].size(); i++){
        int v = a[u][i];
        if (v != F[u][0] && v != MaxV){
            nChain++;
            HLD(v);
        }
    }
}

void down (int id){
    if (it[id].lazy == 0) return;
    it[id * 2 + 1].val = 0;
    it[id *2 ].val = 0;
    it[id *2 +1].lazy =1;
    it[id *2].lazy = 1;
   // it[id].lazy = 0;
}

void updateit(int id, int l, int r, int u, int v){
    if ( v < l || r < u) return ;
    if ( u <= l && r <=v) {
        it[id].val = 0;
        it[id].lazy = 1;
        return;
    }
    int mid = (l + r)/2;
    down (id);
    updateit(id *2 , l, mid, u, v);
    updateit(id *2 +1 , mid +1 , r, u, v);
    it[id].val = it[id*2].val + it[id*2+1].val;
}

void update (int u, int v) {
     while (chain[u] != chain[v]){
        if (h[chainhead[chain[u]]] > h[chainhead[chain[v]]] ){
            updateit(1, 1 ,n, pos[chainhead[chain[u]]], pos[u]);
            u = F[chainhead[chain[u]]][0];
        }
        else{
            updateit(1, 1 ,n, pos[chainhead[chain[v]]], pos[v]);
            v = F[chainhead[chain[v]]][0];
        }
     }
     if (h[u] < h[v]) updateit(1, 1, n, pos[u] + 1, pos[v]);
     else updateit(1, 1, n, pos[v] + 1, pos[u]);
}

void build (int id, int l, int r){
    if (l == r){
        it[id].val = 1;
        it[id].lazy = 0;
        if (l == 1) it[id].val = 0;
        return;
    }
    int mid = (l + r)/2;
    build (id * 2, l, mid);
    build (id * 2 + 1, mid + 1, r);
    it[id].val = it[id*2].val + it[id*2+1].val;
    it[id].lazy = 0;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    freopen("HLD.INP", "r", stdin);
    freopen("HLD.OUT", "w", stdout);
    memset(F, -1, sizeof(F));
    cin>>n;
    for (int i = 1; i< n; i++){
        int u, v;
        cin>>u>>v;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    F[1][0] = 1;
    h[1] = 1;
    DFS(1);
    HLD(1);
    build (1,1, n);
    cin>>q;
    while (q--){
        int x, y;
        cin>>x>>y;
        update(x, y);
    }
    cout<<it[1].val;
}

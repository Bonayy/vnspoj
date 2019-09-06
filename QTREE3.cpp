// HLD - Sol by Taku
// 04.09.2019

#include <bits/stdc++.h>

using namespace std;

const int N = 100005;
const int INF = 1000005;

vector <int> a[N];

int h[N], parent[N], nChild[N], nChain = 1, chain[N], pos[N], chainhead[N],kk = 0 , p = 0;
int n, q, TOPO[N], NUM[N];
int it[4 * N];

void DFS(int u){
    TOPO[u] = ++p;
    NUM[p] = u;
    nChild[u] = 1;
    for (int j = 0; j < a[u].size(); j++){
        int v = a[u][j];
        if (parent[v] == -1) {
            parent[v] = u;
            h[v] = h[u] + 1;
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
        if (v != parent[u]){
            if (MaxV == -1 || nChild[v] > nChild[MaxV]) MaxV = v;
        }
    }
    if (MaxV > -1) HLD (MaxV);
    for (int i = 0; i< a[u].size(); i++){
        int v = a[u][i];
        if (v != parent[u] && v != MaxV){
            nChain++;
            HLD(v);
        }
    }
}

void updateit(int id, int l, int r, int x, int val){
    if ( x < l || r < x) return ;
    if (l == r){
        if (it[id] != val) it[id] = val;
        else it[id] = 1e9;
        return;
    }
    int mid = (l + r)/2;
    updateit(id *2 , l, mid, x, val);
    updateit(id *2 +1 , mid +1 , r, x, val);
    it[id] = min(it[id*2], it[id*2+1]);

}

int getit(int id, int l, int r, int u, int v){
    if ( l > v || u > r) return 1e9;
    if (u <= l && r <=v ) return it[id];
    int mid = (l + r)/2;
    return min(getit(id *2, l, mid, u, v) , getit(id *2 +1, mid +1, r, u, v ));
}

void get(int u) {
     int uchain = chain[u];
     int ans = 1e9;
     while (uchain != 1){
        ans = min(ans, getit(1,1 ,n, pos[chainhead[uchain]], pos[u]));
        u = parent[chainhead[uchain]];
        uchain = chain[u];
     }
     ans = min(ans, getit(1,1,n, 1, pos[u]));
     if (ans == 1e9) cout<<-1<<"\n";
     else cout<<NUM[ans]<<"\n";
}

int main(){
    freopen("HLD.INP", "r", stdin);
    freopen("HLD.OUT", "w", stdout);
    memset(parent, -1, sizeof(parent));
    cin>>n>>q;
    for (int i =1 ; i <= 4*n; i++) it[i] = 1e9;
    for (int i = 1; i< n; i++){
        int u, v;
        cin>>u>>v;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    parent[1] = 1;
    h[1] = 1;
    DFS(1);
    HLD(1);
    while (q--){
        int x, y;
        cin>>x>>y;
        if (x == 1) get(y);
        else updateit(1, 1, n, pos[y], TOPO[y]);
    }
}

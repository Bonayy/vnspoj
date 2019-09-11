// QTREEX - Sol by Taku
// 08.09.2019

#include <bits/stdc++.h>
#define X first
#define Y second

using namespace std;

typedef pair <int, int> ii;

const int INF = 1e9;
const int N = 10005;
vector <ii> a[N];

struct Td{
    int vmax;
    int vmin;
    int lazy;
};

int h[N], nChild[N], nChain = 1, chain[N], pos[N], chainhead[N],kk = 0 , p = 0;
int n, q, F[N][30], val[N], u[N], v[N], w[N];
Td it[4 * N];

void DFS(int u){
    nChild[u] = 1;
    for (int j = 0; j < a[u].size(); j++){
        int v = a[u][j].X;
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
        int v = a[u][i].X;
        if (v != F[u][0]){
            if (MaxV == -1 || nChild[v] > nChild[MaxV]) MaxV = v;
        }
    }
    if (MaxV > -1) HLD (MaxV);
    for (int i = 0; i< a[u].size(); i++){
        int v = a[u][i].X;
        if (v != F[u][0] && v != MaxV){
            nChain++;
            HLD(v);
        }
    }
}

void down (int id){
    if (it[id].lazy % 2 == 1){
        swap(it[id * 2].vmin, it[id*2].vmax);
        it[id * 2].vmin = - it[id * 2].vmin;
        it[id * 2].vmax = - it[id * 2].vmax;
        swap(it[id * 2 + 1].vmin, it[id*2 + 1].vmax);
        it[id * 2 + 1].vmin = - it[id * 2 + 1].vmin;
        it[id * 2 + 1].vmax = - it[id * 2 + 1].vmax;
    }
    it[id *2].lazy += it[id].lazy;
    it[id *2 + 1].lazy += it[id].lazy;
    it[id].lazy = 0;
    return;
}

void updateit(int id, int l, int r, int u, int v){
    if ( v < l || r < u) return ;
    if ( u <= l && r <=v) {
        swap(it[id].vmin, it[id].vmax);
        it[id].vmin = - it[id].vmin;
        it[id].vmax = - it[id].vmax;
        it[id].lazy ++;
        return;
    }
    int mid = (l + r)/2;
    down (id);
    updateit(id *2 , l, mid, u, v);
    updateit(id *2 +1 , mid +1 , r, u, v);
    it[id].vmin = min(it[id*2].vmin , it[id*2+1].vmin);
    it[id].vmax = max(it[id*2].vmax , it[id*2+1].vmax);
}

void change(int id, int l, int r, int x , int val){
    if (x < l || x > r) return;
    if (l == r) {
        it[id].vmax = val;
        it[id].vmin = val;
        return;
    }
    int mid = (l + r)/2;
    down(id);
    change(id * 2, l, mid, x, val);
    change(id*2 + 1, mid +1 , r , x , val);
    it[id].vmax = max(it[id*2].vmax, it[id * 2 + 1].vmax);
    it[id].vmin = min(it[id*2].vmin, it[id * 2 + 1].vmin);
}

void update (int u, int v) {
     while (chain[u] != chain[v]){
        if (h[chainhead[chain[u]]] > h[chainhead[chain[v]]] ){
            updateit(1, 2 ,n, pos[chainhead[chain[u]]], pos[u]);
            u = F[chainhead[chain[u]]][0];
        }
        else{
            updateit(1, 2 ,n, pos[chainhead[chain[v]]], pos[v]);
            v = F[chainhead[chain[v]]][0];
        }
     }
     if (h[u] < h[v]) updateit(1, 2, n, pos[u] + 1, pos[v]);
     else updateit(1, 2, n, pos[v] + 1, pos[u]);
}

int getit(int id, int l, int r, int x, int y){
    if (r < x || l > y) return -INF;
    if ( x <=l && r <=y) return it[id].vmax;
    down(id);
    int mid = (l + r)/2;
    return max(getit(id * 2, l, mid, x, y), getit(id *2 + 1, mid +1, r, x, y));
}

void get (int u, int v){
    int ans = -INF;
    while (chain[u] != chain[v]){
        if (h[chainhead[chain[u]]] > h[chainhead[chain[v]]] ){
            ans = max(ans, getit(1, 2 ,n, pos[chainhead[chain[u]]], pos[u]));
            u = F[chainhead[chain[u]]][0];
        }
        else{
            ans = max(ans, getit(1, 2 ,n, pos[chainhead[chain[v]]], pos[v]));
            v = F[chainhead[chain[v]]][0];
        }
     }
     if (h[u] < h[v]) ans = max(ans, getit(1, 2, n, pos[u] + 1, pos[v]));
     else ans = max (ans, getit(1, 2, n, pos[v] + 1, pos[u]));
     cout<<ans<<"\n";
}

void build (int id, int l, int r){
    if (l == r){
        it[id].vmin = val[l];
        it[id].vmax = val[l];
        it[id].lazy = 0;
        return;
    }
    int mid = (l + r)/2;
    build (id * 2, l, mid);
    build (id * 2 + 1, mid + 1, r);
    it[id].vmin = min(it[id*2].vmin , it[id*2+1].vmin);
    it[id].vmax = max(it[id*2].vmax , it[id* 2 + 1].vmax);
    it[id].lazy = 0;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    freopen("QTREEX.inp", "r", stdin);
    freopen("QTREEX.out", "w", stdout);
    int TT;
    cin>>TT;
    while (TT--){
        memset(F, -1, sizeof(F));
        cin>>n;
        for (int i = 1; i<=n; i++){
            a[i].clear();
            nChild[i] = 0;
            nChain = 1;
            chain[i] = 0;
            pos[i] = 0;
            chainhead[i] = 0;
            kk = 0;
            p = 0;
        }
        for (int i = 1; i< n; i++){
            cin>>u[i]>>v[i]>>w[i];
            a[u[i]].push_back(ii(v[i], w[i]));
            a[v[i]].push_back(ii(u[i], w[i]));
        }
        F[1][0] = 1;
        h[1] = 1;
        DFS(1);
        HLD(1);
        for (int i = 2; i<=n; i++){
            if (a[i][0].X == F[i][0]) val[pos[i]] = a[i][0].Y;
            else val[pos[i]] = a[i][1].Y;
        }
        build (1, 2, n);
        int x, y;
        string ss;
        while (1==1){
            cin>>ss;
            if (ss== "DONE") break;
            cin>>x>>y;
            if (ss == "CHANGE"){
                if (u[x] == F[v[x]][0]) change(1,2,n, pos[v[x]], y);
                else change(1,2,n, pos[u[x]], y);
            }
            if (ss == "NEGATE" && x != y) update(x, y);
            if (ss == "QUERY"){
                if (x == y) cout<<0<<"\n";
                else get(x, y);
            }
        }
    }
    return 0;
}

// HLD - Sol by Taku
// 04.09.2019

#include <bits/stdc++.h>
#define X first
#define Y second

using namespace std;

const int N = 100005;
const int INF = 1000005;

typedef pair <int, int> ii;

struct Td{
    int u;
    int v;
    int c;
};

vector <ii> a[N];
Td cc[N];
int h[N], parent[N], n, F[N][20];
int  u[N],  v[N] , pos[N], nChain = 1, chain[N], chainhead[N], kk = 0, nChild[N], x, y, q, Value[N], Value2[N];
ii it[4 * N];

void DFS(int i){
    bool ok = false;
    for (int j = 0; j < a[i].size(); j++){
        int v = a[i][j].X;
        if (parent[v] == -1) {
            parent[v] = i;
            Value[v] = a[i][j].Y;
            h[v] = h[i] + 1;
            DFS(v);
            nChild[i] += nChild[v];
            ok = true;
        }
    }
    if (!ok) nChild[i] = 1;
}

void buildLCA(){
    for (int i = 1; i<=n; i++) F[i][0] = parent[i];
    for (int j = 1; j <=17; j++)
        for (int i = 1; i<=n; i++)
            if (F[i][j-1] != -1) F[i][j] = F[F[i][j-1]][j-1];
}

int LCA(int u, int v){
    if (h[u] < h[v]) swap (u, v);
    for (int j = 17; j >=0; j--)
        if ((h[u] - (1 << j)) >= h[v]) u = F[u][j];
    if (u == v) return u;
    for (int j = 17; j >=0; j--)
        if (F[u][j]!=-1 && F[u][j] != F[v][j]){
            u = F[u][j];
            v = F[v][j];
        }
    return parent[u];
}

void HLD(int u){
    if (chainhead[nChain] == 0) chainhead[nChain] = u;
    chain[u] = nChain;
    pos[u] = ++kk;
    int MaxV = -1;
    for (int i = 0; i < a[u].size(); i++){
        int v = a[u][i].X;
        if (v != parent[u]){
            if (MaxV == -1 || nChild[v] > nChild[MaxV]) MaxV = v;
        }
    }
    if (MaxV > -1) HLD (MaxV);
    for (int i = 0; i< a[u].size(); i++){
        int v = a[u][i].X;
        if (v != parent[u] && v != MaxV){
            nChain++;
            HLD(v);
        }
    }
}

void updateit(int id, int l, int r, int u, int v, int val){
    if (v < l || r < u) return ;
    if (u <=l && r <=v) {
        it[id].X = min(it[id].X, val);
        it[id].Y = max(it[id].Y, val);
        return;
    }
    int mid = (l + r)/2;
    updateit(id *2 , l, mid, u, v, val);
    updateit(id *2 +1 , mid +1 , r, u, v, val);
    it[id].X = min(it[id * 2].X , it[id * 2 + 1].X);
    it[id].Y = max(it[id * 2].Y , it[id * 2 + 1].Y);
}

ii getit(int id, int l, int r, int u, int v){
    if (v < l || r < u){
        ii t;
        t.X = INF;
        t.Y = 0;
        return t;
    }
    if (u <=l && r <=v) return it[id];
    int mid = (l + r)/2;
    ii t1 = getit(id *2 , l, mid, u, v);
    ii t2 = getit(id *2 +1, mid + 1, r, u, v);
    ii ans;
    ans.X = min(t1.X, t2.X);
    ans.Y = max(t1.Y, t2.Y);
    return ans;
}

/*void update(int u, int a, int val) {
     int uchain = chain[u], achain = chain[a];
     while (1 == 1) {
          if (uchain == achain) {
               updateit(1, 1, n, pos[a], pos[u], val);
               break;
          }
          updateit(1, 1, n , pos[chainhead[uchain]], pos[u], val);
          u = parent[chainhead[uchain]];
          uchain = chain[u];
     }
}*/

ii get(int u, int a) {
     int uchain = chain[u], achain = chain[a];
     ii ans;
     ans.X = INF;
     ans.Y = 0;
     while (1 == 1) {
          if (uchain == achain) {
               if (h[a] < h[u]){
                    ans.X = min(ans.X , getit(1, 1, n, pos[a]+1, pos[u]).X);
                    ans.Y = max(ans.Y , getit(1, 1, n, pos[a]+1, pos[u]).Y);
               }
               else{
                    ans.X = min(ans.X , getit(1, 1, n, pos[u]+1, pos[a]).X);
                    ans.Y = max(ans.Y , getit(1, 1, n, pos[u]+1, pos[a]).Y);
               }
               break;
          }
          ii ttt = getit(1, 1, n , pos[chainhead[uchain]], pos[u]);
          ans.X = min(ans.X, ttt.X);
          ans.Y = max(ans.Y, ttt.Y);
          u = parent[chainhead[uchain]];
          uchain = chain[u];
     }
     return ans;
}

void build (int id, int l, int r){
    if (l == r){
        it[id].X = Value2[l];
        it[id].Y = Value2[l];
        if (l == 1){
            it[id].X = INF;
            it[id].Y = 0;
        }
        return;
    }
    int mid = (l+ r)/2;
    build (id *2 , l , mid);
    build (id *2 + 1, mid +1 , r);
    it[id].X = min(it[id*2].X , it[id*2+1].X);
    it[id].Y = max(it[id*2].Y , it[id*2+1].Y);
}


int main(){
    freopen("HLD.INP", "r", stdin);
    freopen("HLD.OUT", "w", stdout);
    cin>>n;
    for (int i = 1; i< n; i++){
        cin>>cc[i].u>>cc[i].v>>cc[i].c;
        a[cc[i].u].push_back(ii(cc[i].v, cc[i].c));
        a[cc[i].v].push_back(ii(cc[i].u, cc[i].c));
    }
    memset(F, -1, sizeof(F));
    memset(parent, -1, sizeof(parent));
    parent[1] = 1;
    h[1] = 1;
    Value[1] = 0;
    DFS(1);
    buildLCA();
    HLD(1);
    for (int i = 1; i<=n; i++) Value2[pos[i]] = Value[i];
    build (1, 1, n);
    cin>>q;
    while (q --){
        cin>>x>>y;
        int ll = LCA(x, y);
        ii k1 = get(x, ll);
        ii k2 = get(y, ll);
        cout<<min(k1.X, k2.X)<<" "<<max(k1.Y, k2.Y)<<"\n";
    }
}

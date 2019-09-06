#include <bits/stdc++.h>

using namespace std;

const int N = 200010;

vector <int> C[N/2];
vector <int> a[N];

int F[N][20], h[N], n, k;

int kk;

void DFS(int u){
    for (int j = 0; j < a[u].size(); j++){
        int v = a[u][j];
          if (v != F[u][0]){
            h[v] = h[u] + 1;
            F[v][0] = u;
            DFS(v);
        }
    }
}

void buildlca(){
    for (int j = 1; (1 << j) < n; j++)
        for (int i = 1; i<=n; i++)
            if (F[i][j - 1] != -1) F[i][j] = F[F[i][j-1]][j-1];
}

int LCA(int u, int v){
    if (h[u] < h[v]) swap(u, v);
    int Log = 0;
    for(; 1 << Log <= h[u]; ++Log); --Log;
    for (int i = Log; i >= 0; i--)
        if ((h[u] - (1 << i)) >= h[v]) u = F[u][i];
    if (u == v) return u;
    if (u != v){
        for (int i = Log; i >= 0; i--)
            if (F[u][i] != -1 && F[u][i] != F[v][i]){
                u = F[u][i];
                v = F[v][i];
            }
    }
    return F[u][0];
}


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
  //  freopen("HLD.INP", "r", stdin);
 //   freopen("HLD.OUT", "w", stdout);
    cin>>n>>k;
    for (int i = 1; i<=n; i++){
        int u, v;
        cin>>u>>v;
        a[i].push_back(v);
        a[v].push_back(i);
        C[u].push_back(i);
        if (v == 0) kk = i;
    }
    memset(F, -1, sizeof(F));
    F[kk][0] = kk;
    h[kk] = 1;
    DFS(kk);
    buildlca();
    int res, u, v, p, deeperest;
    for (int i = 1; i <=k; i++){
        res = 0;
        deeperest = C[i][0];
        for (int j = 1;  j < C[i].size(); j++){
            u = C[i][j];
            if (h[u] > h[deeperest]) deeperest = u;
        }
        for (int j = 0; j < C[i].size(); j++){
            u = C[i][j];
            p = LCA(u, deeperest);
        //    cout<<u<<" "<<deeperest<<" "<<p<<"\n";
            res = max(res, h[u] + h[deeperest] - h[p] - h[p]);
        }
        cout<<res<<"\n";
    }
}

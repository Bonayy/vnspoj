#include <bits/stdc++.h>
#define X first
#define Y second

using namespace std;

const int N = 1e5 + 7;

typedef pair <int,int> ii;

int h[N], parent[N], n, q, x, y;
int F[N][20], it[4 * N], Wmin[N][20],  Wmax[N][20];

vector <ii> a[N];

void DFS(int u){
    for (int j = 0; j < a[u].size(); j++){
        int v = a[u][j].X;
        int w = a[u][j].Y;
        if (v != F[u][0]){
            h[v] = h[u] + 1;
            F[v][0] = u;
            Wmin[v][0] = w;
            Wmax[v][0] = w;
            DFS(v);
        }
    }
}

void buildlca(){
    for (int j = 1; (1 << j) < n; j++)
        for (int i = 1; i<=n; i++)
            if (F[i][j - 1] != -1){
                F[i][j] = F[F[i][j-1]][j-1];
                Wmin[i][j] = min(Wmin[i][j-1], Wmin[F[i][j-1]][j-1]);
				Wmax[i][j] = max(Wmax[i][j-1], Wmax[F[i][j-1]][j-1]);
            }
}

void LCA(int u, int v){
    if (h[u] < h[v]) swap(u, v);
    int wmin = INT_MAX, wmax = INT_MIN;
    int Log = 0;
    for(; 1 << Log <= h[u]; ++Log); --Log;
    for (int i = Log; i >= 0; i--)
        if ((h[u] - (1 << i)) >= h[v]){
            wmin = min(wmin, Wmin[u][i]);
			wmax = max(wmax, Wmax[u][i]);
            u = F[u][i];
        }
    if (u != v){
        for (int i = Log; i >= 0; i--)
            if (F[u][i] != -1 && F[u][i] != F[v][i]){
                wmin = min(wmin, min(Wmin[u][i], Wmin[v][i]));
				wmax = max(wmax, max(Wmax[u][i], Wmax[v][i]));
                u = F[u][i];
                v = F[v][i];
            }
        wmin = min(wmin, min(Wmin[u][0], Wmin[v][0]));
		wmax = max(wmax, max(Wmax[u][0], Wmax[v][0]));
    }
    cout<<wmin<<" "<<wmax<<"\n";
    return;
}

int main(){
    freopen("HLD.INP", "r", stdin);
    freopen("HLD.OUT", "w", stdout);
    cin>>n;
    for (int i = 1; i<n; i++){
        int u, v, c;
        cin>>u>>v>>c;
        a[u].push_back(ii(v,c));
        a[v].push_back(ii(u,c));
    }
    memset(F, -1, sizeof(F));
    h[1] = 1;
    F[1][0] = 1;
    DFS(1);
    buildlca();
    cin>>q;
    while (q--){
        cin>>x>>y;
        LCA(x, y);
    }

}

// REVAMP - Revamping Trails
// SPOJ - 01.09.2019

#include <bits/stdc++.h>
#define X first
#define Y second

using namespace std;

typedef long long ll;
typedef pair < long long, int> ii;
typedef pair < ii, int > iii;

const int N = 1e5 + 7;
int m, n, k, s, t, x, y;
ll z;
vector <ii> a[N];

void dijsktra(){
    //iii cc;
    priority_queue < iii, vector <iii> , greater <iii> > pq;
    long long d[N][30];
    for (int i = 1; i<=n; i++)
        for (int j = 0; j <= k ; j++) d[i][j] = 1e18;
   	d[s][0] = 0;
    pq.push(iii(ii(0, 0), s));
    while (!pq.empty()){
        int u = pq.top().Y;
        int du = pq.top().X.X;
        int kk = pq.top().X.Y;
        pq.pop();
        if (du != d[u][kk]) continue;
        for (int i = 0; i< a[u].size(); i++){
            int v = a[u][i].Y;
            if (d[v][kk] > d[u][kk] + a[u][i].X){
                d[v][kk] = d[u][kk] + a[u][i].X;
                pq.push(iii(ii(d[v][kk], kk), v));
            }
            if (kk < k){
                if (d[v][kk + 1] > d[u][kk]){
                    d[v][kk + 1] = d[u][kk];
                    pq.push(iii(ii(d[v][kk + 1], kk + 1), v));
                }
            }
        }
    }
    long long res = 1e18;
    for (int i = 0; i<= k; i++) res = min(res, d[t][i]);
    cout<<res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
 //   freopen ("DHFRBUS.INP", "r", stdin);
 //   freopen ("DHFRBUS.OUT", "w", stdout);
    cin>>n>>m>>k>>s>>t;
    for (int i = 1; i<=m ; i++){
        cin>>x>>y>>z;
        a[x].push_back(ii(z, y));
        a[y].push_back(ii(z, x));
    }
   // cout<<k;
    dijsktra();
    return 0;
}

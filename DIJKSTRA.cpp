// DIJKSTRA - Sol by Taku
// 30.08.2019

#include <bits/stdc++.h>
using namespace std;

#define E first
#define W second

typedef pair <int, long long> ii;

const int N = 1e5 + 7;

vector <ii> a[N];
int u, v, n , m;
long long w;

void dijkstra(){
    priority_queue <ii , vector <ii>, greater<ii> > pq;
    long long d[N];
    for (int i = 1; i <= n; i++) d[i] = -1;
    d[1] = 0;
    pq.push(ii(0, 1));
    while (!pq.empty()){
        u = pq.top().E;
        w = pq.top().W;
        if (d[u] != w) continue;
        for (int i = 0; i < a[u].size(); i++){
            if (d[a[u][i].E] > d[u] + a[u][i].W){
                d[a[u][i].E] = d[u] + a[u][i].W;
                pq.push(ii(d[a[u][i].E], a[u][i].E));
            }
        }
    }
    cout<<d[n];
}

int main(){
    cin>>n>>m;
    for (int i = 1; i<=m; i++){
        cin>>u>>v>>w;
        a[u].push_back(ii(v, w));
        a[v].push_back(ii(u, w));
    }
    dijkstra();
    return 0;
}

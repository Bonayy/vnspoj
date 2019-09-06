// SUMS - Sol by Taku
// SPOJ

#include <bits/stdc++.h>
using namespace std;

#define X first
#define Y second

const int INF = 1e9 + 7;
const int N = 50005;
typedef pair <long long, int> ii;

int a[N], n, m;
long long d[N], b;


void dijkstra(){
    for (int i = 0; i < a[1]; i++) d[i] = - 1;
    d[0] = 0;
    priority_queue < ii, vector <ii>, greater<ii> > pq;
    pq.push(ii(0, 0));
    while (!pq.empty()){
        int u = pq.top().Y;
        long long du = pq.top().X;
        pq.pop();
        if (d[u] != du) continue;
        for (int i = 2; i <= n; i++){
            if (d[(u + a[i])% a[1]] > d[u] + a[i] || d[(u + a[i]) % a[1]] == -1){
                d[(u + a[i]) % a[1]] = d[u] + a[i];
                pq.push(ii(d[(u + a[i])% a[1]], (u + a[i]) % a[1]));
            }
        }
    }
}

int main(){
    cin>>n;
    for (int i = 1; i<=n; i++) cin>>a[i];
    sort(a+1, a+1+n);
    dijkstra();
    cin>>m;
    while (m--){
        cin>>b;
        if (b >= d[b % a[1]] && d[b % a[1]] != -1) cout<<"TAK"<<"\n";
        else cout<<"NIE"<<"\n";
    }
}

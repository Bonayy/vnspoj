// MELE 2 - Sol by Taku
// SPOJ
// 31.08.2019

#include <bits/stdc++.h>
using namespace std;

#define X first
#define Y second

const int INF = 1e9 + 7;
const int N = 100005;
typedef pair <long long, int> ii;

int n, m;
long long d[N], b, a[5], h, res = 0;


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
    cin>>h;
    n  = 3;
    for (int i = 1; i<=3; i++) cin>>a[i];
    sort(a+1, a+1+n);
    dijkstra();
    for (int i = 0 ; i < a[1]; i++){
        if (d[i] != -1 && d[i] <= h) res = res + (h - d[i] - 1)/a[1] + 1;
    }
    cout<<res;
}

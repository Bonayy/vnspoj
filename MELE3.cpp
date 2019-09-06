// MELE3 - Sol by Taku
// SPOJ

#include <bits/stdc++.h>

using namespace std;

const int N = 1005;

typedef pair <int , int> ii;

int k, n, x, y, duu;
vector <int> a[N];
int d[N];

void dijsktra(){
    for (int i = 1; i<=n; i++) d[i] = -1;
    d[1] = 0;
    priority_queue < ii , vector <ii>, greater <ii> > pq;
    pq.push(ii (0, 1));
    while (!pq.empty()){
        int u = pq.top().second;
        int du = pq.top().first;
        pq.pop();
        if (d[u] != du) continue;
        for (int i = 0; i<a[u].size(); i++){
            int v = a[u][i];
            int kk = abs (u - v);
            if (u < v){
                if (du % kk == 0) duu = ((du / kk) % 2 == 1) ?  du + 2 * kk : du + kk;
                else {
                    if ((du / kk) % 2 == 1) duu = du / kk * kk + 2 * kk;
                    else duu = du / kk * kk + 3 * kk;
                }
            }
            else{
                if (du % kk == 0) duu = ((du / kk ) % 2 == 1) ? du + kk: du + 2 * kk;
                else{
                    if ((du / kk) %2 == 0) duu = duu / kk * kk + 2 * kk;
                    else duu = du / kk * kk + 3 * kk;
                }
            }
            if (d[v] == -1 || d[v] > duu){
                d[v] = duu;
                pq.push(ii(duu, v));
            }
        }

    }
}

int main(){
    cin>>n>>k;
    for (int i = 1; i<=k; i++){
        cin>>x>>y;
        a[x].push_back(y);
        a[y].push_back(x);
    }
    dijsktra();
    cout<<d[n]* 5;
}

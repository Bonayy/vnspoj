// V8ORG - Sol by Taku

#include <bits/stdc++.h>

using namespace std;

const int N = 10005;

int d[N], n, k, t, res = 0;

vector <int> a[N];

void DFS(int u){
    d[u] = 1;
    for (int i = 0; i<a[u].size(); i++){
        int v = a[u][i];
        DFS(v);
        d[u] += d[v];
    }
    if (d[u] >=k){
        d[u] = 0;
        res++;
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    freopen("INPUT.TXT", "r", stdin);
    freopen("OUTPUT.TXT", "w", stdout);
    cin>>k>>n;
    for (int i = 2; i<=n; i++){
        cin>>t;
        a[t].push_back(i);
    }
    DFS(1);
    cout<<res;
}

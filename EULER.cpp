#include <bits/stdc++.h>

using namespace std;

const int N = 205;

int n, m, a[N][N];

void solve(){
    cout<<m<<'\n';
    stack  <int> s;
    s.push(1);
    while (!s.empty()){
        int u = s.top();
        bool check = 1;
        for (int v = 1; v <= n; v++)
            if (a[u][v]){
                s.push(v);
                a[u][v]--;
                a[v][u]--;
                check = 0;
                break;
            }
        if (check){
            cout<<u<<" ";
            s.pop();
        }
    }
}
int main(){
    cin>>n>>m;
    int x;
    for (int i = 1; i <= n; i++) cin>>x;
    for (int i = 1; i <= m; i++){
        int u, v;
        cin>>u>>v;
        a[u][v]++;
        a[v][u]++;
    }
    solve();
}

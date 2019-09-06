#include <bits/stdc++.h>

using namespace std;

const int N = 205;
const int INF = 1e9;

struct Td{
    int X;
    int Y;
};

int n, m;
Td a[N][N];

int c[N* N], res = 0, kk, deg[N], F[N], minn;

bool check (int kk){
    if (res != m+1) return false;
    for (int i = 1; i<=n; i++)
        if (deg[i] % 2 == 1) return false;
    int sum = 0;
    for(int i=kk; i<res; i++) {
        sum += a[c[i]][c[i+1]].Y;
        if (sum < 0) return false;
    }
    for(int i=1; i<kk; i++) {
        sum += a[c[i]][c[i+1]].Y;
        if (sum < 0) return false;
    }
    return true;
}

void euler(){
    stack  <int> s;
    s.push(1);
    while (!s.empty()){
        int u = s.top();
        bool check = 1;
        for (int v = 1; v <= n; v++)
            if (a[u][v].X){
                s.push(v);
                a[u][v].X--;
                a[v][u].X--;
                check = 0;
                break;
            }
        if (check){
            c[++res] = u;
            s.pop();
        }
    }
}

int main(){
    cin>>n>>m;
    for (int i = 1; i<=m; i++){
        int u, v, w;
        cin>>u>>v>>w;
        a[u][v].X ++;
        a[v][u].X ++;
        a[u][v].Y = w;
        a[v][u].Y = w;
        deg[u] ++;
        deg[v] ++;
    }
    euler();
    minn = INF; F[1] = 0;
    for (int i = 2; i<=res; i++){
        F[i] = F[i-1] + a[c[i]][c[i-1]].Y;
        if (F[i] < minn) {
            minn = F[i];
            kk = i;
        }
    }
    if (check(kk)){
        for(int i = kk ; i<=res; i++) cout<<c[i]<<" ";
        for(int i = 2 ; i<=kk; i++) cout<<c[i]<<" ";
    }
    else {
        cout<<-1;
    }
}

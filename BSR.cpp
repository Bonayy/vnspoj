// BSR - Sol by Taku
#include <bits/stdc++.h>
using namespace std;

const int N = 510;

int m, n, ans = 0;
long long t, a[N][N], f[N][N];
int kk[20];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("BSR.inp", "r", stdin);
    freopen("BSR.out", "w", stdout);
    cin>>m>>n;
    for (int i = 1; i<=m; i++)
        for (int j = 1; j<=n; j++) cin>>a[i][j];
    for (int i = 1; i<=m; i++)
        for (int j = 1; j<=n; j++)
            f[i][j] = (f[i-1][j] + f[i][j-1] - f[i-1][j-1] + a[i][j] + 9) % 9;
    for (int u = 1; u<=m; u++){
        for (int v = 0; v < u; v++){
            for (int i = 0; i<9; i++) kk[i] = 0;
            for (int y = 0; y<=n; y++){
                t = (f[u][y] - f[v][y] + 9) % 9;
                kk[t] ++;
            }
            for (int i = 0; i<9; i++) ans += (kk[i] - 1) * kk[i] /2;
        }
    }
    cout<<ans;
}

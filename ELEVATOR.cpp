// ELEVATOR - Sol by Taku
// SPOJ

#include <bits/stdc++.h>

using namespace std;

const int N = 405;
const int maxn = 40005;

struct Taku{
    int h;
    int a;
    int c;
};

int n;
Taku cc[N];
bool f[N][maxn];

bool operator < (Taku X, Taku Y){
    return (X.a < Y.a);
}

int main(){
    memset(f, 0, sizeof(f));
    cin>>n;
    for (int i = 1; i<=n; i++) cin>>cc[i].h>>cc[i].a>>cc[i].c;
    sort(cc+1, cc+1+n);
    f[0][0] = 1;
    for (int i = 1; i<=n; i++){
        for (int j = 0; j<=cc[i].a; j++){
                for (int k = 0; k <= cc[i].c; k++)
                    if (j - cc[i].h * k >= 0)
                        if (f[i-1][j - cc[i].h *k]) f[i][j] = 1;
        }
    }
    for (int i = cc[n].a; i >= 0; i--) if (f[n][i]) {cout<<i; return 0; }
}

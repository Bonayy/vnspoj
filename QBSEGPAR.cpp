// QBSEGPAR  - Sol by Taku
// 09.09.2019

#include <bits/stdc++.h>
using namespace std;

const int N = 15005;
const int INF = 1e9;

int s[N], a, n, k, b[N];
int ma[N], mi[N],f[N], g[N];

void update (bool ok, int x, int val){
    for (; x <=n; x += x & -x)
        if (ok) ma[x] = max(ma[x], val);
        else mi[x] = min(mi[x], val);
}

int get (bool ok, int x){
    int ans;
    if (ok) ans = -INF;
    else ans = INF;
    for (; x > 0; x -= x & -x)
        if (ok) ans = max(ans, ma[x]);
        else ans = min(ans, mi[x]);
    return ans;
}

bool check (int m){
    memset(f, 0, sizeof (f));
    memset(g, 0, sizeof (g));
    memset(ma, 0, sizeof (ma));
    memset(mi, 0, sizeof (mi));
     for (int i = 0; i<=n; i++){
        int tmp = upper_bound(b, b+1+n, s[i] - m) - b;
        f[i] = get(0, tmp - 1) + 1;
        g[i] = get(1, tmp - 1) + 1;
        update(0, tmp - 1, f[i]);
        update(1, tmp - 1, f[i]);
    }
    return (g[n] <=k && f[n] >=k);
}



int main(){
    cin>>n>>k;
    s[0] = 0; b[0] = 0;
    for (int i = 1; i<=n; i++){
        cin>>a;
        s[i] = s[i-1] + a;
        b[i] = s[i];
    }
    sort(b, b+1+n);
    int l = -INF, r= INF, res;
    while (l <= r){
        int mid = (l + r)/2;
        if (check(mid)){
            res = mid;
            r = mid - 1;
        }
        else l = mid+1;
    }
    cout<<res;
}

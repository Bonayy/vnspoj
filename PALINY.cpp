// PALINY - Sol by Taku
// SPOJ
#include <bits/stdc++.h>
using namespace std;

const int base = 311;
const long long MOD = 1000000003;
const long long maxn = 50005;

using namespace std;

long long POW[maxn], hashT[maxn], hasht[maxn], ll, mid, rr, ans =0, lenT;


long long getHashT(int i,int j) {
    return (hashT[j] - hashT[i - 1] * POW[j - i + 1] + MOD * MOD) % MOD;
}

long long getHasht(int i,int j) {
//swap(i,j);
    return (hasht[i] - hasht[j + 1] * POW[j - i +1] + MOD * MOD) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    //freopen("PALINY.INP","r", stdin);
    // freopen("PALINY.OUT","w", stdout);
    string T, C; int n;
    cin >> n >> C;
    T[0] = ' ';
    T.resize(3*n);
    for (int i=0 ;i < C.length(); i++) {T[i*2+1] = '#'; T[i*2+2] = C[i];}
    T[2*n+1] = '#';lenT = 2*n+1;
    POW[0] = 1;
    hashT[0] = 0;
    for (int i = 1; i <= lenT; i++)
        POW[i] = (POW[i - 1] * base) % MOD;
    for (int i = 1; i <= lenT; i++)
        hashT[i] = (hashT[i - 1] * base + int(T[i])) % MOD;
    hasht[lenT+1] = 0;
    for (int i = lenT; i > 0; i--)
        hasht[i] = (hasht[i + 1] * base + int(T[i]))  % MOD;
        cout<<getHasht(1, 3)<<"\n";
    cout<<getHashT(1, 3);
    for (long long i = 1; i <= lenT; i++){
        ll = 0;
        rr = min(i - 1, lenT - i);
        mid = (ll + rr) / 2;
        while (ll != mid && mid != rr){
            if (getHashT(i - mid, i + mid) == getHasht(i - mid, i + mid)) ll = mid;
            else rr = mid;
            mid = (ll + rr) / 2;
        }
       for (long long j = ll ; j <=rr; j++)
            if (getHashT(i - j, i+ j) == getHasht(i - j,i+j)) ans = max(ans, j);
    }
    cout<<ans;
}

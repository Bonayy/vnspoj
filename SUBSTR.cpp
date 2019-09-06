//Hash - Sol by Taku
// 29.08.2019

#include <bits/stdc++.h>

using namespace std;

const int BASE = 311;
const int MOD = 1e9 + 7;
const int maxn = 1e6 + 5;

typedef long long ll;

ll Pow[maxn], hashT[maxn], HashP;
ll lenT, lenP;
string T, P;

ll getHashT(int i, int j){
    return (hashT[j] - hashT[i-1] * Pow[j - i + 1] % MOD + MOD ) % MOD;
}


int main(){
    cin>>T>>P;
    lenT = T.size();
    lenP = P.size();
    T = " " + T;
    P = " " + P;
    Pow[0] = 1; hashT[0] = 1;
    for (int i = 1; i <= lenT; i++) Pow[i] = (Pow[i-1] * BASE) % MOD;
    for (int i = 1; i <= lenT; i++){
        hashT[i] = (hashT[i-1] * BASE + int(T[i])) % MOD;
    }
    HashP = 0;
    for (int i = 1; i <= lenP; i++) HashP = (HashP * BASE + int(P[i])) % MOD;
    for (int i = 1; i <= lenT; i++) {
        if (getHashT(i, i + lenP - 1) == HashP) cout<<i<<" ";
    }
}

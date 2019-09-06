#include <bits/stdc++.h>
using namespace std;

const int N = 5e6 + 7;

long long a[2 * N], p, q, m, n, dd, res = 1e18;

deque <long long> pq;

void PUSH(int x){
    while (!pq.empty() && a[pq.back()] < a[x]) pq.pop_back();
    pq.push_back(x);
}

int main(){
    cin>>n>>dd;
    cin>>p>>q>>m;
    for (int i = 1; i<=n; i++){
        a[i] = (p * i) % m + q;
        a[i+ n] = a[i];
    }
    for (int i = 1; i<=2 *n; i++) a[i] += dd * i;
    for (int i = 1; i<n; i++) PUSH(i);
    for (int i = n; i<=2 *n; i++){
        PUSH(i);
        res = min(res, a[pq.front()] - (i - n)* dd );
        if (a[pq.front()] == a[i - n + 1]) pq.pop_front();
    }
    cout<<res;
}

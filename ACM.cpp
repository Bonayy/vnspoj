#include <bits/stdc++.h>

using namespace std;

vector <int> cc;

int a, b, n, res = 0;

int main(){
    cin>>n;
    for (int i = 1; i<=2 * n; i++) {
        cin>>a>>b;
        res +=a;
        cc.push_back(b - a);
    }
    sort(cc.begin(), cc.end());
    for (int i = 0; i < n; i++) res += cc[i];
    cout<<res;
}

#include <bits/stdc++.h>
using namespace std;

const int N = 105;
const long long INF = 1e18 + 7;

typedef vector<long long> BigInt;
const long long BASE = 1e4;

BigInt operator + (BigInt a, BigInt b) {
    BigInt c; long long carry = 0;
    for(int i = 0; i < a.size() || i < b.size(); i++) {
        if (i < a.size()) carry += a[i];
        if (i < b.size()) carry += b[i];
        c.push_back(carry % BASE);
        carry /= BASE;
    }
    if (carry) c.push_back(carry);
    return c;
}

BigInt operator * (BigInt a, int b) {
    BigInt c; long long carry = 0;
    for(int i = 0; i < a.size(); i++) {
        carry += a[i] * b;
        c.push_back(carry % BASE);
        carry /= BASE;
    }
    if (carry) c.push_back(carry);
    return c;
}

BigInt operator * (BigInt a, BigInt b) {
    BigInt c(a.size() + b.size() + 2, 0);
    for (int i = 0; i < a.size(); i++) {
        long long  carry = 0;
        for (int j = 0; j < b.size(); j++) {
            int k = i + j;
            c[k] += a[i] * b[j] + carry;
            carry = c[k] / BASE;
            c[k] %= BASE;
        }
        if (carry) c[i + b.size()] += carry;
    }
    while (*c.rbegin() == 0 && c.size() > 0)
        c.erase(c.begin() + c.size() - 1);
    return c;
}

void Print(BigInt a) {
    int L = a.size(), len = 0;
    char buffer[100000];
    len += sprintf(buffer, "%d", a[L - 1]);
    for(int i = L - 2; i >= 0; i--)
        len += sprintf(buffer + len, "%04d", a[i]);
    int cnt = 0;
    for(int i = 0; i < len; i++) {
        printf("%c", buffer[i]);
    }
}

long long t, n, maxb;
BigInt f[N][N];
bool ok1 = false;
string s;

BigInt Cal(int i, int k){
    if (k > maxb || k < 0) {
    	BigInt ans ;
    	ans.push_back(0);
    	return ans;
	}
	if (i > n ){
		BigInt ans;
        if (k == 0) ans.push_back(1);
        else ans.push_back(0);
        return ans;
	}
    if (f[i][k].size() > 0) return f[i][k];
    if (k < maxb) f[i][k]= f[i][k]+ Cal(i+1, k+1) * 3;
    if (k > 0 ) f[i][k]= f[i][k]+ Cal(i+1, k-1);
    return f[i][k];
}

BigInt Cal2(){
	stack <char> pq;
    BigInt ans;
    int k = 0;
    for (int i = 0; i<=n; i++){
        if (s[i] == '(') pq.push('(');
        if (s[i] == ')') {
			ans = ans + Cal(i+1, pq.size()+1);
			pq.pop();
		}
		if (s[i] == '[') {
			ans = ans + Cal(i+1, pq.size() +1);
			if (!pq.empty() ){
			   if (pq.top() == '(') ans = ans + Cal(i+1, pq.size() - 1);
			}
			pq.push('[');
		}
		if (s[i] == ']') {
			ans = ans + Cal (i+1, pq.size() +1) * 2;
			pq.pop();
		}
		if (s[i] == '{'){
			ans = ans + Cal(i+1, pq.size() +1 ) * 2;
			if (!pq.empty() ) {
				if (pq.top() != '{') ans = ans + Cal(i+1, pq.size() - 1);
			}
			pq.push('{');
		}
		if (s[i] == '}'){
			ans = ans + Cal(i+1, pq.size() + 1) * 3;
			pq.pop();
		}
	}
    return ans;
}

int main(){
    cin>>n>>maxb; n--;
	cin>>s;
	BigInt ANS;
	ANS.push_back(1);
	ANS = ANS + Cal2();
    Print(ANS) ;
}

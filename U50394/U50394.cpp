// Problem: U50394 组合数求和
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/U50394
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define pf push_front
#define rep(i, s, t) for (int i = s; i <= t; ++i)
#define per(i, s, t) for (int i = t; i >= s; --i)

const int N = 1e6 + 105;
const int P = 1e9 + 7;

int qpow(int x, int p) {
	int res = 1, base = x;
	while(p) {
		if(p & 1) res = 1ll * res * base % P;
		base = 1ll * base * base % P;
		p >>= 1;
	}
	return res;
}

int n;
int fac[N], ifac[N];

inline int cob(int n, int m) {
	return 1ll * fac[n] * ifac[m] % P * ifac[n-m] % P;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	n = 1e6 + 100;
	
	fac[0] = ifac[0] = fac[1] = ifac[1] = 1;
	rep(i, 2, n) fac[i] = 1ll * fac[i-1] * i % P;
	ifac[n] = qpow(fac[n], P - 2);
	per(i, 2, n-1) ifac[i] = 1ll * (i+1) * ifac[i+1] % P;
	
	int t; cin >> t;
	while(t--) {
		int op, n, m;
		cin >> op >> n >> m;
		if(n < m) cout << 0 << "\n";
		else {
			if(op == 1) cout << cob(n+1, m+1) << "\n";
			else cout << cob(n+1, m) << "\n";
		}
	}
	
	return 0;
}

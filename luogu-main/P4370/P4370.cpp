// Problem: P4370 [Code+#4]组合数问题2
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4370
// Memory Limit: 250 MB
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

const int N = 1e6 + 5;
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

int n, k;
int fac[N], ifac[N];
long double pre[N];

inline long double calc(int n, int m) {
	return pre[n] - pre[m] - pre[n-m];
}

inline int cob(int n, int m) {
	return 1ll * fac[n] * ifac[m] % P * ifac[n-m] % P;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> k;
	fac[0] = ifac[0] = fac[1] = ifac[1] = 1;
	rep(i, 2, n) fac[i] = 1ll * fac[i-1] * i % P;
	ifac[n] = qpow(fac[n], P - 2);
	per(i, 2, n-1) ifac[i] = 1ll * (i+1) * ifac[i+1] % P;
	rep(i, 1, n) pre[i] = pre[i-1] + log((double)i);
	priority_queue<tuple<long double, int, int>> pq;
	rep(i, 0, n) pq.emplace(calc(n, i), n, i);
	
	int ans = 0;
	while(k--) {
		auto [v, i, j] = pq.top(); pq.pop();
		ans = (ans + cob(i, j)) % P;
		if(i != j) pq.emplace(calc(i-1, j), i-1, j);
	}
	cout << ans << "\n";
	
	return 0;
}

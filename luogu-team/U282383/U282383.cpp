// Problem: U282383 雪（irori ）
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/U282383
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// Create Time: 2023-03-19 20:06:33
// Input/Output: stdin/stdout
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

const int N = 5e7 + 5;
const int P = 998244353;

inline int qpow(int x, int p) {
	int res = 1, base = x;
	while(p) {
		if(p & 1) res = 1ll * res * base % P;
		base = 1ll * base * base % P;
		p >>= 1;
	}
	return res;
}

int n, m, k;
int fac[N], ifac[N];

int solve(int l, int r, int x, int y, int lastop) {
	if(x < 0 || y < 0) return 0;
	if(r < 0) return 0;
	assert(x + y == n + m);
	int ans = fac[x];
	rep(i, 0, 1) if(i != lastop) {
		int x0, y0;
		if(i == 0) {
			int d = y-x-l;
			x0 = x+d+1;
			y0 = y-d-1;
		} else {
			int d = r-(y-x);
			x0 = x-d-1;
			y0 = y+d+1;
		}
		ans = (ans - solve(l, r, x0, y0, i)) % P;
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> m >> k;
	
	fac[0] = ifac[0] = fac[1] = ifac[1] = 1;
	rep(i ,2, n+m) fac[i] = 1ll * fac[i-1] * i % P;
	int f = fac[n+m];
	ifac[n+m] = qpow(fac[n+m], P-2);
	per(i, 2, n+m-1) ifac[i] = 1ll * ifac[i+1] * (i+1) % P;
	rep(i, 0, n+m) fac[i] = 1ll * f * ifac[i] % P * ifac[n+m-i] % P;
	int ans = 0;
	rep(i, -k, 0) {
		if(i <= m-n && m-n <= i+k) ans = (ans + solve(i, i+k, n, m, 2)) % P;
		if(i <= m-n && m-n <= i+k-1) ans = (ans - solve(i, i+k-1, n, m, 2)) % P;
	}
	cout << (ans + P) % P << "\n";
	
	return 0;
}

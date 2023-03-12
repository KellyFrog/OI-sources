// Problem: P4769 [NOI2018] 冒泡排序
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4769
// Memory Limit: 500 MB
// Time Limit: 1000 ms
// Create Time: 2022-06-22 12:55:06
// Author: Chen Kaifeng
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

const int N = 1.3e6 + 5;
const int P = 998244353;

int qpow(int x, int p) {
	int res = 1, base = x;
	while(p) {
		if(p & 1) res = 1ll * res * base % P;
		base = 1ll * base * base % P;
		p >>= 1;
	}
	return res;
}

int n, a[N];
int fac[N], ifac[N];
bool vis[N];
int p1, p2;

inline int cob(int n, int m) { return 1ll * fac[n] * ifac[m] % P * ifac[n-m] % P; }
inline int getf(int i, int j) { return i>j || i>n || j>n ? 0 : cob(2*n-i-j, n-i) - cob(2*n-i-j, n+1-i); }

void solve() {
	cin >> n;
	rep(i, 1, n) cin >> a[i];
	int ans = 0;
	int mx = 0;
	p1 = p2 = 0;
	rep(i, 1, n) vis[i] = 0;
	rep(i, 1, n) {
		vis[a[i]] = 1;
		bool ok = 0;
		if(a[i] > mx) {
			mx = a[i];
			ok = 1;
		}
		if(a[i] == p1 + 1) {
			while(p1+1 <= n && vis[p1+1]) ++p1;
			ok = 1;
		}
		ans = (ans + getf(i-1, mx+1)) % P;
		if(!ok) {
			break;
		}
	}
	cout << (ans + P) % P << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	int k = 1.2e6+5;
	fac[0] = fac[1] = ifac[0] = ifac[1] = 1;
	rep(i, 2, k) fac[i] = 1ll * fac[i-1] * i % P;
	ifac[k] = qpow(fac[k], P - 2);
	per(i, 2, k-1) ifac[i] = 1ll * ifac[i+1] * (i+1) % P;

	int t; cin >> t;
	while(t--) solve();
	
	return 0;
}
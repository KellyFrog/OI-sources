// Problem: AT2005 [AGC003E] Sequential operations on Sequence
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT2005
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// Create Time: 2022-07-29 15:00:27
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

const int N = 2e5 + 5;

int n, q, top;
ll stk[N], a[N], f[N], ans[N];
vector<pair<int, ll>> adj[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> q;
	ll mi = 1e18;
	rep(i, 1, q) cin >> a[i], mi = min(mi, a[i]);
	rep(i, 1, n) stk[++top] = i;
	
	rep(i, 1, q) {
		while(top && stk[top] >= a[i]) --top;
		stk[++top] = a[i];
	}
	
	int p = 1;
	rep(i, 1, min(mi, 1ll * min(top, n))) {
		if(stk[i] != i) break;
		p = i;
	}
	
	rep(i, p+1, top) {
		ll x = stk[i];
		while(x) {
			int p = upper_bound(stk + 1, stk + i, x) - stk - 1;
			adj[i].emplace_back(p, x / stk[p]);
			x %= stk[p];
		}
	}
	
	f[top] = 1;
	
	per(i, p+1, top) {
		for(auto [v, t] : adj[i]) {
			f[v] += t * f[i];
		}
	}
	
	rep(i, 1, p) ans[i] = f[i];
	per(i, 1, n) ans[i] += ans[i+1];
	rep(i, 1, n) cout << ans[i] << "\n";
	
	return 0;
}

// Problem: CF521D Shop
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF521D
// Memory Limit: 250 MB
// Time Limit: 2000 ms
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

const int N = 1e5 + 5;

int n, m, k;
ll a[N];
int op[N], pos[N], val[N];
int mx[N];
vector<int> adj[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> m >> k;
	rep(i, 1, n) cin >> a[i];
	vector<pair<long double, int>> v;
	rep(i, 1, m) {
		cin >> op[i] >> pos[i] >> val[i];
		if(op[i] == 1) {
			if(val[mx[pos[i]]] < val[i]) mx[pos[i]] = i;
		} else if(op[i] == 2) {
			adj[pos[i]].pb(i);
		} else {
			v.emplace_back((long double)val[i], i);
		}
	}
	rep(i, 1, n) if(val[mx[i]] > a[i]) {
		val[mx[i]] -= a[i];
		adj[i].pb(mx[i]);
	}
	rep(i, 1, n) {
		sort(adj[i].begin(), adj[i].end(), [&](int j, int k) { return val[j] > val[k]; });
		ll s = a[i];
		for(int j : adj[i]) {
			v.emplace_back((long double)(s + val[j]) / s, j);
			s += val[j];
		}
	}
	sort(v.begin(), v.end());
	reverse(v.begin(), v.end());
	k = min(k, (int)v.size());
	vector<int> ans(k);
	for(int i = 0; i < k; ++i) ans[i] = v[i].se;
	sort(ans.begin(), ans.end(), [&](int i, int j) { return op[i] < op[j]; });
	cout << ans.size() << "\n";
	for(int i : ans) cout << i << " "; cout << "\n";
	
	return 0;
}

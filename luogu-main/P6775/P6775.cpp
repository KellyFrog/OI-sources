// Problem: P6775 [NOI2020] 制作菜品
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6775
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// Create Time: 2022-06-28 10:39:28
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

const int N = 5e2 + 5;
const int M = 5e3 + 5;

int n, m, k;
int a[N];
bitset<2*N*M> f[N];

void solve(const vector<int>& v, int m) {
	assert(m >= v.size() - 1);
	set<pair<int, int>> s;
	for(int i : v) s.emplace(a[i], i);
	while(m--) {
		assert(!s.empty());
		auto [x, i] = *s.begin(); s.erase(s.begin());
		if(x >= k) {
			cout << i << " " << k << "\n";
			x -= k;
			a[i] -= k;
			if(x) s.emplace(x, i);
		} else {
			auto [y, j] = *s.rbegin(); s.erase(--s.end());
			cout << i << " " << x << " " << j << " " << k-x << "\n";
			y -= k-x;
			assert(y >= 0);
			a[i] -= x;
			a[j] -= k-x;
			if(y) s.emplace(y, j);
		}
	}
	assert(s.empty());
}

bool vis[N];

inline void dfs(int i, int p) {
	if(i == 0) return;
	int v = a[i] - k;
	if(f[i-1][p]) dfs(i-1, p);
	else vis[i] = 1, dfs(i-1, p-v);
}

void solve() {
	cin >> n >> m >> k;
	rep(i, 1, n) cin >> a[i];
	if(m >= n-1) {
		vector<int> v;
		rep(i, 1, n) v.push_back(i);
		solve(v, m);
	} else {
		rep(i, 0, n) f[i].reset();
		f[0][n*k] = 1;
		rep(i, 1, n) {
			int v = a[i] - k;
			if(v > 0) f[i] = f[i-1] | (f[i-1] << v);
			else f[i] = f[i-1] | (f[i-1] >> (-v));
		}
		rep(i, 1, n) vis[i] = 0;
		if(!f[n][n*k-k]) cout << -1 << "\n";
		else {
			vector<int> v1, v2;
			dfs(n, n*k-k);
			int s1 = 0, s2 = 0;
			rep(i, 1, n) {
				if(vis[i]) v1.push_back(i), s1 += a[i];
				else v2.push_back(i), s2 += a[i];
			}

			assert(s1 == k * (v1.size()-1));
			assert(s2 == k * (v2.size()-1));

			solve(v1, v1.size()-1);
			solve(v2, v2.size()-1);
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	int t; cin >> t;
	while(t--) solve();
	
	return 0;
}
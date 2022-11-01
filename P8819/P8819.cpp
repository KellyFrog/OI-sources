// Problem: P8819 [CSP-S 2022] 星战（民间数据）
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P8819?contestId=90216
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define pf push_front
#define rep(i, s, t) for (int i = s; i <= t; ++i)
#define per(i, s, t) for (int i = t; i >= s; --i)

const int N = 5e5 + 5;

mt19937_64 mtrnd(0x114514);
int n, m, q;
vector<int> adj[N];
set<int> lst[N];
int tp[N], d[N];
ull val[N], nxt[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> m;
	rep(i, 1, m) {
		int u, v; cin >> u >> v;
		adj[v].pb(u);
		++d[u];
	}
	rep(i, 1, n) val[i] = mtrnd();
	rep(u, 1, n) for(int v : adj[u]) nxt[u] ^= val[v];

	ull all = 0, cur = 0;
	int sum = 0;

	rep(u, 1, n) {
		all ^= val[u];
		if(d[u] & 1) cur ^= val[u];
		sum += d[u];
	}

	auto add = [&](int u, int v) {
		cur ^= val[u];
		++sum;
		if(tp[v] == 0) lst[v].erase(u);
		else lst[v].insert(u);
	};

	auto del = [&](int u, int v) {
		cur ^= val[u];
		--sum;
		if(tp[v] == 0) lst[v].insert(u);
		else lst[v].erase(u);
	};

	cin >> q;

	while(q--) {
		int op; cin >> op;
		if(op == 1) {
			int u, v; cin >> u >> v;
			del(u, v);
		} else if(op == 3) {
			int u, v; cin >> u >> v;
			add(u, v);
		} else if(op == 2) {
			int u; cin >> u;
			if(tp[u] == 0) {
				for(int v : lst[u]) {
					cur ^= val[v];
					++sum;
				}
				lst[u].clear();
				sum -= adj[u].size();
				cur ^= nxt[u];
				tp[u] = 1;
			} else if(tp[u] == 1) {
				for(int v : lst[u]) {
					cur ^= val[v];
					--sum;
				}
				lst[u].clear();
			}
		} else {
			int u; cin >> u;
			if(tp[u] == 0) {
				for(int v : lst[u]) {
					cur ^= val[u];
					++sum;
				}
				lst[u].clear();
			} else {
				for(int v : lst[u]) {
					cur ^= val[u];
					--sum;
				}
				lst[u].clear();
				sum += adj[u].size();
				cur ^= nxt[u];
				tp[u] = 0;
			}
		}
		cout << sum << " " << cur << " ";
		cout << (sum == n && cur == all ? "YES" : "NO") << "\n";
	}
	return 0;
}

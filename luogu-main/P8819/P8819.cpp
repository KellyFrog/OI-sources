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
const int P1 = 998244353;
const int P2 = 1e9 + 7;
const int P3 = 1e9 + 9;

struct E {
	int v1, v2, v3;
	E(int v1, int v2, int v3) : v1(v1), v2(v2), v3(v3) {}
	E(ull v1, ull v2, ull v3) : v1(v1 % P1), v2(v2 % P2), v3(v3 % P3) {}
	E() {}
};

E operator + (const E& x, const E& y) {
	return E((x.v1 + y.v1) % P1, (x.v2 + y.v2) % P2, (x.v3 + y.v3) % P3);
}

E operator - (const E& x, const E& y) {
	return E((x.v1 - y.v1 + P1) % P1, (x.v2 - y.v2 + P2) % P2, (x.v3 - y.v3 + P3) % P3);
}

bool operator == (const E& x, const E& y) {
	return x.v1 == y.v1 && x.v2 == y.v2 && x.v3 == y.v3;
}
	
mt19937_64 mtrnd(0x114514);
int n, m, q;
vector<int> adj[N];
set<int> lst[N];
E val[N], nxt[N], all, cur;
int op[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> m;
	rep(i, 1, m) {
		int u, v; cin >> u >> v;
		adj[v].pb(u);
	}
	rep(i, 1, n) val[i] = E((ull)mtrnd(), (ull)mtrnd(), (ull)mtrnd());
	rep(u, 1, n) for(int v : adj[u]) nxt[u] = nxt[u] + val[v];
	rep(i, 1, n) {
		all = all + val[i];
		cur = cur + nxt[i];
	}
	cin >> q;
	while(q--) {
		int opt; cin >> opt;
		if(opt == 1) {
			int u, v; cin >> u >> v;
			cur = cur - val[u];
			if(op[v] == 0) lst[v].insert(u);
			else lst[v].erase(u);
		} else if(opt == 3) {
			int u, v; cin >> u >> v;
			cur = cur + val[u];
			if(op[v] == 0) lst[v].erase(u);
			else lst[v].insert(u);
		} else if(opt == 2) {
			int u; cin >> u;
			if(op[u] == 0) {
				for(int v : lst[u]) cur = cur + val[v];
				lst[u].clear();
				cur = cur - nxt[u];
			} else {
				for(int v : lst[u]) cur = cur - val[v];
				lst[u].clear();
			}
			
			op[u] = 1;
		} else {
			int u; cin >> u;
			if(op[u] == 0) {
				for(int v : lst[u]) cur = cur + val[v];
				lst[u].clear();
			} else {
				for(int v : lst[u]) cur = cur - val[v];
				lst[u].clear();
				cur = cur + nxt[u];
			}
			
			op[u] = 0;
		}
		cout << (cur == all ? "YES" : "NO") << "\n";
	}
	
	return 0;
}

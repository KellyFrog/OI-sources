// Problem: P6776 [NOI2020] 超现实树
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6776
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// Create Time: 2022-06-28 10:27:57
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

const int N = 2e6 + 5;

int rt, tot, son[N][4];
int ls[N], rs[N];
bool ok[N];
int n, m;

bool isleaf(int u) { return !ls[u] && !rs[u]; }

inline void insert(int u, int& o) {
	if(!u) {
		o = 0;
		return;
	}
	if(!o) {
		o = ++tot;
		memset(son[o], 0, sizeof son[o]);
		ok[o] = 0;
	}
	if(isleaf(u)) ok[o] = 1;
	if(ls[u] && rs[u]) {
		if(isleaf(ls[u])) insert(rs[u], son[o][2]);
		if(isleaf(rs[u])) insert(ls[u], son[o][3]);
	} else {
		if(!ls[u]) insert(rs[u], son[o][1]);
		if(!rs[u]) insert(ls[u], son[o][0]);
	}
}

inline bool dfs(int u) {
	if(!u) return 0;
	if(ok[u]) return 1;
	return dfs(son[u][0]) && dfs(son[u][1]) && dfs(son[u][2]) && dfs(son[u][3]);
}

void solve() {
	cin >> m;
	rt = tot = 0;
	while(m--) {
		cin >> n;
		rep(i, 1, n) cin >> ls[i] >> rs[i];
		insert(1, rt);
	}
	cout << (dfs(rt) ? "Almost Complete" : "No") << "\n";
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
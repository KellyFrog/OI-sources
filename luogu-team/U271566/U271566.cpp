// Problem: U271566 发电机
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/U271566?contestId=96511
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// Create Time: 2022-12-30 15:35:39
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

const int N = 3e5 + 5;
const int M = 22;
const int P = 1e9 + 7;

int n, m, k, a[N], b[N], d[N];
vector<int> adj[N];
int rt[N], ls[N*M], rs[N*M], sum[N*M], cnt[N*M], tt;
int stk[N], top;

inline void pushup(int o) {
	sum[o] = (sum[ls[o]] + sum[rs[o]]) % P;
	cnt[o] = cnt[ls[o]] + cnt[rs[o]];
}

inline void add(int& o, int p, int l, int r) {
	if(!o) o = ++tt;
	if(l == r) {
		++cnt[o];
		sum[o] = (sum[o] + b[p]) % P;
		return;
	}
	int mid = l + r >> 1;
	if(p <= mid) add(ls[o], p, l, mid);
	else add(rs[o], p, mid + 1, r);
	pushup(o);
}

inline int merge(int& o1, int o2, int l, int r) {
	if(!o1 || !o2) return o1 += o2, 0;
	if(l == r) {
		int ret = 1ll * cnt[o1] * cnt[o2] % P * b[l] % P;
		cnt[o1] += cnt[o2];
		sum[o1] = (sum[o1] + sum[o2]) % P;
		return ret;
	}
	int mid = l + r >> 1;
	int ret = (1ll * sum[ls[o1]] * cnt[rs[o2]] + 1ll * sum[ls[o2]] * cnt[rs[o1]] + merge(ls[o1], ls[o2], l, mid) + merge(rs[o1], rs[o2], mid + 1, r)) % P;
	pushup(o1);
	return ret;
}

inline void dfs1(int u, int fa) {
	stk[++top] = u;
	add(rt[u], a[u], 1, m);
	for(int v : adj[u]) if(v != fa) {
		dfs1(v, u);
		int x = merge(rt[u], rt[v], 1, m);
		d[u] = (d[u] + x) % P;
		d[stk[max(0, top-k-1)]] = (d[stk[max(0, top-k-1)]] - x) % P;
	}
	--top;
}

inline void dfs2(int u, int fa) {
	for(int v : adj[u]) if(v != fa) dfs2(v, u), d[u] = (d[u] + d[v]) % P;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> k;
	rep(i, 1, n) cin >> a[i], b[i] = a[i];
	sort(b + 1, b + n + 1);
	m = unique(b + 1, b + n + 1) - b - 1;
	rep(i, 1, n) a[i] = lower_bound(b + 1, b + m + 1, a[i]) - b;
	rep(i, 2, n) {
		int u, v; cin >> u >> v;
		adj[u].pb(v), adj[v].pb(u);
	}
	dfs1(1, 0);
	dfs2(1, 0);
	rep(i, 1, n) cout << (d[i] + P) % P << "\n";
	
	return 0;
}

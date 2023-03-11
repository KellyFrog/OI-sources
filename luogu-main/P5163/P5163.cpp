// Problem: P5163 WD与地图
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5163
// Memory Limit: 500 MB
// Time Limit: 3000 ms
// Create Time: 2022-08-17 15:17:28
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

const int N = 2e5 + 5;
const int M = 1e7 + 5;

int n, m, q;
int dfn[N], low[N], dfncnt, scc[N], scccnt, stk[N], siz[N], top;
bool ins[N];
vector<int> adj[N], bdj[N];
map<int, int> eid[N];
int a[N], t[N], op[N], qx[N], qy[N], res[N], eu[N], ev[N], ttt;
int uni[N];
int rt[N], ls[M], rs[M], cnt[M], tt;
ll sum[M];

inline void add(int& o, int p, int x, int y, int l, int r) {
	if(!o) {
		o = ++tt;
		ls[o] = rs[o] = cnt[o] = sum[o] = 0;
	}
	cnt[o] += x, sum[o] += y;
	if(l == r) return;
	int mid = l + r >> 1;
	if(p <= mid) add(ls[o], p, x, y, l, mid);
	else add(rs[o], p, x, y, mid + 1, r);
}

inline ll query(int o, int k, int l, int r) {
	if(k == 0) return 0;
	if(l == r) return 1ll * min(cnt[o], k) * l;
	int mid = l + r >> 1;;
	if(cnt[rs[o]] <= k) return query(ls[o], k-cnt[rs[o]], l, mid) + sum[rs[o]];
	else return query(rs[o], k, mid+1, r);
}

inline void merge(int& o1, int o2, int l, int r) {
	if(!o1 || !o2) return o1 += o2, void();
	cnt[o1] += cnt[o2];
	sum[o1] += sum[o2];
	if(l == r) return;
	int mid = l + r >> 1;
	merge(ls[o1], ls[o2], l, mid);
	merge(rs[o1], rs[o2], mid+1, r);
}

inline void tarjan(int u) {
	dfn[u] = low[u] = ++dfncnt;
	ins[u] = 1;
	stk[++top] = u;
	for(int v : adj[u]) {
		if(!dfn[v]) {
			tarjan(v);
			low[u] = min(low[u], low[v]);
			} else if(ins[v]) {
			low[u] = min(low[u], dfn[v]);
		}
	}
	if(dfn[u] == low[u]) {
		++scccnt;
		siz[scccnt] = 0;
		while(1) {
			int x = stk[top--];
			ins[x] = 0;
			scc[x] = scccnt;
			++siz[scc[x]];
			if(x == u) break;
		}
	}
}

void solve(const vector<int>& nd, const vector<tuple<int, int, int>>& e, int l, int r) {
	if(e.empty()) return;
	if(l > r) return;

	// cerr << "solve=" << l << " " << r << "\n";
	// cerr << "nd="; for(int u : nd) cerr << u << "\n";
	// cerr << "e=" << "\n";
	// for(auto [i, u, v] : e) cerr << i << " " << u << " " << v << "\n";

	int mid = l + r >> 1;
	for(auto [i, u, v] : e) if(t[i] >= mid) adj[u].pb(v);
	for(int u : nd) if(!dfn[u]) tarjan(u);
	vector<int> nd1, nd2;
	vector<tuple<int, int, int>> e1, e2;

	for(int u : nd) if(siz[scc[u]] > 1) nd2.pb(u);
	rep(i, 1, scccnt) nd1.pb(i);

	for(auto [i, u, v] : e) {
		if(t[i] >= mid && scc[u] == scc[v]) e2.emplace_back(i, u, v), res[i] = mid;
		else if(scc[u] != scc[v]) e1.emplace_back(i, scc[u], scc[v]);
		else res[i] = -1;
	}

	dfncnt = scccnt = 0;
	for(int u : nd) dfn[u] = low[u] = scc[u] = 0, adj[u].clear();

	solve(nd1, e1, l, mid - 1);
	solve(nd2, e2, mid + 1, r);
}

inline int find(int x) { return x == uni[x] ? x : uni[x] = find(uni[x]); }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> m >> q;
	rep(i, 1, n) cin >> a[i];
	rep(i, 1, m) {
		int u, v; cin >> u >> v;
		eu[i] = u, ev[i] = v;
		eid[u][v] = i;
		t[i] = q+1;
	}
	rep(i, 1, q) {
		cin >> op[i] >> qx[i] >> qy[i];
		if(op[i] == 1) t[eid[qx[i]][qy[i]]] = i;
		else if(op[i] == 2) a[qx[i]] += qy[i];
	}

	vector<tuple<int, int, int>> e;
	vector<int> nd;
	rep(i, 1, m) e.emplace_back(i, eu[i], ev[i]);
	rep(i, 1, n) nd.push_back(i);
	ttt = n;
	solve(nd, e, 1, q+1);
	rep(i, 1, m) if(res[i] != -1) bdj[res[i]].pb(i);
	rep(i, 1, n) uni[i] = i;
	rep(i, 1, n) add(rt[i], a[i], 1, a[i], 1, 1e9);
	vector<ll> ans;
	per(i, 1, q+1) {
		for(int e : bdj[i]) {
			int u = find(eu[e]), v = find(ev[e]);
			if(u != v) {
				uni[v] = u;
				merge(rt[u], rt[v], 1, 1e9);
			}
		}
		if(op[i] == 2) {
			int o = find(qx[i]);
			add(rt[o], a[qx[i]], -1, -a[qx[i]], 1, 1e9);
			a[qx[i]] -= qy[i];
			add(rt[o], a[qx[i]], 1, a[qx[i]], 1, 1e9);
		} else if(op[i] == 3) {
			int o = find(qx[i]);
			ans.pb(query(rt[o], qy[i], 1, 1e9));
		}
	}

	reverse(ans.begin(), ans.end());
	for(auto x : ans) cout << x << "\n";

	// rep(i, 1, m) cerr << "i=" << i << " " << eu[i] << " " << ev[i] << " " << t[i] << " " << res[i] << "\n";

	return 0;
}

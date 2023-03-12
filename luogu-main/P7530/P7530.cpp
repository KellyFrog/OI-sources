// Problem: P7530 [USACO21OPEN] United Cows of Farmer John P
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7530
// Memory Limit: 256 MB
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

const int N = 2e5 + 5;

int n, a[N], lst[N];
vector<int> adj[N];
int lazy[N<<2], cnt[N<<2];
ll sum[N<<2];

inline void setlazy(int o, int t) {
	lazy[o] += t, sum[o] += 1ll * t * cnt[o];
}

inline void pushdown(int o) {
	if(lazy[o]) {
		setlazy(o << 1, lazy[o]);
		setlazy(o << 1 | 1, lazy[o]);
		lazy[o] = 0;
	}
}

inline void pushup(int o) {
	cnt[o] = cnt[o<<1] + cnt[o<<1|1];
	sum[o] = sum[o<<1] + sum[o<<1|1];
}

inline void add(int o, int ql, int qr, int x, int l, int r) {
	if(ql > qr) return;
	if(ql <= l && r <= qr) return setlazy(o, x), void();
	pushdown(o);
	int mid = l + r >> 1;
	if(ql <= mid) add(o << 1, ql, qr, x, l, mid);
	if(mid < qr) add(o << 1 | 1, ql, qr, x, mid + 1, r);
	pushup(o);
}

inline void ins(int o, int p, int op, int l, int r) {
	if(l == r) {
		if(op == 1) sum[o] = 0, cnt[o] = 1;
		else sum[o] = cnt[o] = 0;
		return;
	}
	pushdown(o);
	int mid = l + r >> 1;
	if(p <= mid) ins(o << 1, p, op, l, mid);
	else ins(o << 1 | 1, p, op, mid + 1, r);
	pushup(o);
}

inline ll query(int o, int ql, int qr, int l, int r) {
	if(ql <= l && r <= qr) return sum[o];
	pushdown(o);
	int mid = l + r >> 1;
	ll res = 0;
	if(ql <= mid) res += query(o << 1, ql, qr, l, mid);
	if(mid < qr) res += query(o << 1 | 1, ql, qr, mid + 1, r);
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n;
	rep(i, 1, n) cin >> a[i];
	ll ans = 0;
	rep(i, 1, n) adj[i].pb(0);
	rep(i, 1, n) {
		if(adj[a[i]].back()) ins(1, adj[a[i]].back(), 0, 1, n);
		ins(1, i, 1, 1, n);
		if(adj[a[i]].size() >= 2) add(1, adj[a[i]][adj[a[i]].size()-2]+1, adj[a[i]].back()-1, -1, 1, n);
		int lst = adj[a[i]].back();
		ans += query(1, lst + 1, i, 1, n);
		add(1, lst+1, i-1, 1, 1, n);
		adj[a[i]].pb(i);
	}
	cout << ans << "\n";
	
	return 0;
}

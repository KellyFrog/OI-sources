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
const int inf = 0x3f3f3f3f;

int n, q;
int a[N], l[N], r[N];
int ans[N];
vector<pair<int, int>> adj[N];
vector<int> bdj[N<<1];
int lazymx[N<<2], lazymi[N<<2], mx[N<<2], mi[N<<2], mxans[N<<2];

inline void setlazy(int o, int x) {
	lazymx[o] = max(lazymx[o], x);
	lazymi[o] = min(lazymi[o], x);
	mxans[o] = max(mxans[o], max(mx[o] - x, x - mi[o]));
}

inline void pushdown(int o) {
	if(lazymx[o] != -1) {
		setlazy(o << 1, lazymx[o]);
		setlazy(o << 1 | 1, lazymx[o]);
		lazymx[o] = -1;
	}
	if(lazymi[o] != inf) {
		setlazy(o << 1, lazymi[o]);
		setlazy(o << 1 | 1, lazymi[o]);
		lazymi[o] = inf;
	}
}

inline void pushup(int o) {
	mx[o] = max(mx[o << 1], mx[o << 1 | 1]);
	mi[o] = min(mi[o << 1], mi[o << 1 | 1]);
	mxans[o] = max(mxans[o << 1], mxans[o << 1 | 1]);
}

inline void modify(int o, int ql, int qr, int x, int l, int r) {
	if(ql <= l && r <= qr) return setlazy(o, x), void();
	pushdown(o);
	int mid = l + r >> 1;
	if(ql <= mid) modify(o << 1, ql, qr, x, l, mid);
	if(mid < qr) modify(o << 1 | 1, ql, qr, x, mid + 1, r);
	pushup(o);
}

inline void modify(int o, int p, int op, int l, int r) {
	if(l == r) {
		if(op == -1) mi[o] = inf, mx[o] = 0;
		else mi[o] = mx[o] = a[l];
		return;
	}
	pushdown(o);
	int mid = l + r >> 1;
	if(p <= mid) modify(o << 1, p, op, l, mid);
	else modify(o << 1 | 1, p, op, mid + 1, r);
	pushup(o);
}

inline void build(int o, int l, int r) {
	mi[o] = inf, mx[o] = 0, mxans[o] = -1;
	lazymx[o] = -1;
	lazymi[o] = inf;
	if(l == r) return;
	int mid = l + r >> 1;
	build(o << 1, l, mid);
	build(o << 1 | 1, mid + 1, r);
}

inline int query(int o, int ql, int qr, int l, int r) {
	if(ql <= l && r <= qr) return mxans[o];
	pushdown(o);
	int mid = l + r >> 1;
	int res = -1;
	if(ql <= mid) res = max(res, query(o << 1, ql, qr, l, mid));
	if(mid < qr) res = max(res, query(o << 1 | 1, ql, qr, mid + 1, r));
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n;
	rep(i, 1, n) cin >> a[i] >> l[i] >> r[i], bdj[i+l[i]].pb(i), bdj[i+r[i]+1].pb(-i);
	cin >> q;
	rep(i, 1, q) {
		int l, r; cin >> l >> r;
		adj[r].emplace_back(l, i);
	}
	
	build(1, 1, n);

	rep(i, 1, n) {
		for(int j : bdj[i]) {
			if(j > 0) modify(1, j, 1, 1, n);
			else modify(1, -j, -1, 1, n);
		}
		if(i-l[i] >= 1) modify(1, i-r[i], i-l[i], a[i], 1, n);
		for(auto [j, id] : adj[i]) ans[id] = query(1, j, i, 1, n);
	}

	rep(i, 1, q) cout << ans[i] << "\n";
	
	return 0;
}

// Problem: CF1373G Pawns
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1373G
// Memory Limit: 250 MB
// Time Limit: 3000 ms

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

/*template ends here*/

const int N = 6e5 + 5;
const int inf = 0x3f3f3f3f;

struct Node {
	int lazy;
	int mx, mxpos;
	int smx, smxpos;
	Node() : mx(inf), smx(inf) {}
	Node(int lazy, int mx, int mxpos, int smx, int smxpos) : lazy(lazy), mx(mx), mxpos(mxpos), smx(smx), smxpos(smxpos) {}
};

Node tree[N<<2];
set<pair<int, int>> s;

inline Node merge(const Node& x, const Node& y) {
	vector<pair<int, int>> v;
	v.pb(mp(x.mx, x.mxpos)); v.pb(mp(x.smx, x.smxpos));
	v.pb(mp(y.mx, y.mxpos)); v.pb(mp(y.smx, y.smxpos));
	sort(v.begin(), v.end());
	if(v[0].fi >= inf) return Node(0, inf, 0, inf, 0);
	vector<pair<int, int>> ret;
	ret.pb(v[0]);
	for(int i = 1; i < v.size(); i++) {
		if(v[i].fi != v[i-1].fi) {
			ret.pb(v[i]);
		}
	}
	return Node(0, ret[0].fi, ret[0].se, ret[1].fi, ret[1].se);
}

inline void pushup(int cur) {
	tree[cur] = merge(tree[cur << 1], tree[cur << 1 | 1]);
}

inline void setlazy(int cur, int x) {
	tree[cur].lazy += x;
	tree[cur].mx += x;
	tree[cur].smx += x;
}

inline void pushdown(int cur) {
	if(tree[cur].lazy) {
		setlazy(cur << 1, tree[cur].lazy);
		setlazy(cur << 1 | 1, tree[cur].lazy);
		tree[cur].lazy=  0;
	}
}

inline void add(int cur, int ql, int qr, int x, int l, int r) {
	if(ql <= l && r <= qr) return setlazy(cur, x), void();
	pushdown(cur);
	int mid = l + r >> 1;
	if(ql <= mid) add(cur << 1, ql, qr, x, l, mid);
	if(mid < qr) add(cur << 1 | 1, ql, qr, x, mid + 1, r);
	pushup(cur);
}

Node qres; bool isfirst;

inline void query(int cur, int ql, int qr, int l, int r) {
	if(ql <= l && r <= qr) {
		if(isfirst) qres = tree[cur], isfirst = 0;
		else qres = merge(qres, tree[cur]);
		return;
	}
	pushdown(cur);
	int mid = l + r >> 1;
	if(ql <= mid) query(cur << 1, ql, qr, l, mid);
	if(mid < qr) query(cur << 1 | 1, ql, qr, mid + 1, r);	
}

inline void build(int cur, int l, int r) {
	if(l == r) {
		tree[cur] = Node(0, 0, l, inf, l);
		return;
	}
	int mid = l + r >> 1;
	build(cur << 1, l, mid);
	build(cur << 1 | 1, mid + 1, r);
	pushup(cur);
}

inline int querypos(int cur, int l, int r) {
	if(l == r) return l;
	pushdown(cur);
	int mid = l + r >> 1;
	auto check = [&](int x) { return 0 < x && x < inf; };
	if(check(tree[cur<<1|1].mx) || check(tree[cur<<1|1].smx)) return querypos(cur << 1 | 1, mid + 1, r);
	else return querypos(cur << 1, l, mid);
}

int n, m, k;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> k >> m;
	
	build(1, 1, n*2+m);
	
	int q = m;
	while(q--) {
		int x, y;
		cin >> x >> y;
		int p = y + abs(x - k);
			
		if(s.count(mp(x, y))) {
			s.erase(mp(x, y));
			isfirst = 1;
			query(1, p, n*2+m, 1, n*2+m);
			int pos = qres.mx == 1 ? qres.mxpos : qres.smxpos;
			add(1, p, pos, -1, 1, n*2+m);
		} else {
			s.insert(mp(x, y));
			isfirst = 1;
			query(1, p, n*2+m, 1, n*2+m);
			int pos = qres.mxpos;
			add(1, p, pos, 1, 1, n*2+m);
		}
		cout << max(0, querypos(1, 1, n*2+m) - n) << "\n";
	}
	return 0;
}

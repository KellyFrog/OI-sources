// Problem: P4348 [CERC2015]Cow Conﬁnement
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4348
// Memory Limit: 512 MB
// Time Limit: 3000 ms
// Create Time: 2022-07-30 09:24:02
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

const int N = 1e6 + 5;

int n, m, q, k = 1e6;
int sx[N], sy[N], tx[N], ty[N];
int mx[N], my[N], qx[N], qy[N], ans[N];
int tmp1[N], tmp2[N];
tuple<int, int, int, int, int> oper[N*10];
int tt;
int t[N];
set<pair<int, int>> s[N];
vector<pair<int, int>> adj[N];

inline int lowbit(int x) { return x & (-x); }
inline void add(int x, int val) { for(int x0 = x; x0 <= k; x0 += lowbit(x0)) t[x0] += val; }
inline int query(int x) { int ret = 0; for(int x0 = x; x0; x0 -= lowbit(x0)) ret += t[x0]; return ret; }

int modi[N<<2], addi[N<<2], sum[N<<2];

inline void setmod(int o, int x, int l, int r) {
  modi[o] = x;
  addi[o] = 0;
  sum[o] = x * (r - l + 1);
}

inline void setadd(int o, int x, int l, int r) {
  if(modi[o] != -1) {
    setmod(o, modi[o] + x, l, r);
  } else {
    addi[o] += x;
    sum[o] += x * (r - l + 1);
  }
}

inline void pushdown(int o, int l, int r) {
  int mid = l + r >> 1;
  if(modi[o] != -1) {
    setmod(o << 1, modi[o], l, mid);
    setmod(o << 1 | 1, modi[o], mid + 1, r);
    modi[o] = -1;
  }
  if(addi[o]) {
    setadd(o << 1, addi[o], l, mid);
    setadd(o << 1 | 1, addi[o], mid + 1, r);
    addi[o] = 0;
  }
}

inline void pushup(int o) {
  sum[o] = sum[o << 1] + sum[o << 1 | 1];
}

inline void set0(int o, int ql, int qr, int l, int r) {
  if(qr < l || ql > r) return;
  if(ql > qr) return;
  if(ql <= l && r <= qr) return setmod(o, 0, l, r), void();
  pushdown(o, l, r);
  int mid = l + r >> 1;
  if(ql <= mid) set0(o << 1, ql, qr, l, mid);
  if(mid < qr) set0(o << 1 | 1, ql, qr, mid + 1, r);
  pushup(o);
}

inline void add(int o, int ql, int qr, int x, int l, int r) {
  if(qr < l || ql > r) return;
  if(ql > qr) return;
  if(ql <= l && r <= qr) return setadd(o, x, l, r), void();
  pushdown(o, l, r);
  int mid = l + r >> 1;
  if(ql <= mid) add(o << 1, ql, qr, x, l, mid);
  if(mid < qr) add(o << 1 | 1, ql, qr, x, mid + 1, r);
  pushup(o);
}

inline int query(int o, int p, int l, int r) {
  if(p > r) return 0;
  if(l == r) return sum[o];
  pushdown(o, l, r);
  int mid = l + r >> 1;
  if(p <= mid) return query(o << 1, p, l, mid);
  else return query(o << 1 | 1, p, mid + 1, r);
}

void solve(int u) {
	setmod(1, 0, 0, 0);
	tt = 0;
	for(auto [op, id] : adj[u]) {
		if(op == 1) {
			oper[++tt] = {tx[id], sy[id], ty[id], 1, id};
			oper[++tt] = {sx[id]-1, sy[id], ty[id], 3, id};
			oper[++tt] = {sx[id], sy[id], ty[id], 5, id};
		} else if(op == 2) {
			oper[++tt] = {mx[id], my[id], my[id], 2, id};
		} else {
			oper[++tt] = {qx[id], qy[id], qy[id], 4, id};
		}
	}
	sort(oper + 1, oper + tt + 1, [&](const tuple<int, int, int, int, int>& x, const tuple<int, int, int, int, int>& y) {
		return get<0>(x) == get<0>(y) ? get<3>(x) < get<3>(y) : get<0>(x) > get<0>(y);
	});
	set<int> st;
	st.insert(0);
	
	auto getpos = [&](int x) {
		if(x == 0) return 0;
		auto it = st.lower_bound(x);
		assert(it != st.begin());
		--it;
		return *it + 1;
	};
	
	
	rep(i, 1, tt) {
		auto [x, l, r, op, id] = oper[i];
		if(op == 1) {
			tmp1[id] = query(1, r+1, 1, k);
			set0(1, l, r, 1, k);
			st.insert(r);
		} else if(op == 2) {
			add(1, getpos(l), l, 1, 1, k);
		} else if(op == 3) {
			add(1, getpos(r), r, tmp2[id], 1, k);
			add(1, getpos(l-1), l-1, -tmp1[id], 1, k);
		} else if(op == 4) {
			ans[id] = query(1, l, 1, k);
		} else {
			tmp2[id] = query(1, r+1, 1, k);
			st.erase(r);
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n;
	rep(i, 1, n) cin >> sx[i] >> sy[i] >> tx[i] >> ty[i];
	cin >> m;
	rep(i, 1, m) cin >> mx[i] >> my[i];
	cin >> q;
	rep(i, 1, q) cin >> qx[i] >> qy[i];
	
	tt = 0;
	rep(i, 1, n) {
		oper[++tt] = {sx[i], sy[i], ty[i], 1, i};
		oper[++tt] = {tx[i], sy[i], ty[i], 4, i};
	}
	rep(i, 1, m) oper[++tt] = {mx[i], my[i], my[i], 2, i};
	rep(i, 1, q) oper[++tt] = {qx[i], qy[i], qy[i], 3, i};
	sort(oper + 1, oper + tt + 1, [&](const tuple<int, int, int, int, int>& x, const tuple<int, int, int, int, int>& y) {
		return get<0>(x) == get<0>(y) ? get<3>(x) < get<3>(y) : get<0>(x) < get<0>(y);
	});
	s[0].emplace(k+1, 0);
	rep(i, 1, tt) {
		auto [x, l, r, op, id] = oper[i];
		int lv = query(l);
		
		if(op != 4) {
			int o = s[lv].lower_bound(mp(l, 0))->se;
			adj[o].emplace_back(op, id);
		}
		if(op == 1) { //insert
			add(l, 1);
			add(r+1, -1);
			s[lv+1].emplace(r, id);
		} else if(op == 4) {
			add(l, -1);
			add(r+1, 1);
			s[lv].erase(mp(r, id));
		}
	}
	rep(i, 0, n) solve(i);
	rep(i, 1, q) cout << ans[i] << "\n";
	
	return 0;
}

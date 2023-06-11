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

const int N = 1.6e5 + 5;
const int P = 998244353;

int qpow(int x, int p) {
	int res = 1, base = x;
	while(p) {
		if(p & 1) res = 1ll * res * base % P;
		base = 1ll * base * base % P;
		p >>= 1;
	}
	return res;
}

int n, q;
char s[N];
int pw[N], prepw[N];
int rt, ls[N*40], rs[N*40], pre[N*40], suf[N*40], siz[N*40], sum[N*40], ans[N*40], val[N*40], tt;
mt19937 mtrnd(chrono::steady_clock::now().time_since_epoch().count());

inline void pushup(int o) {
	if(o == 0) return;
	pre[o] = (pre[ls[o]] + (10ll * sum[ls[o]] + val[o]) % P * prepw[siz[rs[o]]] + pre[rs[o]]) % P;
	suf[o] = (suf[rs[o]] + 1ll * (siz[ls[o]] + 1) * (sum[rs[o]] + 1ll * pw[siz[rs[o]]] * val[o] % P) + 1ll * suf[ls[o]] * pw[siz[rs[o]]+1]) % P;
	ans[o] = (ans[ls[o]] + ans[rs[o]] + 1ll * suf[ls[o]] * (prepw[siz[rs[o]] + 1] - 1) + 1ll * val[o] * prepw[siz[rs[o]]] % P * (siz[ls[o]] + 1) + 1ll * pre[rs[o]] * (siz[ls[o]] + 1)) % P;
	sum[o] = (sum[rs[o]] + 1ll * pw[siz[rs[o]]] * val[o] + 1ll * pw[siz[rs[o]]+1] * sum[ls[o]]) % P;
	siz[o] = siz[ls[o]] + siz[rs[o]] + 1;
}

inline int copy(int o) {
	int oo = ++tt;
	ls[oo] = ls[o], rs[oo] = rs[o];
	pre[oo] = pre[o], suf[oo] = suf[o];
	sum[oo] = sum[o], val[oo] = val[o], siz[oo] = siz[o];
	return oo;
}

inline void split(int& o1, int& o2, int o, int k) {
	if(!o) {
		o1 = o2 = 0;
		return;
	}
	if(k <= siz[ls[o]]) {
		o2 = copy(o);
		split(o1, ls[o2], ls[o], k);
	} else {
		o1 = copy(o);
		split(rs[o1], o2, rs[o], k-siz[ls[o]]-1);
	}

	pushup(o1);
	pushup(o2);
}

inline void merge(int& o, int o1, int o2) {
	if(!o1 || !o2) {
		o = o1 + o2;
		return;
	}
	if(mtrnd() & 1) {
		o = copy(o1);
		merge(rs[o], rs[o1], o2);
	} else {
		o = copy(o2);
		merge(ls[o], o1, ls[o2]);
	}
	pushup(o);
}

inline void build(int& o, int l, int r) {
	if(l > r) return;
	o = ++tt;
	int mid = l + r >> 1;
	ans[o] = val[o] = sum[o] = pre[o] = suf[o] = s[mid] - '0';
	siz[o] = 1;
	build(ls[o], l, mid - 1);
	build(rs[o], mid + 1, r);
	pushup(o);
}

int sp = 0;

inline void dfs(int o) {
	if(!o) return;
	dfs(ls[o]);
	s[++sp] = val[o]+'0';
	dfs(rs[o]);
}

void rebuild() {
	sp = 0;
	dfs(rt);
	rt = 0;
	tt = 0;
	build(rt, 1, n);
}

int main() {
	freopen("arcane.in", "r", stdin);
	freopen("arcane.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> q;
	cin >> (s+1);

	pw[0] = 1;
	rep(i, 1, n) pw[i] = 10ll * pw[i-1] % P;
	prepw[0] = pw[0];
	rep(i, 1, n) prepw[i] = (prepw[i-1] + pw[i]) % P;

	build(rt, 1, n);

	assert(siz[rt] == n);

	auto getrange = [&](int& a, int& b, int& c, int l, int r) {
		split(a, c, rt, r);
		split(a, b, a, l-1);
		assert(siz[a] + siz[b] + siz[c] == n);
	};

	while(q--) {
		int op; cin >> op;
		if(op == 1) {
			int l, r;
			cin >> l >> r;
			int a, b, c;
			int t0 = tt;
			getrange(a, b, c, l, r);
			cout << 1ll * ans[b] * qpow((1ll * siz[b] * (siz[b] + 1) / 2) % P, P - 2) % P << "\n";
			tt = t0;
		} else {
			int l, r, x;
			cin >> l >> r >> x;
			int a, b, c;
			getrange(a, b, c, r, r+x);
			int aa, bb, cc;
			getrange(aa, bb, cc, l, l+x);
			rt = 0;
			merge(rt, aa, b);
			merge(rt, rt, cc);
		}

		if(q % 10000 == 0) rebuild();
	}

	// cerr << seed << "\n";
	
	return 0;
}
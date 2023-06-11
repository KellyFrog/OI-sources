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

mt19937_64 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

const int N = 2e5 + 5;
const int P = 998244353;

int qpow(int x, ll p) {
	int res = 1, base = x;
	while(p) {
		if(p & 1) res = 1ll * res * base % P;
		base = 1ll * base * base % P;
		p >>= 1;
	}
	return res;
}

int n, m, b[N];
int cnt[N<<2], val[N<<2];
int a[N], ans[N], t[N], pos[N];

inline void pushup(int o) {
	cnt[o] = cnt[o << 1] + cnt[o << 1 | 1];
	val[o] = (val[o << 1] + 1ll * b[cnt[o << 1]] * val[o << 1 | 1]) % P;
}

inline void build(int o, int l, int r) {
	if(l == r) {
		pos[l] = o;
		return;
	}
	int mid = l + r >> 1;
	build(o << 1, l, mid);
	build(o << 1 | 1, mid + 1, r);
}

void add(int x, int p) {
	int o = pos[x];
	cnt[o] += p;
	val[o] += p * x;
	o >>= 1;
	while(o) {
		pushup(o);
		o >>= 1;
	}
}

int cnt0, val0;

inline void query(int o, int ql, int qr, int l, int r) {
	if(ql <= l && r <= qr) {
		val0 = (val0 + 1ll * b[cnt0] * val[o]) % P;
		cnt0 += cnt[o];
		return;
	}
	int mid = l + r >> 1;
	if(ql <= mid) query(o << 1, ql, qr, l, mid);
	if(mid < qr) query(o << 1 | 1, ql, qr, mid + 1, r);
}

struct Q {
	int l, r, x, y, bel, id;
} qr[N];

void insert(int x) {
	if(t[x]++ == 0) add(x, 1);
}

void erase(int x) {
	if(--t[x] == 0) add(x, -1);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	freopen("ds.in", "r", stdin);
	freopen("ds.out", "w", stdout);

	int b0;
	cin >> n >> b0 >> m;
	b[0] = 1;
	rep(i, 1, n) b[i] = 1ll * b[i-1] * b0 % P;

	build(1, 1, n);

	rep(i, 1, n) cin >> a[i];
	int siz = sqrt(n);
	rep(i, 1, m) {
		int l, r, x, y;
		cin >> l >> r >> x >> y;
		qr[i] = {l, r, x, y, l / siz, i};
	}
	sort(qr + 1, qr + m + 1, [&](const Q& x, const Q& y) { return x.bel == y.bel ? (x.bel & 1) ? x.r > y.r : x.r < y.r : x.bel < y.bel; });
	int l = 1, r = 0;
	rep(i, 1, m) {
		// cerr << i << " " << qr[i].l << " " << qr[i].r << " " << qr[i].x << " " << qr[i].y << " " << qr[i].id << "\n";
		while(r < qr[i].r) insert(a[++r]);
		while(l > qr[i].l) insert(a[--l]);
		while(r > qr[i].r) erase(a[r--]);
		while(l < qr[i].l) erase(a[l++]);
		cnt0 = val0 = 0;
		query(1, qr[i].x, qr[i].y, 1, n);
		ans[qr[i].id] = val0;
	}
	rep(i, 1, m) cout << ans[i] << "\n";
	
	return 0;
}
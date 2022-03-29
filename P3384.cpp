#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <map>

using namespace std;

#define vc vector
#define pq priority_queue
#define grt greater
#define pb push_back
#define mp make_pair
#define rg register
#define fi first
#define se second
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef grt<int> gi;
typedef grt<ll> gll;
typedef grt<pii> gii;
typedef grt<pll> gpll;

namespace IO {
	const int SIZE = (1 << 20) + 1;
	char ibuf[SIZE], *iS, *iT, obuf[SIZE],*oS = obuf, *oT = obuf + SIZE - 1;
	char _st[55];
	int _qr = 0;
#ifdef ONLINE_JUDGE
	inline char gc() {
		return (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS++) : *iS++);
	}
#else
#define gc getchar
#endif
	inline void qread() {}
	template<class T1, class ...T2>
	inline void qread(T1 &IEE, T2&... ls) {
		rg T1 __ = 0, ___ = 1;
		rg char ch;
		while(!isdigit(ch = gc())) ___ = (ch == '-') ? -___ : ___;
		do {
			__ = (__ << 1) + (__ << 3) + (ch ^ 48);
		} while(isdigit(ch = gc()));
		__ *= ___;
		IEE = __;
		qread(ls...);
		return ;
	}
	template<class T>
	inline void qreadarr(T beg, T end) {
		while(beg != end) {
			qread(*beg);
			beg++;
		}
	}
	inline void flush() {
		fwrite(obuf, 1, oS - obuf, stdout);
		oS = obuf;
		return ;
	}
#ifdef ONLINE_JUDGE
	inline void putc_(char _x) {
		*oS++ = _x;
		if(oS == oT) flush();
	}
#else
#define putc_ putchar
#endif
	inline void qwrite() {}
	template<class T1, class ...T2>
	inline void qwrite(T1 IEE, T2... ls) {
		if(!IEE) putc_('0');
		if(IEE < 0) putc_('-'), IEE = -IEE;
		while(IEE) _st[++_qr] = IEE % 10 + '0', IEE /= 10;
		while(_qr) putc_(_st[_qr--]);
		qwrite(ls...);
		return ;
	}
	inline void putstr_(const char* IEE) {
		int p = 0;
		while(IEE[p] != '\0') {
			putc_(IEE[p++]);
		}
	}
	inline void puts_(const char* IEE) {
		putstr_(IEE);
		putc_('\n');
	}
	template<class T>
	inline void qwritearr(T beg, T end, const char * IEE = {" "}, const char * EE = {"\n"}) {
		while(beg != end) {
			qwrite(*beg);
			beg++;
			putstr_(IEE);
		}
		putstr_(EE);
	}
	struct Flusher_ {
		~Flusher_() {
			flush();
		}
	} io_flusher;
}
using namespace IO;

#define rep(i, s, t) for(rg int (i) = s; (i) <= t; (i)++)
#define per(i, s, t) for(rg int (i) = t; (i) >= s; (i)--)
#define all(x) x.begin(), x.end()
#define allrev(x) x.rbegin(), x.rend()

/*templates ends here*/

const int N = 1e5 + 5;
ll MOD;

int rt, n, m;
int head[N], to[N << 1], nxt[N << 1], tot;
ll wgt[N];
int siz[N], dfn[N], sgn[N], seg[N], dep[N], son[N], top[N], fat[N];
int dfncnt, sgncnt;
ll sum[N << 2], lazy[N << 2];

void Lazy(int cur, ll x, int l, int r) {
	lazy[cur] = (lazy[cur] + x) % MOD;
	sum[cur] = (sum[cur] + (r - l + 1) * x) % MOD;
}

void PushUp(int cur) {
	sum[cur] = (sum[cur << 1] + sum[cur << 1 | 1]) % MOD;
}

void PushDown(int cur, int l, int r) {
	int mid = l + r >> 1;
	Lazy(cur << 1, lazy[cur], l, mid);
	Lazy(cur << 1 | 1, lazy[cur], mid + 1, r);
	lazy[cur] = 0;
}

void Build(int cur, int l, int r) {
	if(l == r) {
		sum[cur] = seg[l];
		return;
	}
	int mid = l + r >> 1;
	Build(cur << 1, l, mid);
	Build(cur << 1 | 1, mid + 1, r);
	PushUp(cur);
}

void Add(int cur, int ql, int qr, ll x, int l, int r) {
	if(ql <= l && r <= qr) {
		Lazy(cur, x, l, r);
		return;
	}
	PushDown(cur, l, r);
	int mid = l + r >> 1;
	if(ql <= mid) Add(cur << 1, ql, qr, x, l, mid);
	if(mid < qr) Add(cur << 1 | 1, ql, qr, x, mid + 1, r);
	PushUp(cur);
}

ll Sum(int cur, int ql, int qr, int l, int r) {
	if(ql <= l && r <= qr) return sum[cur];
	PushDown(cur, l, r);
	int mid = l + r >> 1;
	ll res = 0;
	if(ql <= mid) res = (res + Sum(cur << 1, ql, qr, l, mid)) % MOD;
	if(mid < qr) res = (res + Sum(cur << 1 | 1, ql, qr, mid + 1, r)) % MOD;
	return res;
}

void AddEdge(int u, int v) {
	nxt[++tot] = head[u];
	to[tot] = v;
	head[u] = tot;
}

void Dfs1(int u, int fa) {
	fat[u] = fa;
	dfn[u] = ++dfncnt;
	siz[u] = 1;
	dep[u] = dep[fa] + 1;
	for(int i = head[u]; i; i = nxt[i]) {
		int v = to[i];
		if(v != fa) {
			Dfs1(v, u);
			siz[u] += siz[v];
			if(siz[v] > siz[son[u]]) son[u] = v;
		}
	}
}

void Dfs2(int u, int fa) {
	if(u == 0) return;
	top[u] = u == son[fa] ? top[fa] : u;
	sgn[u] = ++sgncnt;
	seg[sgncnt] = wgt[u];
	Dfs2(son[u], u);
	for(int i = head[u]; i; i = nxt[i]) {
		int v = to[i];
		if(v != fa && v != son[u]) {
			Dfs2(v, u);
		}
	}
}

ll RouteSum(int x, int y) {
	ll res = 0;
	while(top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		res = (res + Sum(1, sgn[top[x]], sgn[x], 1, n)) % MOD;
		x = fat[top[x]];
	}
	if(sgn[x] > sgn[y]) swap(x, y);
	res = (res + Sum(1, sgn[x], sgn[y], 1, n)) % MOD;
	return res;
}

void RouteAdd(int x, int y, ll z) {
	while(top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		Add(1, sgn[top[x]], sgn[x], z, 1, n);
		x = fat[top[x]];
	}
	if(sgn[x] > sgn[y]) swap(x, y);
	Add(1, sgn[x], sgn[y], z, 1, n);
}

ll SubtreeSum(int x) {
	return Sum(1, sgn[x], sgn[x] + siz[x] - 1, 1, n);
}

void SubtreeAdd(int x, int z) {
	Add(1, sgn[x], sgn[x] + siz[x] - 1, z, 1, n);
}

int main() {
	qread(n, m, rt, MOD);
	qreadarr(wgt + 1, wgt + 1 + n);
	rep(i, 1, n - 1) {
		int u, v;
		qread(u, v);
		AddEdge(u, v), AddEdge(v, u);
	}
	Dfs1(rt, 0), Dfs2(rt, 0);
	Build(1, 1, n);
	rep(i, 1, m) {
		int opt, x, y, z;
		qread(opt);
		if(opt == 1) qread(x, y, z), RouteAdd(x, y, z);
		else if(opt == 2) qread(x, y), printf("%lld\n", RouteSum(x, y));
		else if(opt == 3) qread(x, y), SubtreeAdd(x, y);
		else qread(x), printf("%lld\n", SubtreeSum(x));
	}
	return 0;
}

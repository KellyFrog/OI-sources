/*
	fhq£¬¹·¶¼²»Ð´£¨Îí
 */
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define fi first
#define se second
#define rg register
#define mp make_pair
#define pb push_back
#define pf push_front

#define rep(i, s, t) for (rg int i = s; i <= t; i++)
#define per(i, s, t) for (rg int i = t; i >= s; i--)
#define OK cerr << "OK!\n"

namespace fastio {
	const int SIZE = (1 << 20) + 1;
	char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = obuf + SIZE - 1;
	char _st[55];
	int _qr = 0;

	inline char getchar() {
		return (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin),
		        (iS == iT ? EOF : *iS++) : *iS++);
	}
	inline void qread() {}
	template <typename T1, typename... T2>
	inline void qread(T1 &x, T2 &...ls) {
		x = 0;
		rg char ch = ' ';
		rg int ps = 1;
		while (!isdigit(ch) && ch != '-') ch = getchar();
		if (ch == '-') ps = -1, ch = getchar();
		while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
		x *= ps;
		qread(ls...);
	}

	inline void flush() {
		fwrite(obuf, 1, oS - obuf, stdout);
		oS = obuf;
		return;
	}
	inline void putchar(char _x) {
		*oS++ = _x;
		if (oS == oT) flush();
	}
	template <typename T>
	inline void qwrite(T x) {
		if (x < 0) putchar('-'), x = -x;
		if (x < 10) return putchar('0' + x), void();
		qwrite(x / 10), putchar('0' + (x % 10));
	}

	template <typename T>
	inline void qwrite(T x, char ch) {
		qwrite(x), putchar(ch);
	}
};  // namespace fastio

#ifndef ONLINE_JUDGE

void debug(const char *s) {
	cerr << s;
}
template <typename T1, typename... T2>
void debug(const char *s, const T1 x, T2... ls) {
	int p = 0;
	while (*(s + p) != '\0') {
		if (*(s + p) == '{' && *(s + p + 1) == '}') {
			cerr << x;
			debug(s + p + 2, ls...);
			return;
		}
		cerr << *(s + p++);
	}
}

#else
#define debug(...) void(0)
#endif

ll qpow(ll x, ll p, ll mod) {
	rg ll base = x, res = 1;
	while (p) {
		if (p & 1) res = (res * base) % mod;
		base = (base * base) % mod;
		p >>= 1;
	}
	return res;
}

const int N = 1e5 + 5;
const int LOG = 20;


#define siz(x) tree[x].siz
#define son(x, p) tree[x].son[p]
#define lson(x) son(x, 0)
#define rson(x) son(x, 1)
#define revtag(x) tree[x].revtag
#define xortag(x) tree[x].xortag
#define fa(x) tree[x].fa
#define pos(x) (son(fa(x), 1) == x)
#define sum(x, p) tree[x].sum[p]
#define val(x, p) tree[x].val[p]
int n, q;
int a[N];

struct SplayNode {
	int fa, son[2], sum[20], val[20], siz, revtag, xortag;
	SplayNode() {
	}
};
SplayNode tree[N];

inline void setrev(int cur) {
	if(!cur) return;
	revtag(cur) ^= 1;
	swap(lson(cur), rson(cur));
}
inline void setxor(int cur, int val) {
	if(!cur) return;
	xortag(cur) ^= val;
	rep(i, 0, 19) if((val >> i) & 1) sum(cur, i) = siz(cur) - sum(cur, i), val(cur, i) ^= 1;
}

inline void pushdown(int cur) {
	if(revtag(cur)) {
		setrev(lson(cur));
		setrev(rson(cur));
		revtag(cur) = 0;
	}
	if(xortag(cur)) {
		setxor(lson(cur), xortag(cur));
		setxor(rson(cur), xortag(cur));
		xortag(cur) = 0;
	}
}
inline void pushup(int cur) {
	rep(i, 0, 19) {
		siz(cur) = siz(lson(cur)) + siz(rson(cur)) + 1;
		sum(cur, i) = sum(lson(cur), i) + sum(rson(cur), i) + val(cur, i);
	}
}
inline void connect(int cur, int fa, int p) {
	son(fa, p) = cur;
	fa(cur) = fa;
}
inline void rotate(int cur) {
	int fa = fa(cur);
	pushdown(fa);
	pushdown(cur);
	int pos = pos(cur);
	connect(cur, fa(fa), pos(fa));
	connect(son(cur, pos^1), fa, pos);
	connect(fa, cur, pos^1);
	pushup(fa);
	pushup(cur);
	pushup(fa(cur));
}
inline void splay(int from, int to) {
	to = fa(to);
	while(fa(from) != to) {
		int f = fa(from);
		if(fa(f) == to) {
			rotate(from);
		} else if(pos(from) == pos(f)) {
			rotate(f);
			rotate(from);
		} else {
			rotate(from);
			rotate(from);
		}
	}
}
#define rt lson(1)
#define sroot 1
int tot = 1;
void build(int& cur, int fa, int pos, int l, int r) {
	if(l > r) return;
	int mid = l + r >> 1;
	cur = ++tot;
	connect(cur, fa, pos);
	rep(i, 0, 19) val(cur, i) = (a[mid-1] >> i) & 1;
	siz(cur) = 1;
	build(lson(cur), cur, 0, l, mid - 1);
	build(rson(cur), cur, 1, mid + 1, r);
	pushup(cur);
}
void build() {
	build(rt, sroot, 0, 1, n+2);
}
inline int kth(int cur, int k) {
	pushdown(cur);
	if(k <= siz(lson(cur))) return kth(lson(cur), k);
	else if(k == siz(lson(cur)) + 1) return cur;
	else return kth(rson(cur), k - siz(lson(cur)) - 1);
}
inline void reverse(int L, int R) {
	L++, R++;
	int nd1 = kth(rt, L-1);
	int nd2 = kth(rt, R+1);
	splay(nd1, rt);
	splay(nd2, rson(rt));
	setrev(lson(nd2));
}
inline void modifyxor(int L, int R, int x) {
	L++, R++;
	int nd1 = kth(rt, L-1);
	int nd2 = kth(rt, R+1);
	splay(nd1, rt);
	splay(nd2, rson(rt));
	setxor(lson(nd2), x);
}
inline int querysum(int L, int R) {
	L++, R++;
	int nd1 = kth(rt, L-1);
	int nd2 = kth(rt, R+1);
	splay(nd1, rt);
	splay(nd2, rson(rt));
	ll res = 0;
	rep(i, 0, 19) res += (1ll << i) * sum(lson(nd2), i);
	return res;
}

int main() {
	fastio::qread(n, q);
	rep(i, 1, n) fastio::qread(a[i]);
	build();
	while(q--) {
		int op, L, R, x = -1;
		fastio::qread(op, L, R);
		if(op == 1) {
			reverse(L, R);
		} else if(op == 2) {
			fastio::qread(x);
			modifyxor(L, R, x);
		} else {
			ll ans = querysum(L, R);
			fastio::qwrite(ans, '\n');
		}
	}
	fastio::flush();
	return 0;
}
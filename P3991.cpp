// Happy Chinese new year! (Feb. 12th, 2021)

/*
 * Codeforces @Chenkaifeng
 * Luogu @longer_name
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

#if __cplusplus < 201703L
#define rg register
#else
#define rg
#endif

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

const ll mod = 1e9 + 7;
// const ll mod = 1e9 + 9;
// const ll mod = 19260817;
// const ll mod = 998244353;
// const int mod =2017;

template <typename T>
inline void chkadd(T& x, T y) {
	x = x + y >= mod ? x + y - mod : x + y;
}
template <typename T>
inline void chkadd(T& x, T y, T z) {
	x = y + z >= mod ? y + z - mod : y + z;
}
template <typename T>
inline void chkmns(T& x, T y) {
	x = x - y < 0 ? x - y + mod : x - y;
}
template <typename T>
inline void chkmns(T& x, T y, T z) {
	x = y - z < 0 ? y - z + mod : y - z;
}
template <typename T>
inline void chkmax(T& x, T y) {
	x = x < y ? y : x;
}
template <typename T>
inline void chkmax(T& x, T y, T z) {
	x = y > z ? y : z;
}
template <typename T>
inline void chkmin(T& x, T y) {
	x = x < y ? x : y;
}
template <typename T>
inline void chkmin(T& x, T y, T z) {
	x = y < z ? y : z;
}

ll qpow(ll x, ll p) {
	rg ll base = x, res = 1;
	while (p) {
		if (p & 1) res = (res * base) % mod;
		base = (base * base) % mod;
		p >>= 1;
	}
	return res;
}

// fhq? 狗都不写（雾

const int N = 1e5 + 5;

struct SplayNode {
	int fat, siz;
	int son[2];
	ll val[5][5];
	SplayNode(ll curval[], int fat0 = 0, int siz0 = 0, int lson = 0, int rson = 0) :
		fat(fat0), siz(siz0) {
		son[0] = lson;
		son[1] = rson;
		memset(val, 0, sizeof val);
		val[1][1] = curval[1];
		val[2][2] = curval[2];
		val[3][3] = curval[3];
		val[4][4] = curval[1];
	}
	SplayNode() {}
};

SplayNode tree[N];

#define fa(x) tree[x].fat
#define son(x, p) tree[x].son[p]
#define lson(x) son(x, 0)
#define rson(x) son(x, 1)
#define siz(x) tree[x].siz
#define val(x, i, j) tree[x].val[i][j]
#define pos(x) (rson(fa(x)) == x)

inline void PushUp(SplayNode& tar, SplayNode a, SplayNode b) {
	memset(tar.val, 0, sizeof tar.val);
	rep(i, 1, 4) tar.val[i][i] = a.val[i][i] + b.val[i][i];
	rep(i, 1, 4) rep(j, i+1, 4) rep(k, i, j) chkmax(tar.val[i][j], a.val[i][k] + b.val[k][j]);
	rep(i, 1, 4) {
		ll curmax = 0;
		rep(j, i, 4) {
			chkmax(curmax, tar.val[i][j]);
			chkmax(tar.val[i][j], curmax);
		}
	}
	tar.siz = a.siz + b.siz + 1;
}

void Connect(int cur, int fa, int p) {
	son(fa, p) = cur;
	fa(cur) = fa;
}

void Rotate(int cur) {
	int fa = fa(cur);
	int pos = pos(cur);
	Connect(cur, fa(fa), pos(fa));
	Connect(son(cur, pos ^ 1), fa, pos);
	Connect(fa, cur, pos ^ 1);
	PushUp(tree[fa], tree[lson(fa)], tree[rson(fa)]);
	PushUp(tree[cur], tree[lson(cur)], tree[rson(cur)]);
	PushUp(tree[fa(cur)], tree[lson(fa(cur))], tree[rson(fa(cur))]);
}

void Splay(int from, int to) {
	to = fa(to);
	while(fa(from) != to) {
		int f = fa(from);
		if(fa(f) == to) {
			Rotate(from);
		} else if(pos(from) == pos(f)) {
			Rotate(f), Rotate(from);
		} else {
			Rotate(from), Rotate(from);
		}
	}
}

int Kth(int cur, int k) {
	int left = size(lson(cur));
	int right = size(rson(cur));
	int mid = 1;
	if(k <= left) {
		return Kth(lson(cur), k);
	} else if(left < k && k <= left + mid) {
		return cur;
	} else {
		return Kth(rson(cur), k - left - mid);
	}
}

void Insert(int )

int main() {
	fastio::flush();
	return 0;
}

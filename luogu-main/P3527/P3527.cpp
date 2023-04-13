
// Problem: P3527 [POI2011]MET-Meteors
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3527
// Memory Limit: 64 MB
// Time Limit: 2500 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

//Author: Chenkaifeng

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

#define rep(i, s, t) for(rg int i = s; i <= t; i++)
#define per(i, s, t) for(rg int i = t; i >= s; i--)
#define OK cerr << "OK!\n"


namespace fastio {
	const int SIZE = (1 << 20) + 1;
	char ibuf[SIZE], *iS, *iT, obuf[SIZE],*oS = obuf, *oT = obuf + SIZE - 1;
	char _st[55];
	int _qr = 0;

	inline char getchar() {
		return (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS++) : *iS++);
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
		return ;
	}
	inline void putchar(char _x) {
		*oS++ = _x;
		if(oS == oT) flush();
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
}; //namespace fastio


void debug(const char* s) {
	cerr << s;
}
template<typename T1, typename ...T2>
void debug(const char * s, const T1 x, T2 ...ls) {
	int p = 0;
	while(*(s + p) != '\0') {
		if(*(s + p) == '{' && *(s + p + 1) == '}') {
			cerr << x;
			debug(s + p + 2, ls...);
			return;
		}
		cerr << *(s + p++);
	}
}

ll qpow(ll x, ll p, ll mod) {
	rg ll base = x, res = 1;
	while(p) {
		if(p & 1) res = (res * base) % mod;
		base = (base * base) % mod;
		p >>= 1;
	}
	return res;
}

const int N = 3e5 + 5;

struct Op {
	int l, r;
	ll x;
};

ll cost[N];
Op op[N];
vector<int> bel[N];
int ans[N], pos[N], tmp[N];
ll sum[N];
int n, m, q;

inline int lowbit(int x) {
	return x & (-x);
}

void Add(int x, ll p) {
	for(rg int x0 = x; x0 <= m; x0 += lowbit(x0)) {
		sum[x0] += p;
	}
}

void Add(int L, int R, ll x) {
	Add(L, x);
	if(R + 1 <= m) Add(R + 1, -x);
}

ll Sum(int x) {
	ll res = 0;
	for(rg int x0 = x; x0 > 0; x0 -= lowbit(x0)) res += sum[x0];
	return res;
}

void Solve(int ql, int qr, int l, int r) {
	if(ql > qr || l > r) return;
	if(l == r) {
		rep(i, ql, qr) ans[pos[i]] = l;
		return;
	}
	//debug("[solve]={} {} {} {} {}\n", ql, qr, l, r, l + r >> 1);
	rg int mid = l + r >> 1;
	rg int pl = ql, pr = qr;
	rep(i, l, mid) {
		rg int L = op[i].l, R = op[i].r;
		rg ll x = op[i].x;
		if(L > R) {
			Add(L, m, x);
			Add(1, R, x);
			//debug("[add] [{}, {}] and [{}, {}] = {}\n", L, m, 1, R, x);
		} else {
			Add(L, R, x);
			//debug("[add] [{}, {}] = {}\n", L, R, x);
		}
	}
	rep(i, ql, qr) {
		//debug("[query] pos={}\n", pos[i]);
		ll curres = 0, x = 0;
		for(int p : bel[pos[i]]) {
			x = Sum(p);
			curres += x;
			if(curres > cost[pos[i]]) break;
			//debug("[queried] a[{}] = {}\n", p, x);
		}
		if(curres < cost[pos[i]]) {
			cost[pos[i]] -= curres;
			tmp[pr--] = pos[i];
		} else {
			tmp[pl++] = pos[i];
			//ans[pos[i]] = l;
		}
	}
	
	rep(i, l, mid) {
		rg int L = op[i].l, R = op[i].r;
		rg ll x = op[i].x;
		if(L > R) {
			Add(L, m, -x);
			Add(1, R, -x);
			//debug("[add] [{}, {}] and [{}, {}] = {}\n", L, m, 1, R, x);
		} else {
			Add(L, R, -x);
			//debug("[add] [{}, {}] = {}\n", L, R, x);
		}
	}
	rep(i, ql, qr) pos[i] = tmp[i];
	if(l == r) return;
	Solve(ql, pl - 1, l, mid);
	Solve(pl, qr, mid + 1, r);
}

int main() {
	fastio::qread(n, m);
	rep(i, 1, m) {
		int x; fastio::qread(x);
		bel[x].pb(i);
	}
	rep(i, 1, n) fastio::qread(cost[i]);
	fastio::qread(q);
	rep(i, 1, q) fastio::qread(op[i].l, op[i].r, op[i].x);
	rep(i, 1, n) pos[i] = i;
	Solve(1, n, 1, q + 1);
	rep(i, 1, n) {
		if(ans[i] == q + 1) puts("NIE");
		else printf("%d\n", ans[i]);
	}
	fastio::flush();
	return 0;
}
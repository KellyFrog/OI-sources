
// Problem: P2605 [ZJOI2010]基站选址
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P2605
// Memory Limit: 125 MB
// Time Limit: 1000 ms ~ 5000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

//By luogu @longer_name

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

#define rep(i, s, t) for(int i = s; i <= t; i++)
#define per(i, s, t) for(int i = t; i >= s; i--)
#define debug(x) cerr << (#x) << " = " << (x) << "\n"
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
		char ch = ' ';
		int ps = 1;
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

ll qpow(ll x, ll p, ll mod) {
	ll base = x, res = 1;
	while(p) {
		if(p & 1) res = (res * base) % mod;
		base = (base * base) % mod;
		p >>= 1;
	}
	return res;
}

const int N = 2e4 + 5;
const int K = 105;
const ll inf = 1e18;

ll dp[N];
ll mi[N << 2], lazy[N << 2];
ll c[N], s[N], dis[N], w[N];
int n, k;
vector<pair<int, int> > st[N];

void Lazy(int cur, int x) {
	mi[cur] += x;
	lazy[cur] += x;
}

void PushDown(int cur) {
	Lazy(cur << 1, lazy[cur]);
	Lazy(cur << 1 | 1, lazy[cur]);
	lazy[cur] = 0;
}

void PushUp(int cur) {
	mi[cur] = min(mi[cur << 1], mi[cur << 1 | 1]);
}

void Build(int cur, int l, int r) {
	lazy[cur] = 0;
	if(l == r) return mi[cur] = dp[l], void();
	rg int mid = l + r >> 1;
	Build(cur << 1, l, mid);
	Build(cur << 1 | 1, mid + 1, r);
	PushUp(cur);
}

ll Query(int cur, int ql, int qr, int l, int r) {
	if(ql <= l && r <= qr) return mi[cur];
	PushDown(cur);
	rg int mid = l + r >> 1;
	rg ll res = inf;
	if(ql <= mid) res = min(res, Query(cur << 1, ql, qr, l, mid));
	if(mid < qr) res = min(res, Query(cur << 1 | 1, ql, qr, mid + 1, r));
	return res;
}

void Modify(int cur, int ql, int qr, int l, int r, ll x) {
	if(ql <= l && r <= qr) return Lazy(cur, x), void();
	PushDown(cur);
	rg int mid = l + r >> 1;
	if(ql <= mid) Modify(cur << 1, ql, qr, l, mid, x);
	if(mid < qr) Modify(cur << 1 | 1, ql, qr, mid + 1, r, x);
	PushUp(cur);
}

int main() {
	cin >> n;
	dis[0] = -inf, dis[n+1] = inf;
	rep(i, 1, n) {
		cin >> dis[i];
		w[i] = inf;
		cin >> c[i];
		cin >> s[i];
	}
	rep(i, 1, n) dis[i] -= dis[1];
	rep(i, 1, n) {
		int L = lower_bound(dis, dis + n + 1, dis[i] - s[i]) - dis;
		int R = upper_bound(dis, dis + n + 1, dis[i] + s[i]) - dis - 1;
		st[R].pb(mp(L, i));
	}
	ll res = 0, ans = inf;
		Build(1, 0, n);
		rep(i, 1, n) {
			dp[i] = Query(1, 0, i-1, 0, n) + c[i];
			for(auto x : st[i]) Modify(1, 0, x.fi - 1, 0, n, w[x.se]);
		}
		ans = min(ans, Query(1, 0, n, 0, n));
	fastio::qwrite(ans, '\n');
	fastio::flush();
	return 0;
}
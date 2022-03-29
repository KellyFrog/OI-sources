
// Problem: P6216 »ØÎÄÆ¥Åä
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6216?contestId=41161
// Memory Limit: 500 MB
// Time Limit: 1000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)


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

typedef unsigned int ui;

const int N = 3e6 + 5;

char S[N], T[N];
int R[N];
int nxt[N];
ll sum[N];
int n, m;

void Manacher() {
	int maxr = 0, mid = 0;
	rep(i, 1, n) {
		if(i <= maxr) R[i] = min(R[mid*2 - i], maxr - i + 1);
		while(S[i+R[i]] == S[i-R[i]] && i+R[i] <= n && i-R[i] > 0) R[i]++;
		if(i + R[i] > maxr) {
			maxr = i + R[i] - 1;
			mid = i;
		}
	}
	OK;
}

void KMP() {
	rep(i, 2, m) {
		int j = nxt[i-1];
		while(j && T[j+1] != T[i]) j = nxt[j];
		nxt[i] = T[j+1] == T[i] ? j+1 : 0;
	}
	int mj = 0;
	rep(i, 1, n) {
		while(mj && T[mj+1] != S[i]) mj = nxt[mj];
		if(T[mj+1] == S[i]) mj++;
		if(mj == m) {
			sum[i-m+1]++;
			mj = nxt[mj];
		}
	}
}

ll get(int l, int r) {
	if(l > r) return 0;
	r = min(r, n);
	l = max(l, 1);
	debug("[{},{}] = {} {} {}\n", l, r, sum[r] - sum[l-1], sum[l-1], sum[r]);
	return sum[r] - sum[l-1];
}

ll Calc(int x, int r) {
	return get(x, x + r - 1) - get(x - r + 1, x-1);
}

int main() {
	scanf("%d%d", &n, &m);
	scanf("%s%s", S+1, T+1);
	KMP();
	Manacher();
	ll ans = 0;
	rep(i, 1, n) sum[i] = sum[i-1] + sum[i];
	rep(i, 1, n) sum[i] = sum[i-1] + sum[i];
	rep(i, (m+1)/2, n) {
		if(R[i] * 2 - 1 < m) continue;
		ans += get(i-m+(m+1)/2, i-m+R[i]);
		ans -= get(i-R[i], i-(m+1)/2);
	}
	fastio::qwrite(ans % 4294967296ll, '\n');
	fastio::flush();
	return 0;
}
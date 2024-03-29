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
	template <typename T1>
	inline void qwrite(T1 x) {
		if (x < 0) putchar('-'), x = -x;
		if (x < 10) return putchar('0' + x), void();
		qwrite(x / 10), putchar('0' + (x % 10));
	}

	template <typename T1>
	inline void qwrite(T1 x, char ch) {
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

char S1[N], S2[N], T1[N], T2[N];
int nxt1[N], nxt2[N];
int mx1[N], mx2[N];
int n, m, q;

void KMP(char* S, int* nxt) {
	rep(i, 2, m) {
		int j = nxt[i-1];
		while(j && S[j+1] != S[i]) j = nxt[j];
		nxt[i] = S[j+1] == S[i] ? j+1 : 0;
	}
}

void Solve(char* S, char* T1, int* a, int* nxt) {
	int mj = 0;
	rep(i, 1, n) {
		while(mj && T1[mj+1] != S[i]) mj = nxt[mj];
		if(T1[mj+1] == S[i]) mj++;
		a[i] = max(a[i-1], mj);
		if(mj == m) mj = nxt[mj];
	}
}

int main() {
	scanf("%s", S1 + 1);
	n = strlen(S1 + 1);
	rep(i, 1, n) S2[i] = S1[n-i+1];
	scanf("%d", &q);
	int ans = 0;
	rep(i, 1, q) {
		scanf("%s", T1+1);
		m = strlen(T1+1);
		if(m == 1 || m > n) continue;
		rep(i, 1, m) T2[i] = T1[m-i+1];
		memset(mx1, 0, sizeof mx1);
		memset(nxt1, 0, sizeof nxt1);
		memset(nxt2, 0, sizeof nxt1);
		KMP(T1, nxt1);
		KMP(T2, nxt2);
		Solve(S1, T1, mx1, nxt1);
		Solve(S2, T2, mx2, nxt2);
		rep(i, 1, n) if(mx1[i] + mx2[n-i] >= m) {
			ans++;
			break;
		}
	}
	printf("%d\n", ans);
	return 0;
}
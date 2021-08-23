// Problem: P1117 [NOI2016] 优秀的拆分
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P1117
// Memory Limit: 512 MB
// Time Limit: 1500 ms
// 
// Powered by CP Editor (https://cpeditor.org)

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

const int N = 1e5 + 5;
const ll base = 131;
const ll mod = 1234567891;

ll delta1[N], delta2[N];
char S[N];
int n;
ll pw[N], hs[N];

inline ll gethash(int s, int t) {
	return ((hs[t] - pw[t-s+1] * hs[s-1]) % mod + mod) % mod;
}

inline bool check(int s1, int t1, int s2, int t2) {
	return gethash(s1, t1) == gethash(s2, t2);
}

void solve() {
	scanf("%s", S+1);
	debug("solve = {}\n", S+1);
	n = strlen(S+1);
	memset(delta1, 0, sizeof delta1);
	memset(delta2, 0, sizeof delta2);
	pw[0] = 1;
	rep(i, 1, n) pw[i] = pw[i-1] * base % mod;
	rep(i, 1, n) hs[i] = (base * hs[i-1] + S[i]) % mod;
	rep(i, 1, n) cerr << S[i] << " \n"[i == n];
	cerr << "  ";
	rep(i, 2, n) {
		int L = 1, R = min(i-1, n-i+1);
		int res = 0;
		while(L <= R) {
			int mid = L + R >> 1;
			if(check(i-mid, i-1, i, i+mid-1)) res = mid, L = mid + 1;
			else R = mid - 1;
		}
		cerr << res << " \n"[i == n];
		if(!res) continue;
		delta2[i]++, delta2[i+res]--;
		delta1[i-res]++, delta1[i]--;
	}
	rep(i, 1, n) delta1[i] += delta1[i-1], delta2[i] += delta2[i-1];
	rep(i, 1, n) cerr << delta1[i] << " \n"[i == n];
	rep(i, 1, n) cerr << delta2[i] << " \n"[i == n];
	
	ll ans = 0;
	rep(i, 1, n-2) ans += delta2[i] * delta1[i+1];
	printf("%lld\n", ans);
}

int main() {
	int t;
	scanf("%d", &t);
	while(t--) solve();
	fastio::flush();
	return 0;
}

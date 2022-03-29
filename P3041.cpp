// Problem: P3041 [USACO12JAN]Video Game G
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3041?contestId=45475
// Memory Limit: 125 MB
// Time Limit: 1000 ms
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

const int N = 500 + 5;
const int K = 1e3 + 5;
const int M = 27;

int son[N][27], fail[N], cnt[N], que[N], head = 1, tail, rt, tot;
char S[N];
int n, k;
int dp[N][K], ind[N][K];

void Insert(char* str) {
	int len = strlen(str + 1);
	if(rt == 0) rt = ++tot;
	int cur = rt;
	rep(i, 1, len) {
		if(!son[cur][str[i] - 'A']) son[cur][str[i] - 'A'] = ++tot;
		cur = son[cur][str[i] - 'A'];
	}
	cnt[cur] = 1;
}

void BuildFail() {
	fail[rt] = rt;
	rep(i, 0, 25) {
		if(son[rt][i]) {
			fail[son[rt][i]] = rt;
			que[++tail] = son[rt][i];
		} else {
			son[rt][i] = rt;
		}
	}
	while(head <= tail) {
		int cur = que[head++];
		rep(i, 0, 25) {
			if(son[cur][i]) {
				que[++tail] = son[cur][i];
				fail[son[cur][i]] = son[fail[cur]][i];
			} else {
				son[cur][i] = son[fail[cur]][i];
			}
		}
	}
	rep(i, 1, tot) cnt[que[i]] += cnt[fail[que[i]]];
}


int main() {
	scanf("%d%d", &n, &k);
	rep(i, 1, n) scanf("%s", S+1), Insert(S);
	BuildFail();
	memset(dp, -1, sizeof dp);
	dp[rt][0] = 0;
	queue<pair<int, int> > q;
	q.push(mp(rt, 0));
	while(q.front().se <= k) {
		int nd = q.front().fi, t = q.front().se;
		q.pop();
		rep(i, 0, 25) {
			if(dp[nd][t] + cnt[son[nd][i]] > dp[son[nd][i]][t+1]) {
				dp[son[nd][i]][t+1] = dp[nd][t] + cnt[son[nd][i]];
				if(!ind[son[nd][i]][t+1]) {
					ind[son[nd][i]][t+1] = 1;
					q.push(mp(son[nd][i], t+1));
				}
			}
		}
	}
	int ans = 0;
	rep(i, 1, tot) chkmax(ans, dp[i][k]);
	cout << ans << '\n';
  fastio::flush();
  return 0;
}

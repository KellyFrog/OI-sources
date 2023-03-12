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

const int N = 21;
const int M = 51;
const int LS = 11;
const int LT = 2e6 + 5;

int n, m;
char S[LS], T[LT];
int son[N*LS][27], endlen[N*LS], fail[N*LS], cnt, rt;

inline void insert(char* S) {
	int len = strlen(S + 1);
	if(!rt) rt = ++cnt;
	int cur = rt;
	rep(i, 1, len) {
		if(!son[cur][S[i]-'a']) son[cur][S[i]-'a'] = ++cnt;
		cur = son[cur][S[i]-'a'];
	}
	endlen[cur] |= 1 << len;
}

inline void buildfail() {
	static int que[N], head = 1, tail = 0;
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
		int u = que[head++];
		rep(i, 0, 25) {
			if(son[u][i]) {
				que[++tail] = son[u][i];
				fail[son[u][i]] = son[fail[u]][i];
			} else {
				son[u][i] = son[fail[u]][i];
			}
		}
	}
	rep(i, 1, cnt) endlen[que[i]] |= endlen[fail[que[i]]];
}

inline int solve() {
	static bool dp[LT];
	memset(dp, 0, sizeof dp);
	int ans = 0;
	dp[0] = 1;
	int len = strlen(T+1);
	int cur = rt;
	rep(i, 1, len) {
		cur = son[cur][T[i]-'a'];
		rep(j, 1, min(10, i)) if(endlen[cur] & (1 << j)) {
			if(dp[i-j]) {
				dp[i] = 1;
				break;
			}
		}
	}
	rep(i, 1, len) if(dp[i]) ans = i;
	return ans;
}

int main() {
	scanf("%d%d", &n, &m);
	rep(i, 1, n) scanf("%s", S+1), insert(S);
	buildfail();
	rep(i, 1, m) {
		scanf("%s", T+1);
		printf("%d\n", solve());
	}
 	fastio::flush();
 	return 0;
}
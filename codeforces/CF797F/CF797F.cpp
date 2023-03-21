
// Problem: CF797F Mice and Holes
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF797F
// Memory Limit: 250 MB
// Time Limit: 1500 ms
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

/*
 * dp[i][j] 表示前 i 个老鼠进了前 j 个洞的最小花费
 * 令 sum[i][j] 表示前 i 个老鼠到第 j 个洞的距离和
 * dp[i][j] = min(dp[i'][j-1] + sum[i][j]-sum[i'][j])
 * 单调队列维护 dp[i'][j-1]-sum[i'][j]
*/

const int N = 5005;

ll a[N];
pair<ll, ll> b[N];
ll sum[N], dp[N][2];
pair<ll, ll> que[N];
int head, tail;
int n, m;

int main() {
	memset(dp, 0x3f, sizeof dp);
	fastio::qread(n, m);
	rep(i, 1, n) fastio::qread(a[i]);
	rep(i, 1, m) fastio::qread(b[i].fi, b[i].se);
	int sumb = 0;
	rep(i, 1, m) sumb += b[i].se;
	if(n > sumb) return puts("-1"), 0;
	sort(a + 1, a + 1 + n);
	sort(b + 1, b + 1 + m);
	dp[0][0] = 0;
	rep(j, 1, m) {
		head = 1, tail = 0;
		rep(i, 1, n) sum[i] = sum[i-1] + abs(a[i] - b[j].fi);
		rep(i, 0, n) {
			while(head <= tail && que[tail].se > dp[i][(j+1)&1] - sum[i]) tail--;
			que[++tail] = mp(i, dp[i][(j+1)&1] - sum[i]);
			while(head <= tail && que[head].fi < i - b[j].se) head++;
			dp[i][j&1] = que[head].se + sum[i];
		}
	}
	fastio::qwrite(dp[n][(m&1)], '\n');
	fastio::flush();
	return 0;
}
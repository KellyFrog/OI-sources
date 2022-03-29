<<<<<<< HEAD
// Problem: P7519 [省选联考 2021 A/B 卷] 滚榜
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7519
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

/*
 * Author: chenkaifeng @BDFZ
 */
 
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define pf push_front
#define rep(i, s, t) for (int i = s; i <= t; ++i)
#define per(i, s, t) for (int i = t; i >= s; --i)

namespace nqio{const unsigned R=4e5,W=4e5;char*a,*b,i[R],o[W],*c=o,*d=o+W,h[40],*p=h,y;bool s;struct q{void r(char&x){x=a==b&&(b=(a=i)+fread(i,1,R,stdin),a==b)?-1:*a++;}void f(){fwrite(o,1,c-o,stdout);c=o;}~q(){f();}void w(char x){*c=x;if(++c==d)f();}q&operator>>(char&x){do r(x);while(x<=32);return*this;}q&operator>>(char*x){do r(*x);while(*x<=32);while(*x>32)r(*++x);*x=0;return*this;}template<typename t>q&operator>>(t&x){for(r(y),s=0;!isdigit(y);r(y))s|=y==45;if(s)for(x=0;isdigit(y);r(y))x=x*10-(y^48);else for(x=0;isdigit(y);r(y))x=x*10+(y^48);return*this;}q&operator<<(char x){w(x);return*this;}q&operator<<(char*x){while(*x)w(*x++);return*this;}q&operator<<(const char*x){while(*x)w(*x++);return*this;}template<typename t>q&operator<<(t x){if(!x)w(48);else if(x<0)for(w(45);x;x/=10)*p++=48|-(x%10);else for(;x;x/=10)*p++=48|x%10;while(p!=h)w(*--p);return*this;}}qio;}using nqio::qio;

#define OK debug("OK!\n")
#ifndef ONLINE_JUDGE
namespace debuger{void debug(const char *s) {cerr << s;}template<typename T1,typename... T2>void debug(const char*s, const T1 x, T2...ls) { int p=0; while(*(s + p)!='\0') {if(*(s+p)=='{'&&*(s+p+1)=='}'){cerr << x;debug(s + p + 2, ls...);return;}cerr << *(s + p++);}}}using debuger::debug;
#else
#define debug(...) void(0)
#endif

// const int mod = 1e9 + 7;
const int mod = 998244353;

int qpow(int x, ll p) {
	int res = 1, base = x;
	while(p) {
		if(p & 1) res = 1ll * res * base % mod;
		base = 1ll * base * base % mod;
		p >>= 1;
	}
	return res;
}

template<typename T> inline void upd(T& x, const T& y) {	x += y; }
template<typename T> inline void upd(T& x, const T& y, const T& z) { x = y + z; if(x >= mod) x -= mod; }

/* template ends here */

std::mt19937 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

const int N = 14;
const int M = 505;
const int H = 1 << 14 | 5;

ll f[H][N][M];
int n, m;
int a[N], cost[N][N];
int popcount[H];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> m;
	rep(i, 0, n-1) cin >> a[i];
	rep(i, 0, n-1) rep(j, 0, n-1) {
		if(a[i] < a[j]) {
			cost[i][j] = a[j] - a[i] + (i > j);
		} else if(a[i] == a[j]) {
			cost[i][j] = (i > j);
		}
	}
	int u = (1 << n) - 1;
	rep(s, 1, u) popcount[s] = (s & 1) + popcount[s>>1];
	int mxp = 0;
	rep(i, 0, n-1) if(a[i] > a[mxp]) mxp = i;
	rep(i, 0, n-1) if(n*cost[i][mxp] <= m) f[1<<i][i][m-n*cost[i][mxp]] = 1;
	rep(s, 1, u) {
		rep(i, 0, n-1) {
			if(s >> i & 1) continue;
			int ss = s | 1 << i;
			rep(j, 0, n-1) {
				if(s >> j & 1) {
					int x = cost[i][j];
					int jj = x * (n - popcount[s]);
					rep(k, jj, m) {
						upd(f[ss][i][k-jj], f[s][j][k]);
					}
				}
			}
		}
	}
	
	// rep(s, 1, u) rep(i, 0, n-1) rep(j, 0, m) if(f[s][i][j]) debug("f[{}][{}][{}] = {}\n", s, i, j, f[s][i][j]);
	
	ll ans = 0;
	rep(i, 0, n-1) rep(j, 0, m) {
		upd(ans, f[u][i][j]);
	}
	cout << ans << "\n";
	
	return 0;
}
=======

// Problem: P7519 [省选联考 2021 A/B 卷] 滚榜
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7519
// Memory Limit: 512 MB
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

const int N = 13;
const int M = 5e2 + 5;

ll dp[1 << N | 5][M];
int n, m, a[N], cost[N][N];

int main() {
	scanf("%d%d", &n, &m);
	rep(i, 1, n) scanf("%d", &a[i]);
	rep(i, 1, n) rep(j, 1, n) {
		cost[i][j] = max(0, a[i] - a[j] + (i < j));
		debug("cost[{}][{}] = {}\n", i, j, cost[i][j]);
	}
	dp[0][0] = 1;
	rep(S, 0, (1 << n) - 1) {
		rep(i, 1, n) {
			if(S & (1 << i - 1)) continue;
			int cur = 0, cnt = 1, S0 = S | (1 << i - 1);
			rep(j, 1, n) if(!(S0 & (1 << j - 1))) chkmax(cur, cost[j][i]), cnt++;
			rep(j, 0, m - cur * cnt) dp[S0][j + cur * cnt]  += dp[S][j], debug("{} {} -> {} {} = {} {}\n", S, j, S0, j + cur * cnt, dp[S][j], dp[S0][j + cur * cnt]); 
			
		}
		rep(i, 0, m) debug("dp[{}][{}] = {}\n", S, i, dp[S][i]);
	}
	ll ans = 0;
	rep(i, 0, m) ans += dp[(1 << n) - 1][i];
	cout << ans << "\n";
  fastio::flush();
  return 0;
}
>>>>>>> 2ca9f5c6ce8fc55b851f11a9f33d0133ca8c04ff

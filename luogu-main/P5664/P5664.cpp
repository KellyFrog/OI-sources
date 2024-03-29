// Problem: P5664 [CSP-S2019] Emiya 家今天的饭
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5664
// Memory Limit: 250 MB
// Time Limit: 1000 ms

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
#define rep(i, s, t) for (int i = s; i <= t; i++)
#define per(i, s, t) for (int i = t; i >= s; i--)

namespace nqio{const unsigned R=4e5,W=4e5;char*a,*b,i[R],o[W],*c=o,*d=o+W,h[40],*p=h,y;bool s;struct q{void r(char&x){x=a==b&&(b=(a=i)+fread(i,1,R,stdin),a==b)?-1:*a++;}void f(){fwrite(o,1,c-o,stdout);c=o;}~q(){f();}void w(char x){*c=x;if(++c==d)f();}q&operator>>(char&x){do r(x);while(x<=32);return*this;}q&operator>>(char*x){do r(*x);while(*x<=32);while(*x>32)r(*++x);*x=0;return*this;}template<typename t>q&operator>>(t&x){for(r(y),s=0;!isdigit(y);r(y))s|=y==45;if(s)for(x=0;isdigit(y);r(y))x=x*10-(y^48);else for(x=0;isdigit(y);r(y))x=x*10+(y^48);return*this;}q&operator<<(char x){w(x);return*this;}q&operator<<(char*x){while(*x)w(*x++);return*this;}q&operator<<(const char*x){while(*x)w(*x++);return*this;}template<typename t>q&operator<<(t x){if(!x)w(48);else if(x<0)for(w(45);x;x/=10)*p++=48|-(x%10);else for(;x;x/=10)*p++=48|x%10;while(p!=h)w(*--p);return*this;}}qio;}using nqio::qio;

#define OK debug("OK!\n");
#ifndef ONLINE_JUDGE
namespace debuger{void debug(const char *s) {cerr << s;}template<typename T1,typename... T2>void debug(const char*s, const T1 x, T2...ls) { int p=0; while(*(s + p)!='\0') {if(*(s+p)=='{'&&*(s+p+1)=='}'){cerr << x;debug(s + p + 2, ls...);return;}cerr << *(s + p++);}}}using debuger::debug;
#else
#define debug(...) void(0)
#endif

// const ll mod = 1e9 + 7;
const ll mod = 998244353;
template <typename T> inline void chkadd(T& x, T y) { x = x + y >= mod ? x + y - mod : x + y; }
template <typename T> inline void chkadd(T& x, T y, T z) { x = y + z >= mod ? y + z - mod : y + z; }
template <typename T> inline void chkmns(T& x, T y) { x = x - y < 0 ? x - y + mod : x - y; }
template <typename T> inline void chkmns(T& x, T y, T z) { x = y - z < 0 ? y - z + mod : y - z;}
template <typename T> inline void chkmax(T& x, T y) { x = x < y ? y : x; }
template <typename T> inline void chkmax(T& x, T y, T z) { x = y > z ? y : z; }
template <typename T> inline void chkmin(T& x, T y) { x = x < y ? x : y;}
template <typename T> inline void chkmin(T& x, T y, T z) { x = y < z ? y : z;}
ll qpow(ll x, ll p) { ll base = x, res = 1;	while (p) { if (p & 1) res = (res * base) % mod; base = (base * base) % mod; p >>= 1;} return res;}

/* template ends here */

const int N = 1e2 + 5;
const int M = 2e3 + 5;

int sum[N][M];
int a[N][M];
int n, m;
int dp[N][N<<1];
int ans1, ans2;

int main() {
	ios::sync_with_stdio(false); cin.tie(0), cout.tie(0); cout << fixed << setprecision(15); cerr << fixed << setprecision(15);
	
	cin >> n >> m;
	rep(i, 1, n) rep(j, 1, m) cin >> a[i][j];
	rep(i, 1, n) rep(j, 1, m) chkadd(sum[i][j], sum[i][j-1], a[i][j]);
	// rep(i, 1, n) cerr << sum[i][m] << " \n"[i == n];
	
	ans1 = 1;
	rep(i, 1, n) ans1 = 1ll * ans1 * (sum[i][m] + 1) % mod;
	ans1--; if(ans1 < 0) ans1 += mod;
	rep(c, 1, m) {
		memset(dp, 0, sizeof dp);
		dp[0][n] = 1;
		rep(i, 1, n) {
			rep(j, n-i, n+i) {
				dp[i][j] = (1ll * dp[i-1][j] + 1ll * dp[i-1][j-1] * a[i][c] + 1ll * dp[i-1][j+1] * (sum[i][m] - a[i][c])) % mod;
				if(dp[i][j] < 0) dp[i][j] += mod;
			}
		}
		rep(i, n+1, (n<<1)) chkadd(ans2, dp[n][i]);
	}
	
	int ans = ans1 - ans2;
	if(ans < 0) ans += mod;
	cout << ans << "\n";
	
	return 0;
}
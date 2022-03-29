// Problem: U178872 重开
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/U178872?contestId=52018
// Memory Limit: 256 MB
// Time Limit: 2000 ms
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

#define OK debug("OK!\n");
#ifndef ONLINE_JUDGE
namespace debuger{void debug(const char *s) {cerr << s;}template<typename T1,typename... T2>void debug(const char*s, const T1 x, T2...ls) { int p=0; while(*(s + p)!='\0') {if(*(s+p)=='{'&&*(s+p+1)=='}'){cerr << x;debug(s + p + 2, ls...);return;}cerr << *(s + p++);}}}using debuger::debug;
#else
#define debug(...) void(0)
#endif

const int mod = 1e9 + 7;
// const ll mod = 998244353;
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

const int N = 3e3 + 5;

int dp[N][N];
int fac[N], ifac[N];
int l[N], r[N];
int n, m;
vector<int> rpos[N];
pair<int, int> range[N]; int rp;
char S[N];
int pre[N];

int cnm(int n, int m) {
	if(n < 0 || m < 0) return 0;
	if(m < n) return 0;
	return 1ll * fac[m] * ifac[n] % mod * ifac[m-n] % mod;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> m;
	cin >> S+1;
	rep(i, 1, n) pre[i] = pre[i-1] + (S[i] == '1');
	ifac[0] = ifac[1] = fac[0] = fac[1] = 1;
	rep(i, 2, n) fac[i] = 1ll * fac[i-1] * i % mod;
	ifac[n] = qpow(fac[n], mod-2);
	per(i, 1, n-1) ifac[i] = 1ll * ifac[i+1] * (i+1) % mod;
	
	rep(i, 1, m) {
		cin >> l[i] >> r[i];
		rpos[l[i]].pb(r[i]);
	}
	
	int maxr = 0;
	rep(i, 1, n) {
		int mx = 0;
		for(int r : rpos[i]) {
			chkmax(mx, r);
		}
		if(mx > maxr) range[++rp] = mp(i, mx), maxr = mx;
	}
	
	range[0] = mp(0, range[1].fi-1);
	range[rp+1] = mp(n+1, n+1);
	
	dp[0][0] = 1;
	
	rep(i, 1, rp) {
		int L0 = range[i-1].fi;
		int R0 = range[i-1].se;
		int L1 = range[i].fi;
		int R1 = range[i].se;
		int L2 = range[i+1].fi;
		int R2 = range[i+1].se;
		rep(j, 0, n) {
			if(j>max(0, R1-L2+1)) break;
			int l = max(0, R0 - L1 + 1);
			int sm = pre[R1]-pre[max(L1-1, R0)];
			int us =  min(L2, R1+1) -L1;
			rep(k, 0, l) {
				dp[i][j] = (dp[i][j] + 1ll * dp[i-1][k] * cnm(k+sm-j,us)) % mod; 
			}
			// dp[i][j] = 1ll * dp[i][j] * cnm(j, R1-L2+1);
		}
	}
	
	cout << dp[rp][0] << "\n";
	return 0;
}

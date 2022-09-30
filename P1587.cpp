// Problem: P1587 [NOI2016] 循环之美
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P1587
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// Create Time: 2022-06-01 11:16:48
// Input/Output: stdin/stdout
// 
// Powered by CP Editor (https://cpeditor.org)

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

template<typename T> inline void upd(T& x, const T& y) {	x += y;	if(x >= mod) x -= mod; }
template<typename T> inline void upd(T& x, const T& y, const T& z) { x = y + z; if(x >= mod) x -= mod; }

/* template ends here */

mt19937_64 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

const int N = 1e6 + 5;
const int M = 2e3 + 5;

int n, m, k;
int mu[N], pre[N];
bool vis[N];
int g[M][M], cnt[M];
map<pair<int, int>, ll> f;
vector<int> fac;

ll calc(int n, int k) {
	if(n == 0) return 0;
	if(k == 1 && n <= (int)1e6) return pre[n];
	if(f.count(mp(n, k))) return f[mp(n, k)];
	ll ans = 0;
	if(k == 1) {
		ans = 1;
		for(int l = 2, r; l <= n; l = r + 1) {
			r = n / (n / l);
			ans -= 1ll * (r - l + 1) * calc(n/l, k);
		}
		
	} else {
		for(int d : fac) {
			if(mu[d] != 0 && k % d == 0) {
				ans += calc(n/d, d);
			}
		}
	}
	return f[mp(n, k)] = ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);


	mu[1] = 1;
	rep(i, 2, (int)1e6) {
		if(!vis[i]) {
			mu[i] = -1;
			for(int t = 2; i*t <= (int)1e6; ++t) {
				if(t % i == 0) mu[i*t] = 0;
				else mu[i*t] = -mu[t];
				vis[i*t] = 1;
			}
		}
	}
	rep(i, 1, (int)1e6) pre[i] = pre[i-1] + mu[i];


	cin >> n >> m >> k;

	rep(i, 0, k) g[i][0] = g[0][i] = i;
	rep(i, 1, k) rep(j, 1, k) g[i][j] = g[j%i][i];
	rep(i, 1, k) cnt[i] = cnt[i-1] + (g[k][i] == 1);
	
	rep(i, 1, k) if(k % i == 0) fac.pb(i);

	ll ans = 0;
	for(int l = 1, r; l <= n && l <= m; l = r + 1) {
		r = min(n / (n/l), m / (m/l)); 
		int p = m / l;
		ans += (calc(r, k) - calc(l-1, k)) * (n / l) * ((p/k) * cnt[k] + cnt[p%k]);
	}

	cout << ans << "\n";

	return 0;
}
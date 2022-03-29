// Problem: P1973 [NOI2011] NOI 嘉年华
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P1973
// Memory Limit: 128 MB
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

template<typename T> inline void upd(T& x, const T& y) {	x += y;	if(x >= mod) x -= mod; }
template<typename T> inline void upd(T& x, const T& y, const T& z) { x = y + z; if(x >= mod) x -= mod; }

/* template ends here */

std::mt19937 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

const int N = 405;

int n, m;
int l[N], r[N], a[N], p;
int f[N][N], g[N][N], ans[N][N];
int cnt[N][N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n;
	rep(i, 1, n) cin >> l[i] >> r[i], r[i] += l[i], a[++p] = l[i], a[++p] = r[i];
	sort(a + 1, a + 2 * n + 1);
	m = unique(a + 1, a + 2 * n + 1) - a - 1;
	rep(i, 1, n) {
		l[i] = lower_bound(a + 1, a + m + 1, l[i]) - a;
		r[i] = lower_bound(a + 1, a + m + 1, r[i]) - a;
	}
	rep(a, 0, m+1) rep(b, 0, m+1) {
		rep(i, 1, n) if(a <= l[i] && r[i] <= b) ++cnt[a][b];
	}
	memset(f, 0xf3, sizeof f);
	f[0][0] = 0;
	rep(i, 1, m) rep(j, 0, n) {
		rep(k, 0, i-1) {
			if(cnt[k][i] <= j) {
				f[i][j] = max(f[i][j], f[k][j-cnt[k][i]]);
			}
			f[i][j] = max(f[i][j], f[k][j] + cnt[k][i]);
		}
	}
	
	memset(g, 0xf3, sizeof g);
	g[m+1][0] = 0;
	per(i, 1, m) rep(j, 0, n) {
		rep(k, i+1, m+1) {
			if(cnt[i][k] <= j) {
				// debug("get trans i")
				g[i][j] = max(g[i][j], g[k][j-cnt[i][k]]);
			}
			g[i][j] = max(g[i][j], g[k][j] + cnt[i][k]);
		}
	}
	
	int res = 0;
	rep(i, 1, n) res = max(res, min(i, f[m][i]));
	cout << res << "\n";
	
	memset(ans, 0xf3, sizeof ans);
	
	rep(a, 1, m) rep(b, a, m) {
		if(cnt[a][b] == 0) continue;
		rep(x, 0, n) {
			if(f[a][x] < 0) continue;
			rep(y, 0, n-x) {
				if(g[b][y] < 0) continue;
				int val = max(min(x + y + cnt[a][b], f[a][x] + g[b][y]), min(x + y, f[a][x] + g[b][y] + cnt[a][b]));
				ans[a][b] = max(ans[a][b], val);
			}
		}
	}
	
	per(len, 2, m) {
		rep(i, 1, m) {
			int j = i + len - 1;
			if(j > m) break;
			auto upd = [&](int i, int j, int x) {
				if(ans[i][j] < x) ans[i][j] = x;
			};
			upd(i+1, j, ans[i][j]);
			upd(i, j-1, ans[i][j]);
		}
	}
	
	rep(i, 1, n) cout << ans[l[i]][r[i]] << "\n";
	
	return 0;
}

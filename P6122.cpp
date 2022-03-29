// Problem: P6122 [NEERC2016]Mole Tunnels
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6122
// Memory Limit: 125 MB
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

const int N = 3e5 + 5;
const int inf = 0x3f3f3f3f;

int n, m;
int c[N], p[N];
int f[N], pos[N], cnt1[N], cnt2[N], t[N];
int ans;

void update(int x) {
	int vl = cnt1[x<<1] ? f[x<<1] - 1 : f[x<<1] + 1;
	int vr = cnt1[x<<1|1] ? f[x<<1|1] - 1 : f[x<<1|1] + 1;
	if(c[x] > 0) {
		f[x] = 0, pos[x] = x;
	} else {
		f[x] = inf, pos[x] = -1;
	}
	if(f[x] > vl) f[x] = vl, pos[x] = pos[x<<1];
	if(f[x] > vr) f[x] = vr, pos[x] = pos[x<<1|1];
}

void updater(int x) {
	while(x) {
		update(x);
		x >>= 1;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> m;
	rep(i, 1, n) cin >> c[i];
	rep(i, 1, m) cin >> p[i];
	
	memset(f, 0x3f, sizeof f);
	
	per(i, 1, n) update(i);
	
	
	rep(i, 1, m) {
		int x = p[i];
		int mi = f[x], mpos = pos[x];
		int lca = x;
		
		// debug("mi = {}\n", mi);
		
		while(x >> 1) {
			int cur = f[x^1] + (cnt2[x] ? -1 : 1) + (cnt1[x^1] ? -1 : 1);
			if(cur < mi) {
				mi = cur;
				mpos = pos[x^1];
				lca = x>>1;
				// debug("get cur = {}, mi = {}\n", cur, mi);
			}
			x >>= 1;
		}
		
		--c[mpos];
		
		// debug("p[{}] = {}, mi = {}, mpos = {}, lca = {}\n", i, p[i], mi, mpos, lca);
		
		int a = p[i], b = mpos;
		while(a != lca) {
			if(cnt2[a]) --ans, --cnt2[a];
			else ++ans, ++cnt1[a];
			a >>= 1;
		}
		while(b != lca) {
			if(cnt1[b]) --ans, --cnt1[b];
			else ++ans, ++cnt2[b];
			b >>= 1;
		}
		
		assert(mpos != -1);
		
		updater(p[i]);
		updater(mpos);
		
		cout << ans << " \n"[i == m];
	}
	
	return 0;
}

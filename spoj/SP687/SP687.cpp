// Problem: SP687 REPEATS - Repeats
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/SP687
// Memory Limit: 1500 MB
// Time Limit: 1985 ms
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

const int N = 1e5 + 5;

char s[N];
int n, p, sa[N], rk[N], height[N];

int oldrk[N<<1], id[N], px[N], cnt[N];
int lg2[N], st[21][N];
inline bool cmp(int x, int y, int w) {
	return oldrk[x] == oldrk[y] && oldrk[x+w] == oldrk[y+w];
}

void buildSA(int n) {	
	int i, m = 300, p, w;
	
	memset(cnt, 0, sizeof cnt);
	
	for (i = 1; i <= n; ++i) ++cnt[rk[i] = s[i]];
	for (i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
	for (i = n; i >= 1; --i) sa[cnt[rk[i]]--] = i;

	for (w = 1;; w <<= 1, m = p) {
		for (p = 0, i = n; i > n - w; --i) id[++p] = i;
		for (i = 1; i <= n; ++i)
			if (sa[i] > w) id[++p] = sa[i] - w;
		memset(cnt, 0, sizeof(cnt));
		for (i = 1; i <= n; ++i) ++cnt[px[i] = rk[id[i]]];
		for (i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
		for (i = n; i >= 1; --i) sa[cnt[px[i]]--] = id[i];
		memcpy(oldrk, rk, sizeof(rk));
		for (p = 0, i = 1; i <= n; ++i)
			rk[sa[i]] = cmp(sa[i], sa[i - 1], w) ? p : ++p;
		if (p == n) {
			for (int i = 1; i <= n; ++i) sa[rk[i]] = i;
			break;
		}
	}
}

void buildH(int n) {
	int p = 0;
	for(int i = 1; i <= n; ++i) {
		if(p) --p;
		while(i+p <= n && sa[rk[i]-1] + p <= n && s[i+p] == s[sa[rk[i]-1]+p]) ++p;
		height[rk[i]] = p;
	}
}

void buildST(int n) {
	lg2[0] = -1;
	for(int i = 1; i <= n; ++i) lg2[i] = lg2[i>>1] + 1;
	for(int i = 1; i <= n; ++i) st[0][i] = height[i];
	for(int j = 1; j <= 20; ++j) {
		for(int i = 1; i <= n; ++i) {
			if(i + (1 << j) - 1 > n) break;
			st[j][i] = min(st[j-1][i], st[j-1][i+(1<<(j-1))]);
		}
	}
}

inline int queryST(int l, int r) {
	int j = lg2[r-l+1];
	return min(st[j][l], st[j][r-(1<<j)+1]);
}

inline int LCP(int x, int y) {
	// debug("LCP {} {}\n", x, y);
	if(x == y) return p+1;
	int l = rk[x], r = rk[y];
	// debug("[{}, {}]\n", l, r);
	if(l > r) swap(l, r);
	return queryST(l+1, r);
}

inline void getrange(int p, int len, int& tx, int& ty) {
	p = rk[p];
	tx = ty = p;
	if(height[p] >= len) {
		int L = 1, R = p-1;
		while(L <= R) {
			int mid = (L + R) >> 1;
			if(queryST(mid+1, p) >= len) {
				R = mid - 1;
				tx = mid;
			} else {
				L = mid + 1;
			}
		}
	}
	if(height[p+1] >= len) {
		int L = p+1, R = n;
		while(L <= R) {
			int mid = (L + R) >> 1;
			if(queryST(p+1, mid) >= len) {
				L = mid + 1;
				ty = mid;
			} else {
				R = mid - 1;
			}
		}
	}
}

void solve() {
	cin >> n;
	rep(i, 1, n) cin >> s[i];
	s[n+1] = '#';
	rep(i, n+2, 2*n+1) s[i] = s[2*n+2 - i];
	p = 2*n+1;
	
	buildSA(p);
	buildH(p);
	buildST(p);
	
	int ans = 0;
	
	rep(i, 1, p) debug("sa[{}] = {}, h = {}, str = {}\n", i, sa[i], height[i], &s[sa[i]]);
	
	rep(len, 1, n) {
		for(int i = 1; i <= n;) {
			int j = i;
			
			while(j <= n && LCP(i, j) >= len) j += len;
			j -= len;
			
			auto getrev = [&](int x) {
				return p+1-x;
			};
			
			int l = i==1 ? 0 : LCP(getrev(j+len-1), getrev(i-1));			
			int r = i+len>=n ? 0 : LCP(j+len, i);
			
			int curres = j+len-i;
			if(l + r >= len) curres += len;
				ans = max(ans, curres / len);
			
				// debug("ans = {} for len = {}, i = {} j = {}, l = {} r = {}\n", curres, len, i, j, l, r);
				// debug("solvel, {} {} {} {} {}\n", getrev(j+len-1), &s[getrev(j+len-1)], getrev(i-1), &s[getrev(i-1)], l);
			
			
			i = j + len;
		}
	}
	cout << ans << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	int t;
	cin >> t;
	while(t--) solve();
	
	return 0;
}

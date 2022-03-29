// Problem: P5546 [POI2000]公共串
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5546
// Memory Limit: 128 MB
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

const int N = 1e4 + 5;

string str[N];
int n, p;
char s[N];
int sa[N], rk[N], h[N], cnt[N], oldrk[N], px[N], id[N], hst[22][N], lg2[N];
int bel[N];

void buildSA(int n, const char* s) {
	int m = 300, p = 0;
	memset(cnt, 0, sizeof cnt);
	rep(i, 1, n) ++cnt[s[i]], rk[i] = s[i];
	rep(i, 1, m) cnt[i] += cnt[i-1];
	per(i, 1, n) sa[cnt[rk[i]]--] = i;
	
	for(int w = 1;; w <<= 1, m = p) {
		p = 0;
		per(i, n - w + 1, n) id[++p] = i;
		rep(i, 1, n) if(sa[i] > w) id[++p] = sa[i] - w;
		memset(cnt, 0, sizeof cnt);
		rep(i, 1, n) ++cnt[px[i] = rk[id[i]]];
		rep(i, 1, m) cnt[i] += cnt[i-1];
		per(i, 1, n) sa[cnt[px[i]]--] = id[i];
		memcpy(oldrk, rk, sizeof rk);
		
		auto compare = [&](int x, int y, int w) {
			return oldrk[x] == oldrk[y] && oldrk[x+w] == oldrk[y+w];
		};
		
		p = 0;
		rep(i, 1, n) rk[sa[i]] = compare(sa[i], sa[i-1], w) ? p : ++p;
		if(p == n) break;
	}
	rep(i, 1, n) sa[rk[i]] = i;
}

void buildH(int n) {
	int p = 0;
	rep(i, 1, n) {
		if(p) --p;
		while(i+p <= n && sa[rk[i]-1]+p <= n && s[i+p] == s[sa[rk[i]-1]+p]) ++p;
		h[rk[i]] = p;
	}
}

void buildST(int n) {
	rep(i, 1, n) hst[0][i] = h[i];
	rep(j, 1, 21) rep(i, 1, n) {
		if(i+(1<<j)-1 > n) break;
		hst[j][i] = min(hst[j-1][i], hst[j-1][i+(1<<j-1)]);
	}
	rep(i, 0, n) lg2[i] = i ? lg2[i>>1] + 1 : -1;
}

inline int queryST(int l, int r) {
	int j = lg2[r-l+1];
	debug("queryST({}, {}) = {}, j = {}, {} {}\n", l, r,  min(hst[j][l], hst[j][r-(1<<j)+1]), j, hst[j][l], hst[j][r-(1<<j)+1]);
	return min(hst[j][l], hst[j][r-(1<<j)+1]);
}

inline int lcp(int x, int y) {
	if(x == y) return n - x + 1;
	x = rk[x], y = rk[y];
	if(x > y) swap(x, y);
	return queryST(x+1, y);
}

inline pair<int, int> getrange(int p, int len, int n) { // p is a rk
	int ra = p, rb = p;
	int L = 1, R = p-1;
	while(L <= R) {
		int mid = L+R >> 1;
		if(queryST(mid+1, p) >= len) ra = mid, R = mid-1;
		else L = mid+1;
	}
	L = p+1, R = n;
	while(L <= R) {
		int mid = L+R >> 1;
		if(queryST(p+1, mid) >= len) rb = mid, L = mid+1;
		else R = mid-1;
	}
	return mp(ra, rb);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n;
	rep(i, 1, n) {
		cin >> str[i];
		for(auto c : str[i]) s[++p] = c, bel[p] = i;
		s[++p] = '#' + i;
	}
	
	buildSA(p, s);
	buildH(p);
	buildST(p);
	
	memset(cnt, 0, sizeof cnt);
	
	debug("s = {}\n", s+1);
	rep(i, 1, p) debug("sa[{}] = {}, h = {}, str = {}\n", i, sa[i], h[i], &s[sa[i]]);
	
	int pt = 1, t = 0;
	int ans = 0;
	rep(i, 1, p) {
		while(t < n && pt+1 <= p) {
			++pt;
			if(!cnt[bel[sa[pt]]]) ++t;
			++cnt[bel[sa[pt]]];
		}
		debug("get pt = {} for i = {}\n", pt, i);
		if(t == n) ans = max(ans, queryST(i+1, pt));
		
		--cnt[bel[sa[i]]];
		if(!cnt[bel[sa[i]]]) --t;
	}
	
	cout << ans << "\n";
	
	return 0;
}

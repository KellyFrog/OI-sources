// Problem: P7514 [省选联考 2021 A/B 卷] 卡牌游戏
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7514
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// Create Time: 2022-03-16 16:49:58
// Author: Chen Kaifeng
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

const int N = 2e6 + 5;

int n, m;
int a[N], b[N];
pair<int, int> c[N];
bool vis[N], visa[N], visb[N];
int cnt1, cnt2;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> m;
	rep(i, 1, n) cin >> a[i];
	rep(i, 1, n) cin >> b[i];
	
	rep(i, 1, n) c[i] = mp(a[i], i);
	rep(i, 1, n) c[i+n] = mp(b[i], -i);
	
	sort(c + 1, c + 2 * n + 1);
	
	int j = 0;
	int ans = 1e9;
	
	rep(i, 1, 2*n) {
		while(j < 2*n && (cnt1 < n || cnt2 < n - m)) {
			++j;
			if(c[j].se > 0) {
				visa[c[j].se] = 1, ++cnt2;
				if(!vis[c[j].se]) vis[c[j].se] = 1, ++cnt1;
			} else {
				visb[-c[j].se] = 1;
				if(!vis[-c[j].se]) vis[-c[j].se] = 1, ++cnt1;
			}
		}
		if(cnt1 == n && cnt2 >= n - m) {
			ans = min(ans, c[j].fi - c[i].fi);
		}
		if(c[i].se > 0) {
			visa[c[i].se] = 0;
			--cnt2;
			if(!(vis[c[i].se] = visa[c[i].se] || visb[c[i].se])) --cnt1;
		} else {
			visb[-c[i].se] = 0;
			if(!(vis[-c[i].se] = visa[-c[i].se] || visb[-c[i].se])) --cnt1;
		}
	}
	
	cout << ans << "\n";
	
	return 0;
}


// Problem: CF1202E You Are Given Some Strings...
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1202E
// Memory Limit: 250 MB
// Time Limit: 3000 ms
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

const int N = 1e6 + 5;

char s[N], t[N];
int n, m;
int ans1[N], ans2[N];

struct ACAuto {
	int son[N][26];
	int fail[N], cnt[N];
	int que[N], ph, pt;
	int rt, tot;
	
	ACAuto() : rt(1), tot(1), ph(1), pt(0) {
		memset(cnt, 0, sizeof cnt);
		memset(son, 0, sizeof son);
		memset(fail, 0, sizeof fail);
	}
	
	void insert(const char* ss) {
		int len = strlen(ss + 1);
		int cur = rt;
		rep(i, 1, len) {
			if(!son[cur][ss[i]-'a']) son[cur][ss[i]-'a'] = ++tot;
			cur = son[cur][ss[i]-'a'];
		}
		++cnt[cur];
	}
	
	void buildfail() {
		rep(i, 0, 25) {
			if(son[rt][i]) {
				fail[son[rt][i]] = rt;
				que[++pt] = son[rt][i];
			} else {
				son[rt][i] = rt;
			}
		}
		while(ph <= pt) {
			int u = que[ph++];
			cnt[u] += cnt[fail[u]];
			rep(i, 0, 25) {
				if(son[u][i]) {
					fail[son[u][i]] = son[fail[u]][i];
					que[++pt] = son[u][i];
				} else {
					son[u][i] = son[fail[u]][i];
				}
			}
		}
	}
} a1, a2;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> t+1;
	n = strlen(t+1);
	cin >> m;
	rep(i, 1, m) {
		cin >> s+1;
		int len = strlen(s+1);
		a1.insert(s);
		reverse(s+1, s+len+1);
		a2.insert(s);
	}
	
	a1.buildfail();
	a2.buildfail();
	
	int cur = a1.rt;
	rep(i, 1, n) {
		cur = a1.son[cur][t[i]-'a'];
		ans1[i] = a1.cnt[cur];
	}
	cur = a2.rt;
	per(i, 1, n) {
		cur = a2.son[cur][t[i]-'a'];
		ans2[i] = a2.cnt[cur];
	}
	ll ans = 0;
	rep(i, 1, n-1) ans += 1ll * ans1[i] * ans2[i+1];
	cout << ans << "\n";
	
	return 0;
}

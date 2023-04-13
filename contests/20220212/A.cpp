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

std::mt19937 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

/* template ends here */

const int N = 2e5 + 5;

char op[N];
int ls[N], rs[N], id[N], ncnt, icnt, rt, ans[N];
int f[N][2], h[N];
int n, m;
char s[N];
int stk[N], top, mat[N];
int inv2 = qpow(2, mod-2);

inline void dfs1(int& rt, int l, int r) {
	rt = ++ncnt;
	if(l == r) {
		f[rt][0] = f[rt][1] = inv2;
		op[rt] = 'x';
		id[rt] = ++icnt;
		return;
	}
	int l1, r1, l2, r2;
	if(r - l + 1 == 5) {
		l1 = r1 = l+1;
		l2 = r2 = r-1;
	} else {
		l1 = l+1, r2 = r-1;
		r1 = mat[l1], l2 = mat[r2];
	}
	
	assert(r1 + 1 == l2 - 1);
	int mid = r1 + 1;
	op[rt] = s[mid];
	
	dfs1(ls[rt], l1, r1);
	dfs1(rs[rt], l2, r2);
	
	if(op[rt] == '&') {
		f[rt][1] = 1ll * f[ls[rt]][1] * f[rs[rt]][1] % mod;
		f[rt][0] = (mod+1 - f[rt][1]);
	} else if(op[rt] == '|') {
		f[rt][0] = 1ll * f[ls[rt]][0] * f[rs[rt]][0] % mod;
		f[rt][1] = (mod+1 - f[rt][0]);
	} else if(op[rt] == '^') {
		f[rt][1] = (1ll * f[ls[rt]][0] * f[rs[rt]][1] + 1ll * f[ls[rt]][1] * f[rs[rt]][0]) % mod;
		f[rt][0] = (1+mod - f[rt][1]) % mod;
	}
	
}

inline void dfs2(int rt) {
	
	if(!ls[rt] && !rs[rt]) {
		cout << h[rt] << "\n";
		return;
	}
	if(op[rt] == '&') {
		h[ls[rt]] = 1ll * h[rt] * f[rs[rt]][1] % mod;
		h[rs[rt]] = 1ll * h[rt] * f[ls[rt]][1] % mod;
		// auto update = [&](int x, int y) {
			// g[x][0][0] = g[rt][0][0];
			// g[x][0][1] = g[rt][0][1];
			// g[x][1][0] = (1ll * g[rt][0][0] * f[y][0] + 1ll * g[rt][1][0] * f[y][1]) % mod;
			// g[x][1][1] = (1ll * g[rt][0][1] * f[y][0] + 1ll * g[rt][1][1] * f[y][1]) % mod;
		// };
		// update(ls[rt], rs[rt]);
		// update(rs[rt], ls[rt]);
	} else if(op[rt] == '|') {
		h[ls[rt]] = 1ll * h[rt] * f[rs[rt]][0] % mod;
		h[rs[rt]] = 1ll * h[rt] * f[ls[rt]][0] % mod;
		// auto update = [&](int x, int y) {
			// g[x][0][0] = (1ll * g[rt][0][0] * f[y][0] + 1ll * g[rt][1][0] * f[y][1]) % mod;
			// g[x][0][1] = (1ll * g[rt][0][1] * f[y][0] + 1ll * g[rt][1][1] * f[y][1]) % mod;
			// g[x][1][0] = g[rt][1][0];
			// g[x][1][1] = g[rt][1][1];
		// };
		// update(ls[rt], rs[rt]);
		// update(rs[rt], ls[rt]);
	} else {
		h[ls[rt]] = h[rs[rt]] = h[rt];
		// auto update = [&](int x, int y) {
			// g[x][0][0] = (1ll * g[rt][0][0] * f[y][0] + 1ll * g[rt][1][0] * f[y][1]) % mod;
			// g[x][0][1] = (1ll * g[rt][0][1] * f[y][0] + 1ll * g[rt][1][1] * f[y][1]) % mod;
			// g[x][1][0] = (1ll * g[rt][0][0] * f[y][1] + 1ll * g[rt][1][0] * f[y][0]) % mod;
			// g[x][1][1] = (1ll * g[rt][0][1] * f[y][1] + 1ll * g[rt][1][1] * f[y][0]) % mod;
		// };
		// update(ls[rt], rs[rt]);
		// update(rs[rt], ls[rt]);
	}
	dfs2(ls[rt]);
	dfs2(rs[rt]);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n;
	cin >> (s+1);
	m = strlen(s+1);
	
	rep(i, 1, m) {
		if(s[i] == '(') stk[++top] = i;
		else if(s[i] == ')') {
			int x = stk[top--];
			mat[x] = i, mat[i] = x;
		}
	}
	
	dfs1(rt, 1, m);
	
	h[1] = 1;
	
	dfs2(rt);
	
	return 0;
}

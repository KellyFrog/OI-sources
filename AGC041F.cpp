// Problem: AT5697 [AGC041F] Histogram Rooks
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT5697
// Memory Limit: 1000 MB
// Time Limit: 4000 ms
// Create Time: 2022-06-15 21:41:46
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
const int P = 998244353;

int qpow(int x, ll p) {
	int res = 1, base = x;
	while(p) {
		if(p & 1) res = 1ll * res * base % P;
		base = 1ll * base * base % P;
		p >>= 1;
	}
	return res;
}

/* template ends here */

mt19937_64 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

const int N = 405;

int n, p[N];
int rt, ls[N], rs[N];
int stk[N], top;
int f[N][N][2], siz[N];

inline void dfs(int u, int fa) {
	if(u == 0) return;
	dfs(ls[u], u), dfs(rs[u], u);

	// cerr << "calculate = " << u << " " << fa << " " << ls[u] << " " << rs[u] << "\n";

	siz[u] = siz[ls[u]] + siz[rs[u]] + 1;
	rep(i, 0, siz[ls[u]]) rep(j, 0, siz[rs[u]]) {
		// cerr << i << " + " << j << " -> " << "\n";
		f[u][i+j+1][1] = (f[u][i+j+1][1] + -1ll * f[ls[u]][i][1] * f[rs[u]][j][1]) % P;
		// cerr << "get " << f[ls[u]][i][1] << " " << f[rs[u]][j][1] << "\n";
		f[u][i+j][1] = (f[u][i+j][1] + 1ll * f[ls[u]][i][1] * f[rs[u]][j][1]) % P;
		f[u][i+j+1][0] = (f[u][i+j+1][0] 
							+ -1ll * (1ll * (f[ls[u]][i][0] + f[ls[u]][i][1]) * (f[rs[u]][j][0] + f[rs[u]][j][1]) - 1ll * f[ls[u]][i][1] * f[rs[u]][j][1])
							+ 1ll *  (f[ls[u]][i][0] + f[ls[u]][i][1]) * (f[rs[u]][j][0] + f[rs[u]][j][1])) % P;
		f[u][i+j][0] = (f[u][i+j][0] + 1ll *  (f[ls[u]][i][0] + f[ls[u]][i][1]) * (f[rs[u]][j][0] + f[rs[u]][j][1]) - 1ll * f[ls[u]][i][1] * f[rs[u]][j][1]) % P;
	}
	int d = p[u] - p[fa];
	rep(i, 0, siz[u]) {
		// cerr << "f = " << f[u][i][0] << " " << f[u][i][1] << " " << siz[u]-i << " " << d << "\n";
		f[u][i][0] = 1ll * f[u][i][0] * qpow(qpow(2, siz[u]-i)-1, d) % P;
		f[u][i][1] = 1ll * f[u][i][1] * qpow(qpow(2, siz[u]-i), d) % P;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n;
	rep(i, 1, n) cin >> p[i];
	rep(i, 1, n) {
		while(p[i] < p[stk[top]]) {
			ls[i] = stk[top--];
		}
		rs[stk[top]] = i;
		stk[++top] = i;
	}
	rt = rs[0];

	f[0][0][1] = 1;
	assert(rt != 0);
	dfs(rt, 0);

	int ans = 0;
	rep(i, 0, n) {
		ans = (ans + f[rt][i][0]) % P;
		ans = (ans + f[rt][i][1]) % P;
	}
	cout << (ans + P) % P << "\n";
	
	return 0;
}
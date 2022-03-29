// Problem: P5289 [十二省联考 2019] 皮配
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5289
// Memory Limit: 500 MB
// Time Limit: 2000 ms
// Create Time: 2022-03-15 19:05:34
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

#define ONLINE_JUDGE

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

const int N = 1e3 + 5;
const int M = 2.5e3 + 5;
const int K = 305;

int f[M], g[M], h[M][K], h1[M][K], h2[M][K], tmp[M][K];
int pref[M], preg[M];
int n, c, k;
int c0, c1, d0, d1;
vector<int> adj[N];
bool vis[N];
int pos[N], sum[N];
int b[N], s[N];

void solve() {
	debug("solve\n");
	cin >> n >> c;
	cin >> c0 >> c1 >> d0 >> d1;
	rep(i, 1, c) adj[i].clear();
	memset(f, 0, sizeof f);
	memset(g, 0, sizeof g);
	memset(h, 0, sizeof h);
	memset(pos, 0, sizeof pos);
	memset(vis, 0 ,sizeof vis);
	memset(sum, 0, sizeof sum);
	rep(i, 1, n) {
		cin >> b[i] >> s[i];
		adj[b[i]].pb(i);
		sum[b[i]] += s[i];
	}
	cin >> k;
	rep(i, 1, k) {
		int p, id;
		cin >> p >> id;
		++id;
		pos[p] = id;
		vis[b[p]] = 1;
	}
	
	int suma = 0;
	rep(i, 1, n) suma += s[i];
	
	if(c0 + c1 < suma || d0 + d1 < suma) {
		cout << 0 << "\n";
		return;
	}
	
	f[0] = g[0] = 1;
	rep(i, 1, c) {
		if(vis[i] || adj[i].empty()) continue;
		per(j, sum[i], c0) upd(f[j], f[j-sum[i]]);
	}
	
	rep(i, 1, n) {
		if(!pos[i]) {
			per(j, s[i], d0) upd(g[j], g[j-s[i]]);
		}
	}
	
	int kk = 300;
	
	h[0][0] = 1;
	
	rep(i, 1, n) {
		if(!vis[i]) continue;
		memcpy(h1, h, sizeof h1);
		memcpy(h2, h, sizeof h2);
		
		debug("ok i = {}\n", i);
		for(int id : adj[i]) {
			//1, 2
			if(!pos[id]) continue;
			debug("get lim, id = {}\n", id);
			memcpy(tmp, h1, sizeof tmp);
			memset(h1, 0, sizeof h1);
			rep(ii, 0, c0) rep(j, 0, kk) {
				//1
				if(pos[id] != 1 && j >= s[id]) {
					upd(h1[ii][j], tmp[ii][j-s[id]]);
				}
				//2
				if(pos[id] != 2) {
					upd(h1[ii][j], tmp[ii][j]);
				}
			}
			memcpy(tmp, h2, sizeof tmp);
			memset(h2, 0, sizeof h2);
			rep(ii, 0, c0) rep(j, 0, kk) {
				//3
				if(pos[id] != 3 && j >= s[id]) {
					upd(h2[ii][j], tmp[ii][j-s[id]]);
				}
				//4
				if(pos[id] != 4) {
					upd(h2[ii][j], tmp[ii][j]);
				}
			}
			//3, 4
			// debug("h1:\n"); rep(ii, 0, c0) rep(jj, 0, d0) cerr << h1[ii][jj] << " \n"[jj == d0];
			// debug("h2:\n"); rep(ii, 0, c0) rep(jj, 0, d0) cerr << h2[ii][jj] << " \n"[jj == d0];
			
		}
		memset(h, 0, sizeof h);
		rep(ii, 0, c0) rep(j, 0, kk) {
			if(ii >= sum[i]) {
				upd(h[ii][j], h1[ii-sum[i]][j]);
			}
			upd(h[ii][j], h2[ii][j]);
		}
	}
	
	pref[0] = f[0];
	preg[0] = g[0];
	rep(i, 1, c0) pref[i] = (pref[i-1] + f[i]) % mod;
	rep(i, 1, d0) preg[i] = (preg[i-1] + g[i]) % mod;
	
	int ans = 0;
	rep(i, 0, c0) {
		int li = max(0, suma - i - c1);
		int ri = c0 - i;
		if(li > ri) continue;
		
		int sf = pref[ri] - (li ? pref[li-1] : 0);
		
		rep(j, 0, kk) {
			int lj = max(0, suma - j - d1);
			int rj = d0 - j;
			if(lj > rj) continue;
			
			int sg = 
			preg[rj] - 
			(lj ? preg[lj-1] : 0);
			
			if(h[i][j]) debug("i = {}, j = {}, i0 [{}, {}], j0 [{}, {}], get ans = {} * {} * {}\n", i, j, li, ri, lj, rj, h[i][j], sf, sg);
			
			ans = (ans + 1ll * h[i][j] * sf % mod * sg) % mod;
		}
	}
	if(ans < 0) ans += mod;
	cout << ans << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	int T;
	cin >> T;
	while(T--) solve();
	
	return 0;
}


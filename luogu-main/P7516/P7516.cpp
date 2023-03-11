// Problem: P7516 [省选联考 2021 A/B 卷] 图函数
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7516
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// Create Time: 2022-03-09 17:55:35
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

std::mt19937_64 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

/* template ends here */

const int N = 1e3 + 5;
const int M = 2e5 + 5;
const int inf = 0x3f3f3f3f;

int n, m;
bitset<N> g1[N], g2[N];
bitset<N> vis1[N], vis2[N], v1[N], v2[N];
int eu[M], ev[M];
bitset<N> pre[N];
int cnt = 0;
ll ans[N];

void solve1(int id, int s) {
	debug("solve1 = {} {}\n", id, s);
	queue<int> q;
	vis1[id][s] = 1;
	v1[s][id] = 1;

	if(vis2[id][s] && id < s) ++cnt;

	q.push(s);
	while(!q.empty()) {
		int u = q.front(); q.pop();
		debug("visited {}\n", u);
		bitset<N> nxt = g1[u] & (pre[n] ^ vis1[id]);
		for(int v = nxt._Find_first(); v != N; v = nxt._Find_next(v)) {
			vis1[id][v] = 1;
			v1[v][id] = 1;
			if(vis2[id][v] && id < v) ++cnt;
			q.push(v);
		}
	}
}

void solve2(int id, int s) {
	debug("solve2 = {} {}, cnt = {}\n", id, s, cnt);
	queue<int> q;
	vis2[id][s] = 1;
	v2[s][id] = 1;

	if(vis1[id][s] && id < s) ++cnt;

	q.push(s);
	while(!q.empty()) {
		int u = q.front(); q.pop();
		bitset<N> nxt = g2[u] & (pre[n] ^ vis2[id]);
		for(int v = nxt._Find_first();  v != N; v = nxt._Find_next(v)) {
			vis2[id][v] = 1;
			v2[v][id] = 1;
			q.push(v);
			if(vis1[id][v] && id < v) ++cnt;
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> m;

	rep(i, 1, n) pre[i] = pre[i-1], pre[i][i] = 1;

	rep(i, 1, m) {
		cin >> eu[i] >> ev[i];
	}

	rep(i, 1, n) v1[i][i] = v2[i][i] = vis1[i][i] = vis2[i][i] = 1, ++ans[m+1];

	per(i, 1, m) {
		int u = eu[i], v = ev[i];

		if(u < v) g1[u][v] = 1;
		if(v > u) g2[v][u] = 1;

		debug("edge = {} {}\n", u, v);
		cnt = 0;
		bitset<N> o = v1[u] & (pre[n] ^ v1[v]);
		for(int x = o._Find_first(); x != N; x = o._Find_next(x)) {
			solve1(x, v);
		}

		o = v2[v] & (pre[n] ^ v2[u]);
		for(int x = o._Find_first(); x != N; x = o._Find_next(x)) {
			solve2(x, u);
		}

		debug("get cnt = {}\n", cnt);
		ans[i] = ans[i + 1] + cnt;

		// rep(j, 1, n) rep(k, 1, n) cerr << vis1[j][k] << " \n"[k == n];
		// cerr << "\n";
		
		// rep(j, 1, n) rep(k, 1, n) cerr << vis1[j][k] << " \n"[k == n];
		// cerr << "\n";
	}

	rep(i, 1, m + 1) cout << ans[i] << " \n"[i == m + 1];
	
	return 0;
}

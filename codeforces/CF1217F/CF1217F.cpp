// Problem: CF1217F Forced Online Queries Problem
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1217F
// Memory Limit: 250 MB
// Time Limit: 5000 ms

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

const ll mod = 1e9 + 7;
// const ll mod = 998244353;
template <typename T> inline void chkadd(T& x, T y) { x = x + y >= mod ? x + y - mod : x + y; }
template <typename T> inline void chkadd(T& x, T y, T z) { x = y + z >= mod ? y + z - mod : y + z; }
template <typename T> inline void chkmns(T& x, T y) { x = x - y < 0 ? x - y + mod : x - y; }
template <typename T> inline void chkmns(T& x, T y, T z) { x = y - z < 0 ? y - z + mod : y - z;}
template <typename T> inline void chkmax(T& x, T y) { x = x < y ? y : x; }
template <typename T> inline void chkmax(T& x, T y, T z) { x = y > z ? y : z; }
template <typename T> inline void chkmin(T& x, T y) { x = x < y ? x : y;}
template <typename T> inline void chkmin(T& x, T y, T z) { x = y < z ? y : z;}
ll qpow(ll x, ll p) { ll base = x, res = 1;	while (p) { if (p & 1) res = (res * base) % mod; base = (base * base) % mod; p >>= 1;} return res;}

/* template ends here */

std::mt19937 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

const int N = 2e5 + 5;

int uni[N], siz[N];
int ma[N], msa[N], mb[N], msb[N], top;
set<pair<int, int>> vis;
int op[N], qx[N][2], qy[N][2], nxtop[N][2];
int n, m;
vector<pair<int, int>> qry[N<<2];
map<pair<int, int>, pair<int, int>> last;
int ans[N];

inline int find(int x) { return x == uni[x] ? x : find(uni[x]); }
inline void merge(int x, int y) {
	// debug("merge = {} {}\n", x, y);
	int fx = find(x);
	int fy = find(y);
	if(fx == fy) return;
	if(siz[fx] < siz[fy]) swap(fx, fy);
	++top;
	ma[top] = fx; msa[top] = siz[fx];
	mb[top] = fy; msb[top] = siz[fy];
	uni[fy] = fx;
	siz[fx] += siz[fy];
}
inline void undo() {
	int x = ma[top], y = mb[top];
	int sx = msa[top], sy = msb[top];
	// debug("undo = {} {}\n", x, y);
	--top;
	uni[x] = x, uni[y] = y;
	siz[x] = sx, siz[y] = sy;
}
inline bool query(int x, int y) {
	return find(x) == find(y);
}

int lastans = 0;

inline void insert(int cur, int ql, int qr, int qx, int qy, int l, int r) {
	if(ql <= l && r <= qr) {
		qry[cur].pb(mp(qx, qy));
		return;
	}
	int mid = l + r >> 1;
	if(ql <= mid) insert(cur << 1, ql, qr, qx, qy, l, mid);
	if(mid < qr) insert(cur << 1 | 1, ql, qr, qx, qy, mid + 1, r);
}

inline void dfs(int cur, int l, int r) {
	int tp = top;
	for(auto [x, y] : qry[cur]) {
		merge(x, y);
	}
	if(l == r) {
		if(op[l] == 2) {
			int res = query(qx[l][lastans], qy[l][lastans]);
			ans[l] = lastans = res;
		}
		if(op[l+1] == 1) {
			{
				int x = qx[l+1][lastans];
				int y = qy[l+1][lastans];
				int t = nxtop[l+1][lastans];
				if(vis.count(mp(x, y))) {
					vis.erase(mp(x, y));
				} else {
					vis.insert(mp(x, y));
					insert(1, l+1, t, x, y, 0, m);
				}
			}
			{
				int x = qx[l+1][lastans^1];
				int y = qy[l+1][lastans^1];
				int t = nxtop[l+1][lastans^1];
				if(vis.count(mp(x, y))) {
					insert(1, l+1, t, x, y, 0, m);
				}
			}
		}
		while(top > tp) undo();
		return;
	}
	int mid = l + r >> 1;
	dfs(cur << 1, l, mid);
	dfs(cur << 1 | 1, mid + 1, r);
	while(top > tp) undo();
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> m;
	rep(i, 1, n) uni[i] = i, siz[i] = 1;
	rep(i, 1, m) {
		int x, y;
		cin >> op[i] >> x >> y;
		if(x > y) swap(x, y);
		if(op[i] == 1) {
			qx[i][0] = x;
			qy[i][0] = y;
			qx[i][1] = x % n + 1;
			qy[i][1] = y % n + 1;
			rep(j, 0, 1) {
				if(qx[i][j] > qy[i][j]) swap(qx[i][j], qy[i][j]);
				if(last.count(mp(qx[i][j], qy[i][j]))) {
					auto id = last[mp(qx[i][j], qy[i][j])];
					last[mp(qx[i][j], qy[i][j])] = mp(i, j);
					nxtop[id.fi][id.se] = i-1;
				} else {
					last[mp(qx[i][j], qy[i][j])] = mp(i, j);
				}
			}
		} else {
			qx[i][0] = x;
			qy[i][0] = y;
			qx[i][1] = x % n + 1;
			qy[i][1] = y % n + 1;
			if(qx[i][0] > qy[i][0]) swap(qx[i][0], qy[i][0]);
			if(qx[i][1] > qy[i][1]) swap(qx[i][1], qy[i][1]);
		}
	}
	
	for(auto [e, id] : last) nxtop[id.fi][id.se] = m;
	
	dfs(1, 0, m);
	
	rep(i, 1, m) if(op[i] == 2) cout << ans[i]; cout << "\n";
	
	return 0;
}
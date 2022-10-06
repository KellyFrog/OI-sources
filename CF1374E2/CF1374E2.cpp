// Problem: CF1374E2 Reading Books (hard version)
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1374E2
// Memory Limit: 250 MB
// Time Limit: 3000 ms

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

#define OK debug("OK!\n");
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

const int N = 2e5 + 5;

int n, m, k;
vector<pair<int, int>> v[2][2];
vector<int> pre[2][2];
vector<int> rt[2][2];
int sumcnt[N<<5], sumval[N<<5], lson[N<<5], rson[N<<5], tcnt;
int rt0;

inline void add(int& rt1, int rt2, int p, int l, int r) {
	rt1 = ++tcnt;
	sumcnt[rt1] = sumcnt[rt2] + 1;
	sumval[rt1] = sumval[rt2] + p;
	lson[rt1] = lson[rt2];
	rson[rt1] = rson[rt2];
	if(l == r) return;
	int mid = l + r >> 1;
	if(p <= mid) add(lson[rt1], lson[rt2], p, l, mid);
	else add(rson[rt1], rson[rt2], p, mid + 1, r);
}

inline void add0(int& rt, int p, int l, int r) {
	if(!rt) rt = ++tcnt;
	sumcnt[rt] += 1;
	sumval[rt] += p;
	if(l == r) return;
	int mid = l + r >> 1;
	if(p <= mid) add0(lson[rt], p, l, mid);
	else add0(rson[rt], p, mid + 1, r);
}

inline int ksum(int rt1, int rt2, int rt3, int rt4, int k, int l, int r) {
	if(l == r) return l * k;
	int mid = l + r >> 1;
	int lcnt = sumcnt[lson[rt1]] - sumcnt[lson[rt2]] - sumcnt[lson[rt3]] - sumcnt[lson[rt4]];
	int lval = sumval[lson[rt1]] - sumval[lson[rt2]] - sumval[lson[rt3]] - sumval[lson[rt4]];
	if(k <= lcnt) return ksum(lson[rt1], lson[rt2], lson[rt3], lson[rt4], k, l, mid);
	return lval + ksum(rson[rt1], rson[rt2], rson[rt3], rson[rt4], k-lcnt, mid+1, r);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> m >> k;
	rep(i, 1, n) {
		int t, a, b;
		cin >> t >> a >> b;
		v[a][b].pb(mp(t, i));
		add0(rt0, t, 1, (int)1e4);
	}
	rep(i, 0, 1) rep(j, 0, 1) sort(v[i][j].begin(), v[i][j].end());
	rep(a, 0, 1) rep(b, 0, 1) {
		if(v[a][b].empty()) continue;
		
		rt[a][b].resize(v[a][b].size());
		pre[a][b].resize(v[a][b].size());
		
		add(rt[a][b][0], 0, v[a][b][0].fi, 1, (int)1e4);
		for(int i = 1; i < v[a][b].size(); i++) add(rt[a][b][i], rt[a][b][i-1], v[a][b][i].fi, 1, (int)1e4);
		
		pre[a][b][0] = v[a][b][0].fi;
		for(int i = 1; i < v[a][b].size(); i++) pre[a][b][i] = pre[a][b][i-1] + v[a][b][i].fi;
	}
	int ans = INT_MAX;
	int p = 0;
	if(v[0][1].size() >= k && v[1][0].size() >= k && 2 * k <= m) {
		chkmin(ans, pre[0][1][k-1] + pre[1][0][k-1] + ksum(rt0, rt[0][1][k-1], rt[1][0][k-1], 0, m - 2 * k, 1, (int)1e4));
		p = 0;
	}
	for(int i = 0; i < v[1][1].size(); i++) {
		int x = k - i - 1;
		if(x < 0) continue;
		if(i+1 + 2 * x > m) continue;
		if(x == 0) {
			int val = pre[1][1][i] + ksum(rt0, rt[1][1][i], 0, 0, m - (i+1), 1, (int)1e4);
			debug("val = {}, i = {}\n", val, i);
			if(val < ans) ans = val, p = i+1;
		} else {
			if(x > v[0][1].size() || x > v[1][0].size()) continue;
			x--;
			int val = pre[0][1][x] + pre[1][0][x] + pre[1][1][i];
			 debug("v = {} {}\n", val, i + 2 * x);
			val += ksum(rt0, rt[1][1][i], rt[1][0][x], rt[1][0][x], m - (i+1) - 2 * (x+1), 1, (int)1e4);
			 debug("i = {}, val = {}\n", i, val);
			if(val < ans) ans = val, p = i+1;
		}
	}
	
	if(ans == INT_MAX) {
		cout << -1 << "\n";
		return 0;
	}
	cout << ans << "\n";
	
	rep(i, 1, p) cout << v[1][1][i-1].se << " ";
	rep(i, 1, k-p) cout << v[0][1][i-1].se << " " << v[1][0][i-1].se << " ";
	
	vector<pair<int, int>> vv;
	for(auto e : v[0][0]) vv.pb(e);
	for(int i = p; i < v[1][1].size(); i++) vv.pb(v[1][1][i]);
	for(int i = k - p; i < v[0][1].size(); i++) vv.pb(v[0][1][i]);
	for(int i = k - p; i < v[1][0].size(); i++) vv.pb(v[1][0][i]);
	
	sort(vv.begin(), vv.end());
	for(int i = 0; i < m - (p + 2 * (k - p)); i++) cout << vv[i].se << " "; cout << "\n";
	
	return 0;
}

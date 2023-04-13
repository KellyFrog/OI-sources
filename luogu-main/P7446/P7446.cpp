// Problem: P7446 [Ynoi2007] rfplca
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7446
// Memory Limit: 64 MB
// Time Limit: 2500 ms

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
#define rep(i, s, t) for (int i = s; i <= t; i++)
#define per(i, s, t) for (int i = t; i >= s; i--)

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

const int N = 4e5 + 5;
const int SZ = 750;

int blockid[N], blockL[SZ], blockR[SZ];
int tar[N]; ll tag[SZ];
int a[N], n, q;
int siz, tot;
vector<int> tmp[N], v[SZ];
int pt[N];

int cnt = 0;

inline void build(int id) {
	int l = blockL[id], r = blockR[id];
	rep(i, l, r) a[i] = max(1ll, a[i] - tag[id]); tag[id] = 0;
	rep(i, l, r) tar[i] = a[i] < l ? i : tar[a[i]];
	rep(i, l, r) tmp[i].clear();
	rep(i, l, r) if(a[i] >= l) tmp[a[i]].pb(i);
	pt[id] = 0; rep(i, l, r) for(int e : tmp[i]) v[id].pb(e);
}

inline void modify(int id, int x) {
	int l = blockL[id], r = blockR[id];
	tag[id] += x;
	ll delt = tag[id];
	vector<int> vv;
	for(int i = 0; i < v[id].size(); i++) {
		int p = v[id][i];
		int ap = a[p] - delt;
		if(ap >= l) tar[p] = tar[ap], vv.pb(p), cnt++;
		else tar[p] = p;
	}
	v[id] = vv;
}


inline int query(int x, int y) {
	// rep(i, 1, tot) build(i);
	while(x != y) {
		if(x < y) swap(x, y);
		int nx = max(1ll, a[tar[x]] - tag[blockid[tar[x]]]);
		int ny = max(1ll, a[tar[y]] - tag[blockid[tar[y]]]);
		if(nx == y) return y;
		cnt++;
		if(nx == ny) {
			build(blockid[x]);
			if(blockid[y] != blockid[x]) build(blockid[y]);
			while(x != y) {
				if(x < y) swap(x, y);
				x = a[x];
			}
			return x;
		}
		x = nx;
	}
	return x;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0), cout.tie(0); cout << fixed << setprecision(15); cerr << fixed << setprecision(15);
	
	qio >> n >> q;
	a[1] = 1;
	rep(i, 2, n) qio >> a[i];
	
	siz = sqrt(n);
	tot = (n + siz - 1) / siz;
	blockL[1] = 1, blockR[1] = siz;
	rep(i, 2, tot) blockL[i] = blockL[i-1] + siz, blockR[i] = blockR[i-1] + siz; blockR[tot] = n;
	rep(i, 1, tot) rep(j, blockL[i], blockR[i]) blockid[j] = i;
	
	rep(i, 1, tot) build(i);
	
	int lastans = 0;
	
	while(q--) {
		int op;
		qio >> op;
		if(op == 1) {
			int l, r, x;
			qio >> l >> r >> x;
			// l ^= lastans;
			// r ^= lastans;
			// x ^= lastans;
			if(l > r) swap(l, r);
			int id1 = blockid[l], id2 = blockid[r];
			if(id1 == id2) {
				rep(i, l, r) a[i] = max(1, a[i] - x);
				build(id1);
			} else {
				rep(i, l, blockR[id1]) a[i] = max(1, a[i] - x); build(id1);
				rep(i, blockL[id2], r) a[i] = max(1, a[i] - x); build(id2);
				rep(i, id1+1, id2-1) {
					modify(i, x);
				}
			}
		} else {
			int u, v;
			qio >> u >> v;
			// u ^= lastans;
			// v ^= lastans;
			qio << (lastans = query(u, v)) << "\n";
		}
	}
	
	cerr << cnt << "\n";
	
	
	return 0;
}
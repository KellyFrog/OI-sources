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

typedef unsigned int unit;

const int N = 1e5 + 5;
const int S = 320;

int n, q;
uint val[N], pre[N];
vector<pair<int, int>> adj[N];

namespace sqrtds {
	int blockid[N];
	int blockL[S], blockR[S];
	int siz, tot;
	uint pre1[N], pre2[N], val[N], lazy[N];
	void init() {
		if(n == 0 || q == 0) return;
		siz = sqrt(q);
		tot = (q + siz - 1) / siz;
		rep(i, 1, tot) blockL[i] = (i-1) * siz + 1, blockR[i] = min(q, i*siz);
		rep(i, 1, tot) rep(j, blockL[i], blockR[i]) blockid[j] = i;
	}
	void modify(int l, int r) {
		int id1 = blockid[l], id2 = blockid[r];
		if(id1 == id2) {
			rep(i, l, r) val[i] += ::val[i];
			pre1[blockL[id1]] = val[blockL[id1]];
			rep(i, blockL[id1] + 1, blockR[id1]) pre1[i] = pre1[i-1] + val[i];
			rep(i, 1, tot) pre2[i] = pre2[i-1] + pre1[blockR[i]] + (uint)(::pre[blockR[i]] - ::pre[blockL[i]-1]) * lazy[i];
		} else {
			rep(i, l, blockR[id1]) val[i] += ::val[i];
			pre1[blockL[id1]] = val[blockL[id1]];
			rep(i, blockL[id1] + 1, blockR[id1]) pre1[i] = pre1[i-1] + val[i];
			
			rep(i, id1 + 1, id2 - 1) ++lazy[i];
			
			rep(i, blockL[id2], r) val[i] += ::val[i];
			pre1[blockL[id2]] = val[blockL[id2]];
			rep(i, blockL[id2] + 1, blockR[id2]) pre1[i] = pre1[i-1] + val[i];
			
			rep(i, 1, tot) pre2[i] = pre2[i-1] + pre1[blockR[i]] + (uint)(::pre[blockR[i]] - ::pre[blockL[i]-1]) * lazy[i];
		}
	}
	unit query(int x) {
		uint res = 0;
		int id = blockid[x];
		res += pre2[id-1];
		res += pre1[x];
		res += lazy[id] * (uint)(::pre[x] - ::pre[blockL[id]-1]);
		return res;
	}
	uint query(int l, int r) {
		return query(r) - query(l-1);
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	/*
	cin >> n >> q;
	rep(i, 1, n-1) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].pb(mp(v, w));
		adj[v].pb(mp(u, w));
	}
	*/
	
	cin >> n >> q;
	rep(i, 1, n) cin >> val[i];
	rep(i, 1, n) pre[i] = pre[i-1] + val[i];
	sqrtds::init();
	while(q--) {
		int op, l, r;
		cin >> op >> l >> r;
		if(op == 1) {
			sqrtds::modify(l, r);
		} else {
			cout << sqrtds::query(l, r) << "\n";
		}
	}
	
	
	return 0;
}
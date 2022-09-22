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

const int N = 5e5  + 5;
const int T = 1e7 + 5;

int ls[T], rs[T], val[T], rt[N], tt;
int anc[N][21], mx[N][21];
int n, q, a[N], b[N];

inline void modify(int& o1, int o2, int p, int val, int l, int r) {
	o1 = ++tt;
	ls[o1] = ls[o2];
	rs[o1] = rs[o2];
	if(l == r) {
		::val[o1] = val;
		return;
	}
	int mid = l + r >> 1;
	if(p <= mid) modify(ls[o1], ls[o2], p, val, l, mid);
	else modify(rs[o1], rs[o2], p, val, mid + 1, r);
}

inline int query(int o, int p, int l, int r) {
	if(!o) return n+1;
	if(l == r) return val[o];
	int mid = l + r >> 1;
	if(p <= mid) return query(ls[o], p, l, mid);
	else return query(rs[o], p, mid + 1, r);
}

int main() {
	// freopen("stack.in", "r", stdin);
	// freopen("stack.out", "w", stdout);
// 	
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> q;
	rep(i, 1, n) cin >> a[i];
	rep(i, 1, n) cin >> b[i];
	
	rep(j, 0, 20) anc[n+1][j] = anc[n][j] = n+1;
	modify(rt[n], 0, a[n], n, 1, n);
	per(i, 1, n-1) {
		int p1 = query(rt[i+1], a[i], 1, n);
		int p2 = i + 1;
		if(b[i + 1] < b[i]) {
			per(j, 0, 20) {
				if(p2 == n + 1) break;
				if(mx[p2][j] < b[i]) {
					p2 = anc[p2][j];
				}
			}
			if(p2 != n + 1) p2 = anc[p2][0];
		}
		int p = min(p1, p2);
		anc[i][0] = p;
		mx[i][0] = b[p];
		rep(j, 1, 20) {
			anc[i][j] = anc[anc[i][j-1]][j-1];
			mx[i][j] = max(mx[i][j-1], mx[anc[i][j-1]][j-1]);
		}
		modify(rt[i], rt[p], a[i], i, 1, n);
	}
	
	while(q--) {
		int l, r;
		cin >> l >> r;
		int p = l, ans = 0;
		
		per(j, 0, 20) {
			if(anc[p][j] <= r) {
				p = anc[p][j];
				ans |= 1 << j;
			}
		}
		
		cout << ans + 1 << "\n";
	}
	cout.flush();
	
	cerr << 5 * (sizeof ls) / 1024 / 1024;
	
	return 0;
}
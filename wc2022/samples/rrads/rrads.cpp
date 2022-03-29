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

const int N = 5e5 + 5;

struct Q {
	int id, bel, l, r;
};

Q qr[N];
int n, q;
int a[N];
set<pair<int, int>> s;
ll ans = 0;
ll res[N];

inline void add(int i) {
	if(s.empty()) {
		s.insert(mp(a[i], i));
	} else {
		auto it = s.lower_bound(mp(a[i], i));
		if(it == s.end()) {
			--it;
			ans += abs(it->se - i);
		} else if(it == s.begin()) {
			ans += abs(it->se - i);
		} else {
			auto x = it;
			auto y = --it;
			ans -= abs(x->se - y->se);
			ans += abs(x->se - i);
			ans += abs(y->se - i);
		}
		s.insert(mp(a[i], i));
	}
}

inline void del(int i) {
	if(s.size() == 1) {
		s.erase(mp(a[i], i));
	} else {
		auto it = s.find(mp(a[i], i));
		auto y = it;
		auto x = ++it;
		if(x == s.end()) {
			--y;
			ans -= abs(y->se - i);
		} else if(y == s.begin()) {
			ans -= abs(x->se - i);
		} else {
			--y;
			ans -= abs(x->se - i);
			ans -= abs(y->se - i);
			ans += abs(x->se - y->se);
		}
		s.erase(mp(a[i], i));
	}
}

int main() {
	freopen("rrads.in", "r", stdin);
	freopen("rrads.out", "w", stdout);
	
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> q;
	rep(i, 1, n) cin >> a[i];
	int b = sqrt(n);
	rep(i, 1, q) {
		cin >> qr[i].l >> qr[i].r;
		qr[i].bel = qr[i].l/b;
		qr[i].id = i;
	}
	sort(qr+1, qr+q+1, [&](const Q& a, const Q& b) {
		return a.bel == b.bel ? (a.bel & 1) ? a.r > b.r : a.r < b.r : a.bel < b.bel;
	});
	
	int r=0, l=1;
	
	rep(i, 1, q) {
		while(r < qr[i].r) add(++r);
		while(r > qr[i].r) del(r--);
		while(qr[i].l < l) add(--l);
		while(qr[i].l > l) del(l++);
		res[qr[i].id] = ans;
	}
	
	rep(i, 1, q) cout << res[i] << "\n";
	cout.flush();
	
	return 0;
}

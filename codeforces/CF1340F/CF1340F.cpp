// Problem: CF1340F Nastya and CBS
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1340F
// Memory Limit: 250 MB
// Time Limit: 4000 ms
// Create Time: 2022-04-12 10:46:40
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

/* template ends here */

mt19937_64 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

const int N = 1e5 + 5;
const int S = 1e3 + 5;
const int P1 = 1234567891;
const int P2 = 998244353;

int n, q, k, a[N], B, base;
int pre1[S][S], pre2[S][S], suf1[S][S], suf2[S][S], len1[S], len2[S];
int bel[N], bl[N], br[N], ans[N], tot;
int pw1[N], pw2[N];
int stk[N], top;

void build(int id) {
	debug("build = {}, [{}, {}]\n", id, bl[id], br[id]);
	top = 0;
	ans[id] = 0;
	rep(i, bl[id], br[id]) {
		if(a[i] > 0) {
			stk[++top] = i;
		} else {
			if(!top || a[stk[top]] < 0) {
				stk[++top] = i;
			} else {
				if(a[stk[top]] + a[i] == 0) {
					--top;
				} else {
					ans[id] = 1;
					debug("FUCKED\n");
				}
			}
		}
	}
	int p = 0;
	rep(i, 1, top) {
		if(a[stk[i]] < 0) p = i;
	}
	rep(i, 1, p) assert(a[stk[i]] < 0);
	rep(i, p+1, top) assert(a[stk[i]] > 0);
	suf1[id][0] = suf2[id][0] = pre1[id][0] = pre2[id][0] = 1;
	rep(i, 1, p) {
		pre1[id][i] = (1ll * pre1[id][i-1] * base + (-a[stk[i]])) % P1;
		pre2[id][i] = (1ll * pre2[id][i-1] * base + (-a[stk[i]])) % P2;
	}
	per(i, p+1, top) {
		int j = top-i+1;
		suf1[id][j] = (1ll * suf1[id][j-1] * base + a[stk[i]]) % P1;
		suf2[id][j] = (1ll * suf2[id][j-1] * base + a[stk[i]]) % P2;
	}
	len1[id] = p;
	len2[id] = top-p;
}

bool solve(int l, int r) {
	if((r - l) % 2 == 0) return 0;
	debug("solve = {} {}\n", l, r);
	// rep(i, 1, n) cerr << a[i] << " \n"[i == n];
	if(bel[l] == bel[r]) {
		top = 0;
		rep(i, l, r) {
			if(a[i] > 0) {
				stk[++top] = i;
			} else {
				if(!top || a[stk[top]] + a[i]) return 0;
				--top;
			}
		}
		return !top;
	}
	int o1 = bel[l], o2 = bel[r];
	int t1 = tot + 1, t2 = tot + 2;
	bl[t1] = l, br[t1] = br[o1];
	bl[t2] = bl[o2], br[t2] = r;
	build(t1), build(t2);

	stack<tuple<int, int, int>> s;
	int tlen = 0;
	bool ok = 1;

	auto insert = [&](int id) {
		debug("insert = {}, tlen = {}, len = {} {}, ans = {}\n", id, tlen, len1[id], len2[id], ans[id]);
		if(ans[id] || len1[id] > tlen) {
			debug("fucked\n");
			ok = 0;
			return;
		}
		tlen -= len1[id];
		int p = 0;
		while(p != len1[id] && !s.empty()) {
			auto [t, l, r] = s.top(); s.pop();
			++p;
			int len = min(len1[id] - p + 1, r - l + 1);

			debug("compare [{}, {}], [{}, {}]\n", p, p + len - 1, l, r);

			int hs11 = (pre1[id][p+len-1] - 1ll * pre1[id][p-1] * pw1[len]) % P1; if(hs11 < 0) hs11 += P1;
			int hs12 = (pre2[id][p+len-1] - 1ll * pre2[id][p-1] * pw2[len]) % P2; if(hs12 < 0) hs12 += P2;
			int hs21 = (suf1[t][l+len-1] - 1ll * suf1[t][l-1] * pw1[len]) % P1; if(hs21 < 0) hs21 += P1;
			int hs22 = (suf2[t][l+len-1] - 1ll * suf2[t][l-1] * pw2[len]) % P2; if(hs22 < 0) hs22 += P2;

			debug("hash = {} {} {} {}\n", hs11, hs12, hs21, hs22);

			if(hs11 != hs21) ok = 0;
			if(hs12 != hs22) ok = 0;
			p += len - 1;
			int ll = l + len;
			if(ll <= r) {
				s.emplace(t, ll, r);
			}
		}
		if(p != len1[id]) ok = 0;
		if(len2[id]) s.emplace(id, 1, len2[id]);
		tlen += len2[id];
		debug("ok = {}\n", ok);
	};

	insert(t1);
	rep(id, o1 + 1, o2 - 1) insert(id);
	insert(t2);

	debug("ok = {}\n", ok);

	if(tlen) ok = 0;

	return ok;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> k;
	B = sqrt(n);
	base = k + mtrnd() % 10 + 1;
	pw1[0] = pw2[0] = 1;
	rep(i, 1, n) pw1[i] = 1ll * pw1[i-1] * base % P1, pw2[i] = 1ll * pw2[i-1] * base % P2;

	rep(i, 1, n) cin >> a[i];
	tot = (n + B - 1) / B;
	rep(i, 1, tot) bl[i] = (i - 1) * B + 1, br[i] = i * B;
	br[tot] = n;
	rep(i, 1, tot) rep(j, bl[i], br[i]) bel[j] = i;
	rep(i, 1, tot) build(i);

	cin >> q;
	while(q--) {
		int op, x, y;
		cin >> op >> x >> y;
		if(op == 1) {
			a[x] = y;
			build(bel[x]);
		} else {
			cout << (solve(x, y) ? "Yes" : "No") << "\n";
		}
	}
	
	return 0;
}
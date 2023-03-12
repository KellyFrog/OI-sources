// Problem: P8029 [COCI2021-2022#3] Akcija
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P8029
// Memory Limit: 512 MB
// Time Limit: 5000 ms
// Create Time: 2022-03-22 07:23:51
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

const int N = 2e3 + 5;

int n, k;
pair<int, int> a[N];
int t[N], pos[N];
int stk[N], top;

struct Q {
	bitset<N> p;
	ll ans;
	int cnt;
	Q() : ans(0), cnt(0), p() {}
};

bool operator < (const Q& x, const Q& y) {
	if(x.cnt != y.cnt) return x.cnt < y.cnt;
	if(x.ans != y.ans) return x.ans > y.ans;
	int o = (x.p^y.p)._Find_first();
	if(o == N) return 0;
	return x.p[o];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> k;
	rep(i, 1, n) cin >> a[i].fi >> a[i].se;
	a[n+1] = mp((int)1e9, (int)1e9);
	sort(a + 1, a + n + 1);
	Q ans0;
	rep(i, 1, n) {
		int p = a[i].se;
		bool ok = 1;
		rep(j, p, n) {
			if(t[j] == j) ok = 0;
		}
		if(ok) {
			ans0.p[i] = 1;
			++ans0.cnt;
			ans0.ans += a[i].fi;
			rep(j, p, n) ++t[j];
		}
	}
	
	set<Q> s;
	s.insert(ans0);
	while(k--) {
		assert(!s.empty());
		auto o = *s.rbegin();
		cout << o.cnt << " " << o.ans << "\n";
		s.erase(--s.end());
		rep(i, 1, n) {
			if(o.p[i]) {
				auto cur = o;
				--cur.cnt;
				cur.ans -= a[i].fi;
				cur.p[i] = 0;
				s.insert(cur);
			}
		}
		memset(t, 0 ,sizeof t);
		rep(i, 1, n) if(o.p[i]) ++t[a[i].se];
		rep(i, 1, n) t[i] += t[i-1];
		rep(i, 1, n) assert(t[i] <= i);
		
		int last = 0;
		rep(i, 1, n) {
			pos[i] = last;
			if(t[i] == i) last = i;
		}
		
		
		
		stk[top=1] = n+1;
		per(i, 1, n) {
			if(!o.p[i]) {
				while(top && a[stk[top]].se <= a[i].se) --top;
				stk[++top] = i;
			} else {
			
				int L = 1, R = top;
				int res = -1;
				while(L <= R) {
					int mid = L + R >> 1;
					if(a[stk[mid]].se > pos[a[i].se]) {
						res = mid;
						L = mid + 1;
					} else {
						R = mid - 1;
					}
				}
				
				if(res != 1) {
					auto cur = o;
					cur.p[i] = 0;
					cur.ans -= a[i].fi;
					int p = stk[res];
					assert(!cur.p[p]);
					cur.p[p] = 1;
					cur.ans += a[p].fi;
					s.insert(cur);
				}
			}
			
		}
		while(s.size() > k) s.erase(s.begin());
	}	
	
	return 0;
}


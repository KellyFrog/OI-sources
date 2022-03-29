// Problem: CF1637E Best Pair
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1637E
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

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

const int N = 3e5 + 5;

int a[N];
int n, m;
vector<int> val[N];

void solve() {
	cin >> n >> m;
	map<int, int> cnt;
	set<pair<int, int>> s;
	priority_queue<tuple<ll, pair<int, int>, pair<int, int>>> pq;
	
	rep(i, 1, n) cin >> a[i], ++cnt[a[i]];
	rep(i, 1, m) {
		int x, y;
		cin >> x >> y;
		s.insert(mp(x, y));
		s.insert(mp(y, x));
	}
	
	vector<int> appt;
	for(auto [x, t] : cnt) {
		appt.pb(t);
		val[t].pb(x);
	}
	sort(appt.begin(), appt.end());
	appt.erase(unique(appt.begin(), appt.end()), appt.end());
	
	auto calc = [&](int x, int y) {
		return 1ll * (x + y) * (cnt[x] + cnt[y]);
	};
	
	auto add = [&](pair<int, int> a, pair<int, int> b) {
		pq.emplace(calc(val[a.fi][a.se], val[b.fi][b.se]), a, b);
	};
	
	for(int i = 0; i < appt.size(); ++i) {
		int t = appt[i];
		sort(val[t].begin(), val[t].end(), greater<int>());
		if(val[t].size() > 1) add(mp(t, 0), mp(t, 1));
	}
	for(int i = 0; i < appt.size(); ++i) {
		for(int j = 0; j < i; ++j) {
			int t1 = appt[i], t2 = appt[j];
			add(mp(t1, 0), mp(t2, 0));
		}
	}
	set<pair<int, int>> vis;
	while(!pq.empty()) {
		auto [ans, x, y] = pq.top(); pq.pop();
		int valx = val[x.fi][x.se];
		int valy = val[y.fi][y.se];
		if(vis.count(mp(valx, valy))) continue;
		vis.insert(mp(valx, valy));
		if(!s.count(mp(valx, valy))) {
			cout << ans << "\n";
			
			for(int t : appt) {
				val[t].clear();
			}
			
			return;
		}
		auto x0 = mp(x.fi, x.se + 1);
		auto y0 = mp(y.fi, y.se + 1);
		
		auto insert = [&](pair<int, int> a, pair<int, int> b) {
			if(a == b) return;
			if(a.se >= val[a.fi].size()) return;
			if(b.se >= val[b.fi].size()) return;
			add(a, b);
		};
		
		insert(x0, y);
		insert(x, y0);
	}
	
	cout << -1 << "\n";
	
	for(int t : appt) {
		val[t].clear();
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	int t;
	cin >> t;
	while(t--) solve();
	
	return 0;
}

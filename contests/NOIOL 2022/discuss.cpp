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

const int N = 1e6 + 5;

int n;
vector<int> s[N], bel[N];
set<int> st[N];
bool vis[N];
set<vector<int>> cnt;

void solve() {
	cin >> n;
	rep(i, 1, n) s[i].clear(), bel[i].clear(), st[i].clear(), vis[i] = 0;
	cnt.clear();
	rep(i, 1, n) {
		int k; cin >> k;
		s[i].resize(k);
		for(int& x : s[i]) cin >> x;
		sort(s[i].begin(), s[i].end());
		if(cnt.count(s[i])) continue;
		cnt.insert(s[i]);
		for(int x : s[i]) bel[x].pb(i), st[i].insert(x);
	}
	vector<pair<int, int>> qr;
	rep(i, 1, n) {
		sort(bel[i].begin(), bel[i].end(), [&](int i, int j) { return s[i].size() < s[j].size(); });
		for(int j = 1; j < bel[i].size(); ++j) {
			qr.pb(mp(bel[i][j-1], bel[i][j]));
		}
	}
	sort(qr.begin(), qr.end(), [&](const pair<int, int>& x, const pair<int, int>& y) { return s[x.se].size() < s[y.se].size(); });
	
	auto check = [&](int i, int j) {
		if(vis[i] || vis[j]) return false;
		if(s[i].size() < s[j].size()) swap(i, j);
		vector<int> era;
		bool ok1 = 0, ok2 = 0;
		for(int x : s[j]) {
			if(!st[i].count(x)) ok1 = 1;
			else st[i].erase(x), era.pb(x);
		}
		ok2 = !st[i].empty();
		for(int x : era) st[i].insert(x);
		
		assert(s[i].size() >= s[j].size());
		
		vis[j] = 1;
		return ok1 && ok2;
	};
	
	for(auto q : qr) {
		if(check(q.se, q.fi)) {
			cout << "YES" << "\n";
			cout << q.fi << " " << q.se << "\n";
			return;
		}
	}
	cout << "NO" << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	freopen("discuss.in", "r", stdin);
	freopen("discuss.out", "w", stdout);
	
	int t;
	cin >> t;
	while(t--) solve();
	cout.flush();
	
	return 0;
}
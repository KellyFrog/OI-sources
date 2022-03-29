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

int id;
int n, k;
string s1, s2;

namespace bf {
	
const int N = 27;

struct mhash {
	template<class T1, class T2>
	std::size_t operator () (const pair<T1, T2>& x) const {
		return (hash<T1>()(x.fi) << 5) ^ x.se;
	}
};

unordered_map<pair<int, int>, pair<pair<int, pair<int, int> >, int>, mhash > dis;
int stk[N], top;

int tob(const string& s) {
	if(s.length() == 0) return 0;
	int res = 0;
	rep(i, 1, s.length()-1) {
		if(s[i] == '(') res |= 1 << i-1;
	}
	return res;
}

inline void dfs(pair<int, int> cur) {
	if(cur.fi == tob(s2) || cur.fi == 0) return;
	int d = cur.se - (dis[cur].fi.se.se == 6);
	// debug("dfs = {} {} {} {}\n", cur.fi, cur.se, dis[cur].fi.se.fi, dis[cur].fi.se.se);
	// debug("call {} {}\n", dis[cur].se, d);
	cout << dis[cur].fi.se.se << " " << dis[cur].fi.se.fi << "\n";
	dfs(mp(dis[cur].se, d));
}

void solve() {
	dis.clear();
	queue<pair<string, pair<int, int>> > q;
	int s = tob(s1);
	int t = tob(s2);
	int id = s;
	dis[mp(t, 0)] = mp(mp(0, mp(0, 0)), 0);
	q.push(mp(s2, mp(0, 0)));
	int base = 1<<25;
	int cnt = 0;
	while(!q.empty()
	 // && !dis.count(mp(s, 0)) 
	 // && !dis.count(mp(s, 1)) && !dis.count(mp(s, 2))
	 ) {
		string s = q.front().fi; int d1 = q.front().se.fi, d2 = q.front().se.se; q.pop();
		++cnt;
		// debug("s ={}, d = {}, {}\n", s, d1, d2);
		if(int(s.length()) < 2*n-4 || s.length() == 1) continue;
		int o = tob(s);
		// debug("id = {}\n", o);
		bool ok = 0;
		rep(i, 1, int(s.length())-1-5) {
			bool ok = 1;
			int sa=-100, ta=-100, sb=-100, tb=-100, sc=-100, tc=-100;
			top = 0;
			if(!(s[i] == '(' && s[i+1] == '(')) continue;
			rep(j, i, s.length()-1) {
				if(s[j] == '(') stk[++top] = j;
				else {
					if(top == 0) break;
					if(stk[top] == i) sb = ta+2, tb=j-1;
					else if(stk[top] == i+1) sa = i+2, ta = j-1;
					else if(stk[top] == tb+2) sc=tb+3, tc=j-1;
					
					--top;
				}
			}
			if(ta==-100 || tb==-100 || tc==-100) continue;
			string a = "", b = "", c = "";
			string p = " ", qq = "";
			rep(j, 1, i-1) p += s[j];
			rep(j, tc+2, s.length()-1) qq += s[j];
			rep(j, sa, ta) a += s[j];
			rep(j, sb, tb) b += s[j];
			rep(j, sc, tc) c += s[j];
			string n1 = p+"((("+a+")"+b+")"+c+")"+qq;
			string n2 = p+"(("+a+")("+b+")"+c+")"+qq;
			string n3 = p+"("+a+")(("+b+")"+c+")"+qq;
			string n4 = p+"("+a+")("+b+")("+c+")"+qq;
			int i1 = tob(n1);
			int i2 = tob(n2);
			int i3 = tob(n3);
			int i4 = tob(n4);
			// debug("get{}{}{}{}\n", n1, n2, n3, n4);
			if(!dis.count(mp(i1, d2))) dis[mp(i1, d2)] = mp(mp(d1+1, mp(i-1, 1)), o), q.push(mp(n1, mp(d1+1, d2)));
			if(!dis.count(mp(i2, d2))) dis[mp(i2, d2)] = mp(mp(d1+1, mp(i-1, 2)), o), q.push(mp(n2, mp(d1+1, d2)));
			if(!dis.count(mp(i3, d2))) dis[mp(i3, d2)] = mp(mp(d1+1, mp(i-1, 3)), o), q.push(mp(n3, mp(d1+1, d2)));
			if(!dis.count(mp(i4, d2))) dis[mp(i4, d2)] = mp(mp(d1+1, mp(i-1, 4)), o), q.push(mp(n4, mp(d1+1, d2)));
			
			if(i1 == id || i2 == id || i3 == id || i4 == id) {
				ok = 1;
				break;
			}
		}
		if(ok) break;
		if(d2 < 2) {
			rep(i, 0, s.length()-1) {
				string p = " ", qq = "";
				rep(j, 1, i) p += s[j];
				rep(j, i+1, s.length()-1) qq += s[j];
				string ns = p+"()"+qq;
				// debug("get ns ={}\n", ns);
				int oo = tob(ns);
				if(!dis.count(mp(oo, d2+1))) {
					// debug("ok update\n");
					dis[mp(oo, d2+1)] = mp(mp(d1+1, mp(i, 6)), o);
					q.push(mp(ns, mp(d1+1, d2+1)));
				}
				if(oo == id) {
					ok = 1;
					break;
				}
			}
		}
		if(ok) break;
		rep(i, 1, s.length()-2) {
			if(s[i] == '(' && s[i+1] == ')') {
				string ns = " ";
				rep(j, 1, i-1) ns += s[j];
				rep(j, i+2, s.length()-1) ns += s[j];
				int oo = tob(ns);
				// debug("get ds = {} {}\n", ns, oo);
				if(!dis.count(mp(oo, d2))) {
					// debug("ok update, i-1 = {}\n", i-1);
					dis[mp(oo, d2)] = mp(mp(d1+1, mp(i-1, 5)), o);
					q.push(mp(ns, mp(d1+1, d2)));
				}
				if(oo == id) {
					ok = 1;
					break;
				}
			}
		}
		if(ok) break;
	}
	int mi = 1e9, p = -1;
	rep(i, 0, 2) {
		if(dis.count(mp(s, i))) {
			if(dis[mp(s, i)].fi.fi < mi) p = i, mi = dis[mp(s, i)].fi.fi;
		}
	}
	cerr << cnt << "\n";
	if(p == -1 || dis[mp(s, p)].fi.fi > k) {
		cout << -1 << "\n";
	} else {
		cout << dis[mp(s, p)].fi.fi << "\n";
		dfs(mp(s, p));
	}
}

}

namespace op56 {

const int N = 4e5 + 5;

int stk[N], top, mat1[N], mat2[N];
vector<pair<int, int>> ans;

inline void dfs1(int l, int r) {
	if(l > r) return;
	if(mat1[l] == r) {
		dfs1(l+1, r-1);
		ans.pb(mp(6, l-1));
	} else {
		for(int i = r; i >= l; i = mat1[i] - 1) {
			dfs1(mat1[i], i);
		}
	}
}

inline void dfs2(int l, int r) {
	if(l > r) return;
	if(mat2[l] == r) {
		ans.pb(mp(5, l-1));
		dfs2(l+1, r-1);
	} else {
		for(int i = l; i <= r; i = mat2[i] + 1) {
			dfs2(i, mat2[i]);
		}
	}
}

void solve() {
	ans.clear();
	rep(i, 1, 2*n) {
		if(s1[i] == '(') stk[++top] = i;
		else mat1[i] = stk[top], mat1[stk[top]] = i, --top;
	}
	assert(top == 0);
	rep(i, 1, 2*n) {
		if(s2[i] == '(') stk[++top] = i;
		else mat2[i] = stk[top], mat2[stk[top]] = i, --top;
	}
	assert(top == 0);
	dfs1(1, 2*n);
	dfs2(1, 2*n);
	cout << ans.size() << "\n";
	for(auto e : ans) cout << e.fi << " " << e.se << "\n";
}
}

void solve() {
	cin >> n >> k;
	cin >> s1 >> s2;
	s1 = ' ' + s1;
	s2 = ' ' + s2;
	if(1 <= id && id <= 3) bf::solve();
	if((7 <= id && id <= 8) || (14 <= id && id <= 16)) op56::solve();
}

int main() {
	freopen("oper.in", "r", stdin);
	freopen("oper.out", "w", stdout);
	
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	int t;
	cin >> id >> t;
	while(t--) solve();
	cout.flush();
	
	return 0;
}

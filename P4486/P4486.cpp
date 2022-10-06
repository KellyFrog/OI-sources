// Problem: P4486 [BJWC2018]Kakuro
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4486
// Memory Limit: 500 MB
// Time Limit: 1000 ms
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

const int N = 4 * 30 * 30 + 10;
const int M = 1e7 + 5;

const ll inf = 0x3f3f3f3f3f3f3f3f;

int n, m, k, s, t;
int head[N], nxt[M<<1], to[M<<1], tot = 1;
ll cost[M<<1], wgt[M<<1];
ll dis[N], in[N], from[N];
bool inq[N];
ll eu[M], ev[M], el[M], er[M], ec[M], ep[M];
ll ind[N], oud[N];
int clim;

inline void addedge(int u, int v, ll w, ll c) {
	nxt[++tot] = head[u];
	to[tot] = v;
	wgt[tot] = w;
	cost[tot] = c;
	head[u] = tot;
}

inline void addlim(int u, int v, ll l, ll r, ll c) {
	debug("addlim({} -> {}, [{}, {}], cost = {}\n", u, v, l, r, c);
	int i = ++clim;
	eu[i] = u, ev[i] = v, el[i] = l, er[i] = r, ec[i] = c;
}

inline bool spfa() {
	memset(dis, 0x3f, sizeof dis);
	memset(from, 0, sizeof from);
	queue<int> q;
	dis[s] = 0;
	in[s] = inf;
	q.push(s);
	while(!q.empty()) {
		int u = q.front(); q.pop();
		inq[u] = 0;
		for(int e = head[u]; e; e = nxt[e]) {
			int v = to[e];
			ll w = cost[e], f = wgt[e];
			if(f && dis[u] + w < dis[v]) {
				dis[v] = dis[u] + w;
				in[v] = min(in[u], f);
				from[v] = e;
				if(!inq[v]) q.push(v), inq[v] = 1;
			}
		}
	}
	return dis[t] != inf;
}

pair<ll, ll> mcmf() {
	ll flow = 0, tcost = 0;
	
	while(spfa()) {
		int cur = t;
		flow += in[t];
		while(cur != s) {
			int e = from[cur];
			tcost += 1ll * cost[e] * in[t];
			wgt[e] -= in[t];
			wgt[e^1] += in[t];
			cur = to[e^1];
		}
	}
	return mp(flow, tcost);
}


ll possible_mc(int n) {
	ll sum1 = 0, sum2 = 0;
	ll ans1 = 0;
	
	rep(i, 1, clim) {
		ind[ev[i]] += el[i];
		oud[eu[i]] += el[i];
	}		
	
	rep(i, 1, n) {
		if(ind[i] <= oud[i]) {
			addedge(i, t, oud[i]-ind[i], 0);
			addedge(t, i, 0, 0);
			sum1 += oud[i]-ind[i];
			
		} else {
			addedge(s, i, ind[i]-oud[i], 0);
			addedge(i, s, 0, 0);
			sum2 += ind[i]-oud[i];
		}
	}
	
	rep(i, 1, clim) {
		ep[i] = tot+1;
		addedge(eu[i], ev[i], er[i]-el[i], ec[i]);
		addedge(ev[i], eu[i], 0, -ec[i]);
		ans1 += el[i]*ec[i];
	}
	
	if(sum1 != sum2) {
		return inf;
	}
	
	auto [flow, cost] = mcmf();
	
	if(flow != sum1) return inf;
	return ans1 + cost;
}

const int L = 35;

int c[L][L];
int lim1[L][L], lim2[L][L];
int lc1[L][L], lc2[L][L];
// lim1 -> 下 lim2 -> 右
int a[L][L], tp[L][L];
int b[L][L], r1[L][L], r2[L][L];
int ida[L][L], id1[L][L], id2[L][L];
int l1[L][L], l2[L][L];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> m;
	rep(i, 1, n) rep(j, 1, m) {
		cin >> tp[i][j];
	}
	
	memset(lim1, -1, sizeof lim1);
	memset(lim2, -1, sizeof lim2);
	
	rep(i, 1, n) {
		int p = 1;
		while(p <= m) {
			while(p <= m && (tp[i][p] == 0 || tp[i][p] == 4)) ++p;
			if(p > m) break;
			if(tp[i][p] == 4) cin >> a[i][p];
			else if(tp[i][p] == 1) cin >> lim1[i][p];
			else if(tp[i][p] == 2) cin >> lim2[i][p];
			else cin >> lim1[i][p] >> lim2[i][p];
			++p;
		}
	}
	rep(i, 1, n) {
		int p = 1;
		while(p <= m) {
			while(p <= m && tp[i][p] == 0) ++p;
			if(p > m) break;
			if(tp[i][p] == 4) cin >> a[i][p];
			else if(tp[i][p] == 1) cin >> lc1[i][p];
			else if(tp[i][p] == 2) cin >> lc2[i][p];
			else cin >> lc1[i][p] >> lc2[i][p];
			++p;
		}
	}
	
	rep(i, 1, n) rep(j, 1, m) if(tp[i][j] == 4) b[i][j] = 1;
	rep(i, 1, n) rep(j, 1, m) {
		if(tp[i][j] == 1 || tp[i][j] == 3) {
			int p = i+1;
			while(b[p][j]) l1[p++][j] = i;
			--p;
			r1[i][j] = p-i;
		}
		if(tp[i][j] == 2 || tp[i][j] == 3) {
			int p = j+1;
			while(b[i][p]) l2[i][p++] = j;
			--p;
			r2[i][j] = p-j;
		}
	}
	
	int iid = 0;
	
	rep(i, 1, n) rep(j, 1, m) {
		if(tp[i][j] == 1 || tp[i][j] == 3) id1[i][j] = ++iid;
		if(tp[i][j] == 2 || tp[i][j] == 3) id2[i][j] = ++iid;
	}
	
	rep(i, 1, n) rep(j, 1, m) cerr << lim1[i][j] << " \n"[j == m]; cerr << "\n";
	rep(i, 1, n) rep(j, 1, m) cerr << lim2[i][j] << " \n"[j == m]; cerr << "\n";
	rep(i, 1, n) rep(j, 1, m) cerr << r1[i][j] << " \n"[j == m]; cerr << "\n";
	rep(i, 1, n) rep(j, 1, m) cerr << r2[i][j] << " \n"[j == m]; cerr << "\n";
	
	rep(i, 1, n) rep(j, 1, m) {
		if(tp[i][j] == 1 || tp[i][j] == 3) {
			if(r1[i][j] > lim1[i][j]) {
				cout << -1 << "\n";
				return 0;
			}
		}
		if(tp[i][j] == 2 || tp[i][j] == 3) {
			if(r2[i][j] > lim2[i][j]) {
				cout << -1 << "\n";
				return 0;
			}
		}
	}
	
	int ss = ++iid, tt = ++iid;
	
	addlim(tt, ss, 0, inf, 0);
	
	int ans = 0;
	
	rep(i, 1, n) rep(j, 1, m) {
		debug("i = {}, j = {}\n", i, j);
		if(tp[i][j] == 1 || tp[i][j] == 3) {
			int x = id1[i][j], y = ++iid;
			debug("down, x = {}, y = {}\n", x, y);
			addlim(ss, x, 0, inf, 0);
			
			if(lc1[i][j] == -1) addlim(x, y, lim1[i][j]-r1[i][j], lim1[i][j]-r1[i][j], 0);
			else {
				ans += (lim1[i][j]-r1[i][j]) * lc1[i][j];
				addlim(x, y, 0, lim1[i][j]-r1[i][j], -lc1[i][j]);
				addlim(x, y, 0, inf, lc1[i][j]);
			}
			int p = i+1;
			while(tp[p][j] == 4) {
				int o = id2[p][l1[p][j]];
				if(c[p][j] == -1) {
					addlim(y, o, a[p][j]-1, a[p][j]-1, 0);
				} else {
					ans += (a[p][j]-1) * c[p][j];
					addlim(y, o, 0, a[p][j]-1, -c[p][j]);
					addlim(y, o, 0, inf, lc1[i][j]);
				}
				++p;
			}
		}
		if(tp[i][j] == 2 || tp[i][j] == 3) {
			int x = id2[i][j], y = ++iid;
			debug("right, x = {}, y = {}\n", x, y);
			addlim(y, tt, 0, inf, 0);
			if(lc2[i][j] == -1) addlim(x, y, lim2[i][j]-r2[i][j], lim2[i][j]-r2[i][j], 0);
			else {
				ans += (lim2[i][j]-r2[i][j]) * lc2[i][j];
				addlim(x, y, 0, lim2[i][j]-r2[i][j], -lc2[i][j]);
				addlim(x, y, 0, inf, lc2[i][j]);
			}
		}
	}
	
	s = iid+1, t = iid+2;
	debug("ans0 = {}\n", ans);
	cout << ans + possible_mc(iid) << "\n";
	
	return 0;
}

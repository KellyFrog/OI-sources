// Problem: CF639F Bear and Chemistry
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF639F
// Memory Limit: 250 MB
// Time Limit: 6000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

<<<<<<< HEAD

=======
/*
 * Author: chenkaifeng @BDFZ
 */
 
>>>>>>> 07e8fc721cf87637ca1e4d43005e936688912e6e
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
<<<<<<< HEAD
#define pb push_back
#define mp make_pair
#define ep emplace_back
#define fi first
#define se second
#define rep(i, s, t) for(int i = (s); i <= (t); ++i)
#define per(i, s, t) for(int i = (t); i >= (s); --i)
=======
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define pf push_front
#define rep(i, s, t) for (int i = s; i <= t; ++i)
#define per(i, s, t) for (int i = t; i >= s; --i)

namespace nqio{const unsigned R=4e5,W=4e5;char*a,*b,i[R],o[W],*c=o,*d=o+W,h[40],*p=h,y;bool s;struct q{void r(char&x){x=a==b&&(b=(a=i)+fread(i,1,R,stdin),a==b)?-1:*a++;}void f(){fwrite(o,1,c-o,stdout);c=o;}~q(){f();}void w(char x){*c=x;if(++c==d)f();}q&operator>>(char&x){do r(x);while(x<=32);return*this;}q&operator>>(char*x){do r(*x);while(*x<=32);while(*x>32)r(*++x);*x=0;return*this;}template<typename t>q&operator>>(t&x){for(r(y),s=0;!isdigit(y);r(y))s|=y==45;if(s)for(x=0;isdigit(y);r(y))x=x*10-(y^48);else for(x=0;isdigit(y);r(y))x=x*10+(y^48);return*this;}q&operator<<(char x){w(x);return*this;}q&operator<<(char*x){while(*x)w(*x++);return*this;}q&operator<<(const char*x){while(*x)w(*x++);return*this;}template<typename t>q&operator<<(t x){if(!x)w(48);else if(x<0)for(w(45);x;x/=10)*p++=48|-(x%10);else for(;x;x/=10)*p++=48|x%10;while(p!=h)w(*--p);return*this;}}qio;}using nqio::qio;
>>>>>>> 07e8fc721cf87637ca1e4d43005e936688912e6e

#define OK debug("OK!\n")
#ifndef ONLINE_JUDGE
namespace debuger{void debug(const char *s) {cerr << s;}template<typename T1,typename... T2>void debug(const char*s, const T1 x, T2...ls) { int p=0; while(*(s + p)!='\0') {if(*(s+p)=='{'&&*(s+p+1)=='}'){cerr << x;debug(s + p + 2, ls...);return;}cerr << *(s + p++);}}}using debuger::debug;
#else
#define debug(...) void(0)
#endif

<<<<<<< HEAD

mt19937_64 mtrnd(chrono::system_clock::now().time_since_epoch().count());

const int N = 6e5 + 5;
const int M = 1e6 + 5;

int n, m, q;
int nn, mm;
int head[N], nxt[M<<1], to[M<<1], tot = 1;
int dfn[N], low[N], dfncnt, stk[N], ins[N], top, bel[N], bid, rt;
vector<int> adj[N], vt[N];
int eul[N<<1], st[21][N<<1], dep[N], pos[N], lg2[N<<1], eid;
=======
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

const int N = 1e6 + 5;
const int M = 1e6 + 5;

int n, m, q;
int head[N], nxt[M], to[M], tot = 1;
>>>>>>> 07e8fc721cf87637ca1e4d43005e936688912e6e

inline void addedge(int u, int v) {
	nxt[++tot] = head[u];
	to[tot] = v;
	head[u] = tot;
}

<<<<<<< HEAD
inline void tarjan(int u, int from) {
	dfn[u] = low[u] = ++dfncnt;
	stk[++top] = u;
	ins[u] = 1;
	for(int i = head[u]; i; i = nxt[i]) {
		if((i ^ 1) == from) continue;
=======
int dfn[N], low[N], bel[N], stk[N], top, ins[N], did, bid, rt;
vector<int> t[N];

inline void tarjan(int u, int from) {
	debug("tarjan({}, {})\n", u, from);
	dfn[u] = low[u] = ++did;
	stk[++top] = u, ins[u] = 1;
	for(int i = head[u]; i; i = nxt[i]) {
		if(i == (from ^ 1)) continue;
>>>>>>> 07e8fc721cf87637ca1e4d43005e936688912e6e
		int v = to[i];
		if(!dfn[v]) {
			tarjan(v, i);
			low[u] = min(low[u], low[v]);
<<<<<<< HEAD
			if(low[v] == dfn[v]) {
				++bid;
				while(stk[top] != u) {
					int x = stk[top--];
					bel[x] = bid;
					ins[x] = 0;
				}
=======
			if(dfn[v] == low[v]) {
				++bid;
				int x = 0;
				do {
					x = stk[top--];
					bel[x] = bid;
				} while(x != v);
>>>>>>> 07e8fc721cf87637ca1e4d43005e936688912e6e
			}
		} else if(ins[v]) {
			low[u] = min(low[u], dfn[v]);
		}
	}
<<<<<<< HEAD
=======
	
	ins[u] = 0;
	
>>>>>>> 07e8fc721cf87637ca1e4d43005e936688912e6e
	if(from == 0) {
		++bid;
		while(top) {
			int x = stk[top--];
			bel[x] = bid;
<<<<<<< HEAD
			ins[x] = 0;
=======
>>>>>>> 07e8fc721cf87637ca1e4d43005e936688912e6e
		}
	}
}

<<<<<<< HEAD
inline void dfs(int u, int fa) {
	dep[u] = dep[fa] + 1;
	eul[pos[u] = ++eid] = u;
	for(int v : adj[u]) {
=======
int dep[N], st[21][N], lg2[N], pos[N], eul[N<<1], eid;

inline int compare(int x, int y) {
	return dep[x] < dep[y] ? x : y;
}

inline void dfs(int u, int fa) {
	dep[u] = dep[fa] + 1;
	eul[pos[u] = ++eid] = u;
	for(int v : t[u]) {
>>>>>>> 07e8fc721cf87637ca1e4d43005e936688912e6e
		if(v != fa) {
			dfs(v, u);
			eul[++eid] = u;
		}
	}
}

<<<<<<< HEAD
inline int compare(int x, int y) {
	return dep[x] < dep[y] ? x : y;
}

void buildst() {
=======
void buildst() {
	lg2[0] = -1;
	rep(i, 1, eid) lg2[i] = lg2[i>>1] + 1;
	
>>>>>>> 07e8fc721cf87637ca1e4d43005e936688912e6e
	rep(i, 1, eid) st[0][i] = eul[i];
	rep(j, 1, 20) rep(i, 1, eid) {
		if(i + (1 << j) - 1 > eid) break;
		st[j][i] = compare(st[j-1][i], st[j-1][i+(1<<j-1)]);
	}
<<<<<<< HEAD
	lg2[0] = -1;
	rep(i, 1, eid) lg2[i] = lg2[i>>1] + 1;
=======
>>>>>>> 07e8fc721cf87637ca1e4d43005e936688912e6e
}

inline int LCA(int x, int y) {
	x = pos[x], y = pos[y];
	if(x > y) swap(x, y);
	int j = lg2[y - x + 1];
	return compare(st[j][x], st[j][y-(1<<j)+1]);
}

<<<<<<< HEAD
int nd[N<<2], vtn[N], vtp;
int delt[N], eu[N], ev[N], qr[N], cnt[N];
int k;
bool ok;

void buildvt() {
	sort(nd + 1, nd + k + 1, [&](int u, int v) { return pos[u] < pos[v]; });
	vtp = 0, top = 0;
	vtn[++vtp] = stk[++top] = rt;
	
	auto add = [&](int u, int v) {
		if(u == rt || v == rt) return;
=======
int nd[N], k, vtn[N], vtp;
int nn, mm, qa[N], qu[N], qv[N];

void buildvt() {
	vtp = top = 0;
	vtn[++vtp] = stk[++top] = rt;
	sort(nd + 1, nd + k + 1, [&](int x, int y) { return pos[x] < pos[y]; });
	nd[0] = rt;
	
	auto add = [&](int u, int v) {
		if(u == rt || v == rt) return;
		debug("{} {}\n", u, v);
>>>>>>> 07e8fc721cf87637ca1e4d43005e936688912e6e
		addedge(u, v);
		addedge(v, u);
	};
	
	rep(i, 1, k) {
		if(nd[i] == nd[i-1]) continue;
<<<<<<< HEAD
		//cerr << "vt insert = " << nd[i] << "\n";
		int lca = LCA(nd[i], stk[top]);
		while(dep[lca] < dep[stk[top]]) {
			if(dep[lca] < dep[stk[top-1]]) {
				add(stk[top-1], stk[top]);
			} else {
				add(stk[top], lca);
=======
		int lca = LCA(nd[i], stk[top]);
		while(dep[stk[top]] > dep[lca]) {
			if(dep[stk[top-1]] > dep[lca]) {
				add(stk[top], stk[top-1]);
			} else {
				add(lca, stk[top]);
>>>>>>> 07e8fc721cf87637ca1e4d43005e936688912e6e
			}
			--top;
		}
		if(stk[top] != lca) stk[++top] = lca, vtn[++vtp] = lca;
		if(stk[top] != nd[i]) stk[++top] = nd[i], vtn[++vtp] = nd[i];
<<<<<<< HEAD
		qr[nd[i]] = 1;
=======
>>>>>>> 07e8fc721cf87637ca1e4d43005e936688912e6e
	}
	rep(i, 2, top) add(stk[i], stk[i-1]);
}

<<<<<<< HEAD
void clear() {
	rep(i, 1, vtp) {
		int u = vtn[i];
		head[u] = 0;
		qr[u] = 0;
		delt[u] = 0;
		cnt[u] = 0;
		dfn[u] = low[u] = 0;
		ins[u] = 0;
	}
	dfncnt = 0;
	tot = 1;
	top = 0;
}

int fuck;
int fucked[N], a[N];

inline void tarjan2(int u, int from) {
	dfn[u] = low[u] = ++dfncnt;
	stk[++top] = u;
	// debug("top = {}, stk = {}\n", top, stk[top]);
	ins[u] = 1;
	for(int i = head[u]; i; i = nxt[i]) {
		if((i ^ 1) == from) continue;
=======
int bbel[N];

inline void tarjan2(int u, int from) {
	debug("tarjan2({}, {})\n", u, from);
	dfn[u] = low[u] = ++did;
	stk[++top] = u, ins[u] = 1;
	for(int i = head[u]; i; i = nxt[i]) {
		if(i == (from ^ 1)) continue;
>>>>>>> 07e8fc721cf87637ca1e4d43005e936688912e6e
		int v = to[i];
		if(!dfn[v]) {
			tarjan2(v, i);
			low[u] = min(low[u], low[v]);
<<<<<<< HEAD
			if(low[v] == dfn[v]) {
				++fuck;
				// debug("fuck on u = {}, v = {}\n", u, v);
				while(stk[top] != u) {
					int x = stk[top--];
					// debug("get x = {}\n", x);
					fucked[x] = fuck;
					ins[x] = 0;
				}
=======
			if(dfn[v] == low[v]) {
				++bid;
				int x = 0;
				do {
					x = stk[top--];
					bbel[x] = bid;
				} while(x != v);
>>>>>>> 07e8fc721cf87637ca1e4d43005e936688912e6e
			}
		} else if(ins[v]) {
			low[u] = min(low[u], dfn[v]);
		}
	}
<<<<<<< HEAD
	if(from == 0) {
		++fuck;
		// debug("fuckrt, top = {}\n", top);
		while(top) {
			int x = stk[top--];
			// debug("get x = {}\n", x);
			fucked[x] = fuck;
			ins[x] = 0;
=======
	
	ins[u] = 0;
	
	if(from == 0) {
		++bid;
		while(top) {
			int x = stk[top--];
			bbel[x] = bid;
>>>>>>> 07e8fc721cf87637ca1e4d43005e936688912e6e
		}
	}
}

<<<<<<< HEAD

int main() {
=======
bool check() {
	top = 0;
	bid = did = 0;
	rep(i, 1, vtp) {
		int u = vtn[i];
		if(!dfn[u]) tarjan2(u, 0);
	}
	rep(i, 2, nn) if(bbel[qa[i]] != bbel[qa[i-1]]) return 0;
	return 1;
}

void clear() {
	rep(i, 1, vtp) {
		int u = vtn[i];
		dfn[u] = low[u] = bbel[u] = 0;
		head[u] = 0;
		bbel[u] = 0;
		ins[u] = 0;
	}
	tot = 1;
}

int R;

void fuck(int& x) {
	x = (x + R) % n;
	if(x == 0) x = n;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
>>>>>>> 07e8fc721cf87637ca1e4d43005e936688912e6e
	cin >> n >> m >> q;
	rep(i, 1, m) {
		int u, v;
		cin >> u >> v;
		addedge(u, v);
		addedge(v, u);
	}
<<<<<<< HEAD
	rt = n + 1;
	rep(i, 1, n) {
		if(!dfn[i]) {
			tarjan(i, 0);
			adj[bel[i]].pb(rt);
			adj[rt].pb(bel[i]);
		}
	}
	rep(u, 1, n) {
		for(int i = head[u]; i; i = nxt[i]) {
			int v = to[i];
			if(bel[u] != bel[v]) adj[bel[u]].pb(bel[v]);
		}
	}
	
	dfs(rt, 0);
	buildst();
	
	memset(head, 0, sizeof head);
	memset(dfn, 0, sizeof dfn);
	memset(low, 0, sizeof low);
	tot = 1;
	
	while(q--) {
		cin >> nn >> mm;
		
		// debug("fucking on n = {}, m = {}\n", nn, mm);
		
		fuck = 0;
		k = 0;
		rep(i, 1, nn) {
			int x; cin >> x;
			x = bel[x];
			a[i] = x;
			nd[++k] = x;
			// cerr << x << " \n"[i == nn];
		}
		rep(i, 1, mm) {
			int u, v; cin >> u >> v;
			u = bel[u], v = bel[v];
			// cerr << u << " " << v << "\n";
			eu[i] = u, ev[i] = v;
			nd[++k] = u, nd[++k] = v;
=======
	
	rt = n + 1;
	rep(i, 1, n) if(!dfn[i]) {
		tarjan(i, 0);
		t[rt].pb(bel[i]);
		t[bel[i]].pb(rt);
	}
	
	rep(u, 1, n) for(int i = head[u]; i; i = nxt[i]) {
		int v = to[i];
		if(bel[u] != bel[v]) t[bel[u]].pb(bel[v]);
	}
	dfs(rt, 0);
	buildst();
	
	
	memset(head, 0, sizeof head);
	tot = 1;
	memset(dfn, 0, sizeof dfn);
	memset(low, 0, sizeof low);
	
	rep(T, 1, q) {
		k = 0;
		cin >> nn >> mm;
		rep(i, 1, nn) {
			cin >> qa[i];
			fuck(qa[i]);
			qa[i] = bel[qa[i]];
			nd[++k] = qa[i];
		}
		rep(i, 1, mm) {
			cin >> qu[i] >> qv[i];
			fuck(qu[i]), fuck(qv[i]);
			qu[i] = bel[qu[i]];
			qv[i] = bel[qv[i]];
			nd[++k] = qu[i], nd[++k] = qv[i];
>>>>>>> 07e8fc721cf87637ca1e4d43005e936688912e6e
		}
		
		buildvt();
		
<<<<<<< HEAD
		top = 0;
		
		rep(i, 1, mm) {
			int u = eu[i], v = ev[i];
			
			// debug("addedge = {} {}\n", u, v);
			
			addedge(u, v);
			addedge(v, u);
		}
		
		// rep(i, 1, vtp) cerr << vtn[i] << " \n"[i == vtp];
		
		rep(i, 1, vtp) {
			int u = vtn[i];
			if(u == rt) continue;
			if(!dfn[u]) tarjan2(u, 0);
		}
		
		bool ok = 1;
		
		// rep(i, 1, nn) debug("nd = {}, fucked = {}\n", a[i], fucked[a[i]]);
		
		rep(i, 2, nn) {
			int u = a[i], v = a[i-1];
			if(fucked[u] != fucked[v]) ok = 0;
		}
		
		cout << (ok ? "YES" : "NO") << "\n";
		
		clear();
	}
	
	return 0;
}
=======
		rep(i, 1, mm) {
			debug("{} {}\n", qu[i], qv[i]);
			addedge(qu[i], qv[i]);
			addedge(qv[i], qu[i]);
		}
		
		bool ok = check();
		if(ok) {
			cout << "YES" << "\n";
			R = (R + T) % n;
		} else {
			cout << "NO" << "\n";
		}
		clear();
		assert(dfn[2] == 0);
	}
	
	return 0;
}
>>>>>>> 07e8fc721cf87637ca1e4d43005e936688912e6e

// Problem: P2762 太空飞行计划问题
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P2762
// Memory Limit: 125 MB
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

const int N = 105;
const int M = 1e7 + 5;
const int inf = 0x3f3f3f3f;

int n, m, e, s, t;
int cur[N], head[N], nxt[M], to[M], fl[M], tot = 1;
int dis[N];
int que[N], ph=1, pt=0;

inline void addedge(int u, int v, int f) {
	if(f) debug("{} {} {}\n", u, v, f);
	nxt[++tot] = head[u];
	to[tot] = v;
	fl[tot] = f;
	head[u] = tot;
}

inline bool bfs() {
	memset(dis, 0, sizeof dis);
	memcpy(cur, head, sizeof cur);
	ph=1, pt=0;
	dis[s] = 1;
	que[++pt] = s;
	while(ph <= pt) {
		int u = que[ph++];
		for(int i = head[u]; i; i = nxt[i]) {
			int v = to[i];
			int f = fl[i];
			if(f && !dis[v]) {
				dis[v] = dis[u] + 1;
				que[++pt] = v;
			}
		}
	}
	return dis[t];
}

inline int dfs(int u, int l) {
	if(u == t) return l;
	int res = 0;
	for(int& i = cur[u]; i; i = nxt[i]) {
		int v = to[i];
		int f = fl[i];
		if(f && dis[v] == dis[u] + 1) {
			int x = dfs(v, min(l, f));
			l -= x;
			fl[i] -= x;
			fl[i^1] += x;
			res += x;
		}
		if(!l) break;
	}
	if(l) dis[u] = -1;
	return res;
}

int dinic() {
	int res = 0;
	while(bfs()) res += dfs(s, inf);
	return res;
}

inline vector<int> cut() {
    vector<int> res;
    static int que[N], hea = 1, tail = 0;
    hea = 1, tail = 0;
    static bool vis1[N], vis2[N];
    memset(vis1, 0, sizeof vis2);
    memset(vis2, 0, sizeof vis2);

    {
        que[++tail] = s;
        vis1[s] = 1;
        while (hea <= tail) {
            int u = que[hea++];
            for (int e = head[u]; e; e = nxt[e]) {
                int v = to[e];
                int w = fl[e];
                if (w && !vis1[v])
                    vis1[v] = 1, que[++tail] = v;
            }
        }
    }

    rep(i, 1, tail) {
    	int u = que[i];
        for (int e = head[u]; e; e = nxt[e]) {
            int v = to[e];
            if (vis1[u] && !vis1[v]) {
                res.pb(e);
            }
        }
    }
    return res;
}

char ss[10006];
int a[N], b[N];
int e1[N], e2[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	int ans = 0;
	
	
	cin >> n >> m;
	
	
	s = n+m+1, t = n+m+2;
	
	string tmp; getline(cin, tmp);
	rep(i, 1, n) {
		string str;
		getline(cin, str);
		stringstream ss(str);
		int v; ss >> v;
		ans += v;
		e1[i] = tot+1;
		addedge(s, i, v);
		addedge(i, s, 0);
		int x;
		while(ss >> x) {
			addedge(i, x+n, inf);
			addedge(x+n, i, 0);
		}
	}
	rep(i, 1, m) {
		int v; cin >> v;
		e2[i] = tot+1;
		addedge(i+n, t, v);
		addedge(t, i+n, 0);
	}
	
	int fl = dinic();
	
	auto eg = cut();
	set<int> e;
	for(int i : eg) e.insert(i);
	
	vector<int> ans1, ans2;
	
	rep(i, 1, n) if(!e.count(e1[i]) && !e.count(e1[i]^1)) ans1.pb(i);
	rep(i, 1, m) if(e.count(e2[i]) || e.count(e2[i]^1)) ans2.pb(i);
	
	if(ans1.empty()) cout << "\n";
	else rep(i, 0, ans1.size()-1) cout << ans1[i] << " \n"[i == ans1.size()-1];
	
	
	if(ans2.empty()) cout << "\n";
	else rep(i, 0, ans2.size()-1) cout << ans2[i] << " \n"[i == ans2.size()-1];
	
	cout << ans - fl << "\n";
	
	return 0;
}

// Problem: P4013 数字梯形问题
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4013
// Memory Limit: 250 MB
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

const int N = 1e3 + 5;
const int M = 5e6 + 5;


const int inf = 0x3f3f3f3f;

int n, m, s, t;
int head[N], nxt[M<<1], to[M<<1], cost[M<<1], wgt[M<<1], tot = 1;
int dis[N], in[N], from[N];
bool inq[N];
int a[N][N], id[N][N], icnt;

inline void addedge(int u, int v, int w, int c) {
	nxt[++tot] = head[u];
	to[tot] = v;
	wgt[tot] = w;
	cost[tot] = c;
	head[u] = tot;
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
			int v = to[e], w = cost[e], f = wgt[e];
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

void clear() {
	memset(head, 0, sizeof head);
	tot = 1;
}

int solve1() {
	clear();
	rep(i, 1, n) rep(j, 1, m+i-1) {
		addedge(id[i][j], id[i][j]+icnt, 1, -a[i][j]);
		addedge(id[i][j]+icnt, id[i][j], 0, a[i][j]);
	}
	rep(i, 2, n) rep(j, 1, m+i-1) {
		if(j-1) {
			addedge(id[i-1][j-1]+icnt, id[i][j], 1, 0);
			addedge(id[i][j], id[i-1][j-1]+icnt, 0, 0);
		}
		if(j != m+i-1) {
			addedge(id[i-1][j]+icnt, id[i][j], 1, 0);
			addedge(id[i][j], id[i-1][j]+icnt, 0, 0);
		}
	}
	rep(i, 1, m) {
		addedge(s, id[1][i], 1, 0);
		addedge(id[1][i], s, 0, 0);
	}
	rep(i, 1, n+m-1) {
		addedge(id[n][i]+icnt, t, 1, 0);
		addedge(t, id[n][i]+icnt, 0, 0);
	}
	return -mcmf().se;
}

int solve2() {
	clear();
	rep(i, 1, n) rep(j, 1, m+i-1) {
		addedge(id[i][j], id[i][j]+icnt, inf, -a[i][j]);
		addedge(id[i][j]+icnt, id[i][j], 0, a[i][j]);
	}
	rep(i, 2, n) rep(j, 1, m+i-1) {
		if(j != m+i-1) {
			addedge(id[i-1][j]+icnt, id[i][j], 1, 0);
			addedge(id[i][j], id[i-1][j]+icnt, 0, 0);
		}
		if(j-1) {
			addedge(id[i-1][j-1]+icnt, id[i][j], 1, 0);
			addedge(id[i][j], id[i-1][j-1]+icnt, 0, 0);
		}
	}
	int ss = 2*icnt+1, tt = 2*icnt+2;
	addedge(s, ss, m, 0);
	addedge(ss, s, 0, 0);
	addedge(tt, t, m, 0);
	addedge(t, tt, 0, 0);
	rep(i, 1, m) {
		addedge(ss, id[1][i], 1, 0);
		addedge(id[1][i], ss, 0, 0);
	}
	rep(i, 1, n+m-1) {
		addedge(id[n][i]+icnt, tt, inf, 0);
		addedge(tt, id[n][i]+icnt, 0, 0);
	}
	return -mcmf().se;
}

int solve3() {clear();
	rep(i, 1, n) rep(j, 1, m+i-1) {
		addedge(id[i][j], id[i][j]+icnt, inf, -a[i][j]);
		addedge(id[i][j]+icnt, id[i][j], 0, a[i][j]);
	}
	rep(i, 2, n) rep(j, 1, m+i-1) {
		if(j != m+i-1) {
			addedge(id[i-1][j]+icnt, id[i][j], inf, 0);
			addedge(id[i][j], id[i-1][j]+icnt, 0, 0);
		}
		if(j-1) {
			addedge(id[i-1][j-1]+icnt, id[i][j], inf, 0);
			addedge(id[i][j], id[i-1][j-1]+icnt, 0, 0);
		}
	}
	int ss = 2*icnt+1, tt = 2*icnt+2;
	addedge(s, ss, m, 0);
	addedge(ss, s, 0, 0);
	addedge(tt, t, m, 0);
	addedge(t, tt, 0, 0);
	rep(i, 1, m) {
		addedge(ss, id[1][i], 1, 0);
		addedge(id[1][i], ss, 0, 0);
	}
	rep(i, 1, n+m-1) {
		addedge(id[n][i]+icnt, tt, inf, 0);
		addedge(tt, id[n][i]+icnt, 0, 0);
	}
	return -mcmf().se;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> m >> n;
	rep(i, 1, n) {
		rep(j, 1, m+i-1) {
			cin >> a[i][j];
			id[i][j] = ++icnt;
		}
	}
	
	s = ++icnt, t = ++icnt;
	
	debug("icnt = {}\n", icnt);
	
	cout << solve1() << "\n";
	cout << solve2() << "\n";
	cout << solve3() << "\n";
	
	return 0;
}

// Problem: P5297 [北京省选集训2019]完美塔防
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5297
// Memory Limit: 128 MB
// Time Limit: 1000 ms

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

const int N = 55;
const int nxt[4][2] = {
	{0, 1}, {1, 0}, {-1, 0}, {0, -1}
};

char s[N][N];
int n, m;
int v[N][N][2];
bool vis[N][N][2], inq[N][N][2];
vector<int> adj[2*N*N];
int ans[N*N], id[N][N], nid;

void bfs(int x, int y) {
	memset(inq, 0, sizeof inq);
	
	int p = id[x][y];
	queue<tuple<int, int, int>> q;
	
	auto check = [&](int i, int j) { return 1 <= i && i <= n && 1 <= j && j <= m && s[i][j] != '#'; };
	
	rep(i, 0, 3) q.push({x, y, i});
	inq[x][y][0] = inq[x][y][1] = 1;
	
	while(!q.empty()) {
		auto [x, y, t] = q.front(); q.pop();
		
		int tt = t == 0 || t == 3 ? 0 : 1;
		
		if(vis[x][y][tt]) continue;
		
		if(v[x][y][tt]) vis[x][y][tt] = 1;
		else v[x][y][tt] = p;
		
		if(s[x][y] == '/') t ^= 2;
		if(s[x][y] == '\\') t ^= 1;
		
		x += nxt[t][0];
		y += nxt[t][1];
		
		if(check(x, y)) q.push({x, y, t});
	}
}


int dfn[2*N*N], low[2*N*N], dfncnt, ins[2*N*N], stk[2*N*N], top, scc[2*N*N], scccnt;
inline void tarjan(int u) {
	dfn[u] = low[u] = ++dfncnt;
	ins[u] = 1;
	stk[++top] = u;
	for(int v : adj[u]) {
		if(!dfn[v]) {
			tarjan(v);
			low[u] = min(low[u], low[v]);
		} else if(ins[v]) {
			low[u] = min(low[u], dfn[v]);
		}
	}
	if(dfn[u] == low[u]) {
		++scccnt;
		while(1) {
			int x = stk[top--];
			ins[x] = 0;
			scc[x] = scccnt;
			if(x == u) break;
		}
	}
}

void solve() {
	nid = 0;
	memset(id, 0, sizeof id);
	memset(v, 0, sizeof v);
	memset(ans, 0, sizeof ans);
	memset(vis, 0, sizeof vis);
	memset(dfn, 0, sizeof dfn);
	dfncnt = scccnt = 0;
	
	cin >> n >> m;
	rep(i, 1, 2*n*m) adj[i].clear();
	rep(i, 1, n) cin >> s[i] + 1;
	
	rep(i, 1, n) rep(j, 1, m) if(s[i][j] == '-' || s[i][j] == '|') id[i][j] = ++nid, bfs(i, j);
	
	rep(i, 1, n
	
	rep(i, 1, n) rep(j, 1, m) {
		if(s[i][j] == '.') {
			if((vis[i][j][0] || !v[i][j][0]) && (vis[i][j][1] || !v[i][j][1])) {
				cout << "IMPOSSIBLE" << "\n";
				return;
			}
			if(vis[i][j][0] || !v[i][j][0]) {
				adj[v[i][j][1]].pb(v[i][j][1]+nid);
			} else if(vis[i][j][1] || !v[i][j][1]) {
				adj[v[i][j][0]+nid].pb(v[i][j][0]);
			} else {
				int a = v[i][j][0], b = v[i][j][1];
				adj[a+nid].pb(b+nid);
				adj[b].pb(a);
			}
		}
	}
	
	rep(i, 1, 2*nid) if(!dfn[i]) tarjan(i);
	
	rep(i, 1, nid) {
		if(scc[i] == scc[i+nid]) {
			cout << "IMPOSSIBLE" << "\n";
			return;
		}
	}
	
	cout << "POSSIBLE" << "\n";
	rep(i, 1, n) {
		rep(j, 1, m) {
			if(s[i][j] == '-' || s[i][j] == '|') {
				cout << "|-"[scc[id[i][j]] < scc[id[i][j]+nid]];
			} else {
				cout << s[i][j];
			}
		}
		cout << "\n";
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

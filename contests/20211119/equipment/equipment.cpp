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

std::mt19937 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

const int N = 1e5 + 5;

int n, m, k;
int c[N], a[N], b[N], pos[N];
vector<int> bpos[N];
vector<int> adj[N], radj[N];
int cyc[N], vis[N], dep[N];
int t[N], tt;
int stk[N], top;

inline void dfsc(int u, int st) {
    t[u] = tt;
    if(t[pos[b[u]]] == tt) {
	cyc[u] = -1;
	return;
    }
    if(!pos[b[u]]) {
	cyc[u] = 1;
	return;
    }
    if(!t[pos[b[u]]]) dfsc(pos[b[u]], st);
    cyc[u] = cyc[pos[b[u]]];
}

inline void dfsd(int u) {
    //cerr << "dfsd = " << u << "\n";
    if(dep[u]) return;
    if(!pos[b[u]]) dep[u] = 1;
    else {
	dfsd(pos[b[u]]);
	dep[u] = dep[pos[b[u]]] + 1;
    }
}

inline void dfss(int u) {
    stk[++top] = u;
    if(!pos[b[u]]) return;
    dfss(pos[b[u]]);
}

inline void dfsvis(int u) {
    vis[u] = 1;
    for(int v : bpos[a[u]]) if(!vis[v]) dfsvis(v);
}

int dfn[N], dfncnt, siz[N];
int bit[N];

inline int lowbit(int x) { return x & (-x); }
inline void add(int x, int p) { for(int x0 = x; x0 <= m; x0 += lowbit(x0)) bit[x0] += p; }
inline void add(int l, int r, int p) { add(l, p), add(r+1, -p); }
inline int query(int x) { int res = 0; for(int x0 = x; x0; x0 -= lowbit(x0)) res += bit[x0]; return res; }

inline void dfsdfn(int u) {
    //cerr << "dfsdfn = " << u << "\n";
    dfn[u] = ++dfncnt;
    siz[u] = 1;
    add(dfn[u], dfn[u], dep[u]);
    for(int v : radj[u]) dfsdfn(v), siz[u] += siz[v];
}

int main() {
    freopen("equipment.in", "r", stdin);
    freopen("equipment.out", "w", stdout);
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    cin >> n >> m >> k;
    rep(i, 1, n) cin >> c[i];
    rep(i, 1, m) cin >> a[i] >> b[i], pos[a[i]] = i, bpos[b[i]].pb(i);

    rep(i, 1, m) if(pos[b[i]])  radj[pos[b[i]]].pb(i);

    per(i, 1, m) {
	if(!cyc[i]) {
	    ++tt;
	    dfsc(i, i);
	    if(cyc[i] == 1 && !dep[i]) dfsd(i);
	}
    }

    rep(i, 1, m) if(pos[b[i]] == 0) dfsdfn(i);

//    cerr << "ok init" << "\n";

    vector<int> res;

//    rep(i, 1, m) cerr << dfn[i] << " \n"[i == m];
    
    per(u, 1, m) {
	if(cyc[u] == 1) {
	    int d = query(dfn[u]);
	    if(c[a[u]] < c[b[u]] && !vis[u] && d <= k) {
		top = 0;
		dfss(u);
		assert(top == d);

		add(dfn[u], dfn[u]+siz[u]-1, -d);
		
		while(top) {
		    int p = stk[top--];
		    pos[a[p]] = 0;
		    assert(!pos[b[p]]);
		    pos[b[p]] = p;
		    swap(a[p], b[p]);
		    if(!vis[p]) dfsvis(p);
		    res.pb(p), --k;
		}
	    }
	    if(!vis[u] && c[a[u]] != c[b[u]]) dfsvis(u);
	}
    }

    cout << res.size() << "\n";
    for(int x : res) cout << x << "\n";

    return 0;
}
    

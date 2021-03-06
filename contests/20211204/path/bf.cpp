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

int n, m;

namespace forces {

    const int N = 2e3 + 5;
    const int inf = 0x3f3f3f3f;

    int cur[N], head[N], nxt[N<<1], to[N<<1], fl[N<<1], tot = 1;
    int h0[N], n0[N<<1], t0[N<<1], f0[N<<1], tt0;
    int dep[N], s, t;
    int n, m;

    inline void init() {
	memcpy(head, h0, sizeof head);
	memcpy(nxt, n0, sizeof nxt);
	memcpy(to, t0, sizeof to);
	memcpy(fl, f0, sizeof fl);
	tot = tt0;
    }

    bool bfs() {
	memset(dep, -1, sizeof dep);
	memcpy(cur, head, sizeof head);
	dep[s] = 0;
	static int que[N];
	int ph = 1, pt = 0;
	que[++pt] = s;
	while(ph <= pt) {
	    int u = que[ph++];
	    for(int i = head[u]; i; i = nxt[i]) {
		if(fl[i]) {
		    int v = to[i];
		    if(dep[v] == -1) {
			dep[v] = dep[u] + 1;
			que[++pt] = v;
		    }
		}
	    }
	}
	return dep[t] != -1;
    }

    int dinic(int u, int f) {
	if(u == t) return f;
	int res = 0;
	for(int& i = cur[u]; i; i = nxt[i]) {
	    if(!fl[i]) continue;
	    int v = to[i], w = min(f, fl[i]);
	    if(dep[v] == dep[u] + 1) {
		int x = dinic(v, w);
		res += x;
		fl[i] -= x;
		fl[i^1] += x;
		f -= x;
	    }
	    if(f == 0) return res;
	}
	return res;
    }

    int solve() {
	int res = 0;
	while(bfs()) res += dinic(s, inf);
	return res;
    }

    inline void addedge(int u, int v, int w) {
	nxt[++tot] = head[u];
	to[tot] = v;
	fl[tot] = w;
	head[u] = tot;
    }

    int main() {
	rep(i, 1, m) {
	    int u, v;
	    cin >> u >> v;
	    addedge(u, v, 1);
	    addedge(v, u, 0);
	}

	memcpy(h0, head, sizeof head);
	memcpy(n0, nxt, sizeof nxt);
	memcpy(f0, fl, sizeof fl);
	memcpy(t0, to, sizeof to);
	tt0 = tot;

	s = n+1, t = n+2;
    
	rep(i, 2, n) {
	    init();
	    addedge(s, 1, inf);
	    addedge(1, s, 0);
	    addedge(i, t, inf);
	    addedge(t, i, 0);
	    cout << solve() << "\n";
	}
    
	return 0;
    }
    
}

namespace sub1 {
    const int N = 1e5 + 5;
    const int M = 2e5 + 5;
    int n, m;
    int head[N], nxt[M<<1], to[M<<1], tot, oud[N];
    int f[N], ans[N], ind[N];
    bool vis[N];
    int que[N], ph = 1, pt = 0;

    inline void addedge(int u, int v) {
	nxt[++tot] = head[u];
	to[tot] = v;
	head[u] = tot;
	++oud[u];
	++ind[v];
    }

    void bfs() {
	vis[1] = 1;
	que[++pt] = 1;
	while(ph <= pt) {
	    int u = que[ph++];
	    for(int i = head[u]; i; i = nxt[i]) {
		int v = to[i];
		if(!vis[v]) {
		    vis[v] = 1;
		    que[++pt] = v;
		}
	    }
	}
    }
    
    void solve1() {
	rep(i, 2, n) cout << vis[i] << "\n";
    }

    void solve2() {
	memset(f, -1, sizeof f);
	memset(ind, 0, sizeof ind);
	rep(u, 1, n) {
	    for(int i = head[u]; i; i = nxt[i]) {
		int v = to[i];
		if(vis[u] && vis[v]) {
		    ++ind[v];
		}
	    }
	}
	f[1] = 0;
	que[++pt] = 1;
	while(ph <= pt) {
	    int u = que[ph++];
	    for(int i = head[u]; i; i = nxt[i]) {
		int v = to[i];
		if(!vis[v]) continue;
		if(f[v] == -1) f[v] = f[u] == 0 ? i : f[u];
		else if(f[v] != 0) {
		    if(f[u] != f[v]) f[v] = 0;
		}
		if(--ind[v] == 0) que[++pt] = v;
	    }
	}
	rep(i, 2, n) {
	    if(f[i] == -1) cout << 0;
	    else if(f[i] == 0) cout << 2;
	    else cout << 1;
	    cout << "\n";
	}
    }
    
    void main() {
	rep(i, 1, m) {
	    int u, v;
	    cin >> u >> v;
	    addedge(u, v);
	}
	bfs();
	if(oud[1] == 1) solve1();
	else solve2();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    cin >> n >> m;
    if(n <= 1e3 && m <= 2e3) {
	forces::n = n;
	forces::m = m;
	forces::main();
	return 0;
    } else {
	sub1::n = n;
	sub1::m = m;
	sub1::main();
    }

    return 0;
}

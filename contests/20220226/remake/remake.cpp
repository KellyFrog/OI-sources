#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define rep(i, s, t) for(int i = (s); i <= (t); ++i)
#define per(i, s, t) for(int i = (t); i >= (s); --i)
#define fi first
#define se second
#define pb push_back
#define mp make_pair

const int N = 105;
const int M = 205;
const long double inf = 1e18;
const double eps = 1e-9;

struct E {
    int v, w, x;
    E(int v, int w, int x) : v(v), w(w), x(x) {}
};

int n, m, L, l = 100 * 100;
vector<E> adj[N];
long double f[N][N*N];
long double val;
ll dis[N];
bool vis[N];

inline void dfs(int u) {
    if(vis[u]) return;
    vis[u] = 1;
    if(adj[u].empty()) {
	rep(i, 0, min(l, L)) f[u][i] = 0;
	return;
    }
    int sum = 0;
    for(auto e : adj[u]) dfs(e.v), sum += e.x;

    rep(i, 0, min(l, L)) {
	for(auto e : adj[u]) {
	    long double p = (long double)e.x / sum;
	    long double vf = i + e.w > L ? inf : f[e.v][i + e.w];
	    f[u][i] += p * (min(vf, val) + e.w);
	}
    }
}

bool check(long double mid) {
    val = mid;
    memset(f, 0, sizeof f);
    memset(vis, 0, sizeof vis);
    dfs(1);
    return f[1][0] <= val;
}

int main() {

    clock_t stime = clock();
    freopen("remake.in", "r", stdin);
    freopen("remake.out", "w", stdout);
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    cin >> n >> m >> L;
    rep(i, 1, m) {
	int u, v, w, x;
	cin >> u >> v >> w >> x;
	if(v == 1) continue;
	adj[u].pb(E(v, w, x));
    }

/*
    if(adj[1].size() == m && 0) {
	int sum = 0;
	for(auto e : adj[1]) sum += e.x;
	long double a = 0, c = 0;
	for(auto e : adj[1]) {
	    long double p = (long double)e.x / sum;
	    if(e.w <= L) {
		c += p * e.w;
	    } else {
		a += p;
		c += p * e.w;
	    }
	}
	cout << setprecision(15) << c / (1 - a) << "\n";
	return 0;
    }
*/
    //tree

    long double l = 0, r = 1e9;
    long double res = 1e9;
    
    while((long double)(clock() - stime) / CLOCKS_PER_SEC < 0.9) {
	long double mid = (l + r) / 2;
	if(check(mid)) res = mid, r = mid;
	else l = mid;
    }
    
    cout << setprecision(15) << res << endl;
    
    return 0;
}

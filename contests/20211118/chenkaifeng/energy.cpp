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

template<typename T>
inline void upd(T& x, T y) {
    if(x > y) x = y;
}

const int N = 1e3 + 5;
const int M = 2e2 + 5;
const int inf = 0x3f3f3f3f;

int f[N][N], tmp[N];
vector<pair<int, int>> adj[N];
int a[N], siz[N];
int n;

inline void dfs(int u) {
    f[u][0] = 0;
    if(u) f[u][1] = a[u];
    siz[u] = 1;
    for(auto e : adj[u]) {
	int v = e.fi, w = e.se;

	dfs(v);

	memcpy(tmp, f[u], sizeof tmp);

	rep(i, 0, siz[u]) {
	    rep(j, 0, siz[v]) {
		if(f[v][j] > w) break;
		upd(f[u][i+j], tmp[i] + f[v][j]);
	    }
	}
	siz[u] += siz[v];
    }
}

int main() {
    freopen("energy.in", "r", stdin);
    freopen("energy.out", "w", stdout);
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    cin >> n;
    rep(i, 1, n) {
	int fa, w;
	cin >> fa >> a[i] >> w;
	adj[fa].pb(mp(i, w));
    }

    memset(f, 0x3f, sizeof f);

    dfs(0);
    int ans = 0;

    /*
    rep(i, 0, n) {
	rep(j, 0, n) {
	    if(f[i][j] != inf) cerr << f[i][j] << " ";
	}
	cerr << "\n";
    }
    */
	    
    rep(i, 0, n) if(f[0][i] != inf) ans = i;
    cout << ans << "\n";

    cout.flush();
    
    return 0;
}
    

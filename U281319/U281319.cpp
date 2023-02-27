// Problem: U281316 倍数（multi）
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/U281319
// Memory Limit: 256 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

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

const int N = 5e4 + 5;
const int inf = 0x3f3f3f3f;
const ll P = 2.5e9 + 1;

int n, m, k;
vector<int> adj[N];
pair<int, int> a[N];
int dis[2][N], b[N];
ll d[N<<1];

ll qpow(ll x, ll p) {
	ll res = 1, base = x;
	while(p) {
		if(p & 1) res = res * base % P;
		base = base * base % P;
		p >>= 1;
	}
	return res;
}

void solve() {
	cin >> n >> m >> k;
	rep(i, 1, n) adj[i].clear();
	rep(i, 1, k) {
		int x, y; cin >> x >> y;
		a[i] = mp(x, y);
		adj[x].pb(y);
		b[i] = x;
	}
	b[++k] = n;
	sort(b + 1, b + k + 1);
	int p = unique(b + 1, b + k + 1) - b - 1;

	rep(i, 0, n+m-2) d[i] = 0;
	auto add = [&](int l, int r, int x) {
		if(l <= r) {
			d[l] += x, d[r+1] -= x;
		}
   	};

	b[0] = 1;
	rep(i, 1, m) dis[0][i] = inf;
	rep(i, 1, p) {
		rep(j, 0, m+1) dis[i&1][j] = inf;
		rep(j, 1, k-1) dis[i&1][a[j].se] = min(dis[i&1][a[j].se], abs(b[i]-a[j].fi));
		rep(j, 1, m) dis[i&1][j] = min(dis[i&1][j], dis[i&1][j-1]+1);
		per(j, 1, m) dis[i&1][j] = min(dis[i&1][j], dis[i&1][j+1]+1);
		rep(j, 1, m) {
			int x = b[i] + b[i-1] + dis[i&1][j] - dis[i-1&1][j] >> 1;
			if(x >= b[i]) x = b[i] - 1;
			if(x < b[i-1]) x = b[i-1] - 1;
			add(dis[i-1&1][j], dis[i-1&1][j] + x - b[i-1], 1);
			add(dis[i&1][j] + 1, dis[i&1][j] + b[i] - x - 1, 1);
		}
	}
	rep(i, 1, m) add(dis[p&1][i], dis[p&1][i], 1);
	ll ans = 1;
	rep(i, 1, n+m-2) d[i] += d[i-1];
	rep(i, 1, n+m-2) d[i] += d[i-1];
	ll inv = 1;
	rep(i, 0, n+m-2) {
		ans = ans * (d[i]-i) % P; 
		inv = inv * (1ll * n * m - i) % P;
	}
	cout << ans * qpow(inv, P-2) % P << "\n";
}
	


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	int t; cin >> t;
	while(t--) solve();

	return 0;
}

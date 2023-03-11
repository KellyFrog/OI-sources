// Problem: P8290 [省选联考 2022] 填树
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P8290
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// Create Time: 2022-05-10 10:55:10
// Input/Output: stdin/stdout
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

const int N = 211;
const int P = 1e9 + 7;
const int inv2 = (P + 1) / 2;

int qpow(int x, int p) {
	int res = 1, base = x;
	while(p) {
		if(p & 1) res = 1ll * res * base % P;
		base = 1ll * base * base % P;
		p >>= 1;
	}
	return res;
}

int f[N][N], g[N][N], ans1[N], ans2[N], tp[N], siz[N];
int l[N], r[N], n, k;
vector<int> adj[N];
int x[N][N], y[N][N], fac[N], ifac[N];
int pre[N], suf[N];

void init() {
	ifac[0] = fac[0] = ifac[1] = fac[1] = 1;
	rep(i, 2, n+2) fac[i] = 1ll * fac[i-1] * i % P;
	ifac[n+2] = qpow(fac[n+2], P - 2);
	per(i, 2, n+1) ifac[i] = 1ll * ifac[i+1] * (i+1) % P;

	rep(i, 0, n+1) {
		int sum = 0;
		rep(j, 0, i+2) {
			sum = (sum + qpow(j, i)) % P;
			x[i][j+1] = j;
			y[i][j+1] = sum;
		}
	}
}

int getsum(int k, int val) {
	pre[1] = val - x[k][1];
	suf[k+2] = val - x[k][k+2];
	pre[0] = 1, suf[k+3] = 1;
	rep(i, 2, k+2) pre[i] = 1ll * pre[i-1] * (val - x[k][i]) % P;
	per(i, 1, k+1) suf[i] = 1ll * suf[i+1] * (val - x[k][i]) % P;
	int res = 0;
	rep(i, 1, k+2) {
		int t = (k+2-i & 1 ? -1ll : 1ll) * y[k][i] * ifac[i-1] % P * ifac[k+2-i] % P;
		res = (res + 1ll * t * pre[i-1] % P * suf[i+1]) % P;
	}
	return res;
}

int tmp[N];

inline void update(int tar[], int f[], int g[], int h[], int n, int m, int p) {
	rep(i, 0, n+m) tmp[i] = 0;
	rep(i, 0, n) rep(j, 0, m) tmp[i+j] = (tmp[i+j] + 1ll * f[i] * g[j]) % P;
	rep(i, 0, n+m) rep(j, 0, p) tar[i+j] = (tar[i+j] + 1ll * tmp[i] * h[j]) % P;
}

inline void update(int tar[], int f[], int g[], int n, int m) {
	rep(i, 0, n) rep(j, 0, m) tar[i+j] = (tar[i+j] + 1ll * f[i] * g[j]) % P;
}

inline void update(int tar[], int f[], int n) {
	rep(i, 0, n) tar[i] = (tar[i] + f[i]) % P;
}

inline void dfs(int u, int fa, int k) {
	siz[u] = 1;
	memset(f[u], 0, sizeof f[u]);
	memset(g[u], 0, sizeof g[u]);
	int f1[4] = {0, 0, 0, 0};
	int f2[4] = {0, 0, 0, 0};
	if(tp[u] == 1) {
		f1[0] = (r[u] - l[u] + 1) % P;
		f2[0] = (1ll * (l[u] + r[u]) * (r[u] - l[u] + 1) / 2) % P;
	} else if(tp[u] == 2) {
		f1[0] = (r[u] + 1) % P;
		f1[1] = -1;
		f2[0] = (1ll * r[u] * (r[u] + 1) / 2) % P;
		f2[1] = inv2;
		f2[2] = -inv2;
	} else if(tp[u] == 3) {
		f1[0] = (k - l[u] + 1) % P;
		f1[1] = 1;
		f2[0] = (1ll * (k + l[u]) * (k - l[u] + 1) / 2) % P;
		f2[1] = 1ll * (2ll * k + 1) * inv2 % P;
		f2[2] = inv2;
	} else if(tp[u] == 4) {
		f1[0] = (k + 1) % P;
		f2[0] = (1ll * k * (k + 1) / 2) % P;
		f2[1] = (k + 1) % P;
	}
	memcpy(f[u], f1, sizeof f1);
	memcpy(g[u], f2, sizeof f2);
	update(ans1, f1, 1);
	update(ans2, f2, 2);

	for(int v : adj[u]) if(v != fa) dfs(v, u, k);

	for(int i = 0; i < adj[u].size(); ++i) {
		int x = adj[u][i];
		if(x == fa) continue;
		update(ans1, f[x], f1, siz[x], 1);
		update(ans2, g[x], f1, siz[x] + 1, 1);
		update(ans2, f[x], f2, siz[x], 2);
		update(f[u], f[x], f1, siz[x], 1);
		update(g[u], f[x], f2, siz[x], 2);
		update(g[u], g[x], f1, siz[x] + 1, 1);
		for(int j = i + 1; j < adj[u].size(); ++j) {
			int y = adj[u][j];
			if(y == fa || y == x) continue;
			update(ans1, f[x], f[y], f1, siz[x], siz[y], 1);
			update(ans2, g[x], f[y], f1, siz[x] + 1, siz[y], 1);
			update(ans2, f[x], g[y], f1, siz[x], siz[y] + 1, 1);
			update(ans2, f[x], f[y], f2, siz[x], siz[y], 2);
		}
	}

	for(int v : adj[u]) if(v != fa) siz[u] += siz[v];
}

int pos[N<<2];

pair<int, int> solve(int k) {

	int res1 = 0, res2 = 0;
	rep(i, 1, n) pos[i] = l[i], pos[i+n] = max(1, r[i] - k), pos[i+2*n] = r[i] + 1, pos[i+3*n] = max(1, l[i] - k - 1);
	pos[0] = 0;
	pos[4*n+1] = 1e9;
	sort(pos, pos + 4 * n + 2);

	rep(i, 1, 4*n+1) {
		int p = k == ::k ? pos[i-1]+1 : max(pos[i-1]+1, 2);
		if(p > pos[i]) continue;
		int x = p;
		memset(ans1, 0, sizeof ans1);
		memset(ans2, 0, sizeof ans2);
		rep(u, 1, n) {
			if(r[u] < x || l[u] > x + k) tp[u] = 0;
			else if(x < l[u] && r[u] < x + k) tp[u] = 1;
			else if(l[u] <= x && r[u] < x + k) tp[u] = 2;
			else if(x < l[u] && x + k <= r[u]) tp[u] = 3;
			else if(l[u] <= x && x + k <= r[u]) tp[u] = 4;
		}

		dfs(1, 0, k);

		rep(j, 0, n+1) {
			int sum = (getsum(j, pos[i]) - getsum(j, p-1)) % P;
			res1 = (res1 + 1ll * ans1[j] * sum) % P;
			res2 = (res2 + 1ll * ans2[j] * sum) % P;
		}
	}

	return mp(res1, res2);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> k;
	rep(i, 1, n) cin >> l[i] >> r[i];
	rep(i, 1, n-1) {
		int u, v;
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	}

	init();

	auto [x1, y1] = solve(k);
	auto [x2, y2] = solve(k-1);

	int ans1 = (x1 - x2) % P;
	int ans2 = (y1 - y2) % P;
	
	cout << (ans1 + P) % P << "\n";
	cout << (ans2 + P) % P << "\n";

	return 0;
}
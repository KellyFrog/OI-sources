// Problem: T263663 游走
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T263663
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// Create Time: 2022-08-11 19:08:27
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

const int N = 405;
const int P = 1e9 + 7;

int qpow(int x, int p) {
	int res = 1, base = x;
	while(p) {
		if(p & 1) res = 1ll * res * base % P;
		base = 1ll * base * base % P;
		p >>= 1;
	}
	return res;
}

int n, m, q, t;
int p[N][N][4], f[N][N][N];
int qx[N], qy[N], qz[N][4], last[N][N];
int vis[N][N];
bool ism[N][N];
int a[N][N], b[N], c[N][N], d[N];
vector<tuple<int, int, int>> tr[N<<2];
int stk[N], top;
int res[N], inv[N];

int insert() {
	rep(i, 1, t) {
		if(b[i]) {
			if(!a[i][i]) {
				memcpy(a[i], b, sizeof a[i]);
				inv[i] = qpow(a[i][i], P - 2);
				return i;
			} else {
				int x = 1ll * b[i] * inv[i] % P;
				rep(j, i, t+1) {
					b[j] = (b[j] - 1ll * x * a[i][j]) % P;
				}
			}
		}
	}
	// assert(0);
	return 0;
}

inline void insert(int o, int ql, int qr, int i, int j, int id, int l, int r) {
	if(ql <= l && r <= qr) {
		tr[o].emplace_back(i, j, id);
		return;
	}
	int mid = l + r >> 1;
	if(ql <= mid) insert(o << 1, ql, qr, i, j ,id, l, mid);
	if(mid < qr) insert(o << 1 | 1, ql, qr, i, j, id, mid + 1, r);
}

inline void dfs(int o, int l, int r) {
	int top0 = top;
	for(auto [i, j, x]  : tr[o]) {
		memset(b, 0, sizeof b);
		int p[4];
		if(x == 0) memcpy(p, ::p[i][j], sizeof p);
		else memcpy(p, ::qz[x], sizeof p);
		rep(k, 1, t+1) b[k] = (f[i][j][k] - 1ll * p[0] * f[i-1][j][k] - 1ll * p[1] * f[i+1][j][k] - 1ll * p[2] * f[i][j-1][k] - 1ll * p[3] * f[i][j+1][k]) % P;
		b[t+1] = -b[t+1] + 1;
		stk[++top] = insert();
	}
	if(l == r) {
		memcpy(c, a, sizeof c);
		per(i, 1, t) per(j, 1, i-1) {
			if(c[j][i]) {
				int x = 1ll * c[j][i] * inv[i] % P;
				int k = 0;
				k = j; c[j][k] = (c[j][k] - 1ll * c[i][k] * x) % P;
				k = t+1; c[j][k] = (c[j][k] - 1ll * c[i][k] * x) % P;
			}
		}
		rep(i, 1, t) d[i] = 1ll * c[i][t+1] * inv[i] % P;
		d[t+1] = 1;
		int ans = 0;
		rep(k, 1, t+1) ans = (ans + 1ll * res[k] * d[k]) % P;
		cout << (ans + P) % P << "\n";
	} else {
		int mid = l + r >> 1;
		dfs(o << 1, l, mid);
		dfs(o << 1 | 1, mid + 1, r);
	}
	while(top0 < top) {
		memset(a[stk[top]], 0, sizeof a[stk[top]]);
		--top;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> m >> q;
	rep(i, 1, n) rep(j, 1, m) rep(k, 0, 3) cin >> p[i][j][k];
	rep(i, 1, m) vis[1][i] = ++t;
	rep(i, 1, m) ism[n][i] = 1;
	rep(i, 1, q) {
		cin >> qx[i] >> qy[i];
		rep(j, 0, 3) cin >> qz[i][j];
		if(!vis[qx[i]+1][qy[i]]) vis[qx[i]+1][qy[i]] = ++t;
		ism[qx[i]][qy[i]] = 1;
		insert(1, last[qx[i]][qy[i]], i-1, qx[i], qy[i], last[qx[i]][qy[i]], 0, q);
		last[qx[i]][qy[i]] = i;
	}
	rep(i, 1, n) rep(j, 1, m) if(ism[i][j]) insert(1, last[i][j], q, i, j, last[i][j], 0, q);
	rep(i, 1, n) rep(j, 1, m) {
		if(!vis[i][j]) {
			int inv = qpow(p[i-1][j][1], P - 2);
			f[i][j][t+1] = ((f[i-1][j][t+1] - 1ll * p[i-1][j][0] * (f[i-2][j][t+1] + 1) - 1ll * p[i-1][j][2] * (f[i-1][j-1][t+1] + 1) - 1ll * p[i-1][j][3] * (f[i-1][j+1][t+1] + 1)) % P * inv - 1) % P;
			rep(k, 1, t) f[i][j][k] = (f[i-1][j][k] - 1ll * p[i-1][j][0] * f[i-2][j][k] - 1ll * p[i-1][j][2] * f[i-1][j-1][k] - 1ll * p[i-1][j][3] * f[i-1][j+1][k]) % P * inv % P;
		} else {
			f[i][j][vis[i][j]] = 1;
		}
	}
	rep(i, 1, n) rep(j, 1, m) rep(k, 1, t+1) res[k] = (res[k] + f[i][j][k]) % P;
	dfs(1, 0, q);
	
	return 0;
}

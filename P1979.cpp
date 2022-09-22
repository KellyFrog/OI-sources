// Problem: P1979 [NOIP2013 提高组] 华容道
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P1979
// Memory Limit: 125 MB
// Time Limit: 1000 ms
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

const int N = 35;
const int inf = 0x3f3f3f3f;
const int step[4][2] = {
	{-1, 0}, {1, 0}, {0, -1}, {0, 1}
};

int n, m, q;
int a[N][N], d[N][N], dis[N*N*5];
bool vis[N*N*5];
vector<pair<int, int>> adj[N*N*5];

inline bool check(int x, int y) {
	return x < 1 || x > n || y < 1 || y > m || a[x][y] == 0;
}

inline int id(int x, int y) { return m * (x-1) + y; }

inline void bfs(int sx, int sy) {
	memset(d, inf, sizeof d);
	queue<pair<int, int>> q;
	q.emplace(sx, sy), d[sx][sy] = 0;
	while(!q.empty()) {
		auto [x, y] = q.front(); q.pop();
		rep(k, 0, 3) {
			int nx = x + step[k][0], ny = y + step[k][1];
			if(check(nx, ny)) continue;
			if(d[nx][ny] > d[x][y] + 1) {
				d[nx][ny] = d[x][y] + 1;
				q.emplace(nx, ny);
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> m >> q;
	rep(i, 1, n) rep(j, 1, m) cin >> a[i][j];
	rep(i, 1, n) rep(j, 1, m) {
		if(a[i][j] == 0) continue;
		a[i][j] = 0;
		rep(k, 0, 3) {
			int nx = i + step[k][0];
			int ny = j + step[k][1];
			if(check(nx, ny)) continue;
			bfs(nx, ny);
			rep(kk, 0, 3) if(kk != k) {
				int tx = i + step[kk][0];
				int ty = j + step[kk][1];
				if(check(tx, ty)) continue;
				adj[id(i, j) + k * n * m].emplace_back(id(i, j) + kk * n * m, d[tx][ty]);
			}
			adj[id(i, j) + k * n * m].emplace_back(id(nx, ny) + (k ^ 1) * n * m, 1);
		}
		a[i][j] = 1;
	}


	while(q--) {
		int ex, ey, sx, sy, tx, ty;
		cin >> ex >> ey >> sx >> sy >> tx >> ty;
		if(sx == tx && sy == ty) {
			cout << 0 << "\n";
			continue;
		}
		a[sx][sy] = 0;
		bfs(ex, ey);
		a[sx][sy] = 1;
		memset(dis, 0x3f, sizeof dis);
		memset(vis, 0, sizeof vis);
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
		rep(i, 0, 3) {
			int nx = sx + step[i][0];
			int ny = sy + step[i][1];
			if(check(nx, ny)) continue;
			pq.emplace(dis[id(sx, sy) + i * n * m] = d[nx][ny], id(sx, sy) + i * n * m);
		}
		while(!pq.empty()) {
			int u = pq.top().se; pq.pop();
			if(vis[u]) continue;
			vis[u] = 1;
			for(auto [v, w] : adj[u]) {
				if(dis[v] > dis[u] + w) {
					pq.emplace(dis[v] = dis[u] + w, v);
				}
			}
		}
		int ans = inf;
		rep(i, 0, 3) ans = min(ans, dis[id(tx, ty) + i * n * m]);
		cout << (ans == inf ? -1 : ans) << "\n"; 
	}

	return 0;
}

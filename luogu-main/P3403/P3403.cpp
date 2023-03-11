// Problem: P3403 跳楼机
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3403
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define pf push_front
#define rep(i, s, t) for (int i = s; i <= t; ++i)
#define per(i, s, t) for (int i = t; i >= s; --i)

const int N = 1e5 + 5;

ll h;
int a, b, c;
ull dis[N];
bool vis[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> h >> a >> b >> c;
	
	rep(i, 0, a-1) dis[i] = LONG_LONG_MAX;
	priority_queue<pair<ull, int>, vector<pair<ull, int>>, greater<pair<ull, int>>> pq;
	pq.emplace(dis[1%a] = 1, 1);
	while(!pq.empty()) {
		int u = pq.top().se; pq.pop();
		if(vis[u]) continue;
		vis[u] = 1;
		auto upd = [&](int v, ull d) {
			if(d < dis[v]) pq.emplace(dis[v] = d, v);
		};
		upd((u + b) % a, dis[u] + b);
		upd((u + c) % a, dis[u] + c);
	}
	ll ans = 0;
	rep(i, 0, a-1) {
		if(dis[i] <= h) ans += (h - dis[i]) / a + 1;
	}
	cout << ans << "\n";
	
	return 0;
}

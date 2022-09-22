// Problem: AT2046 [AGC004F] Namori
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT2046
// Memory Limit: 250 MB
// Time Limit: 2000 ms
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

const int N = 1e5 + 5;

int n, m;
vector<int> adj[N];
int uni[N], dep[N], cnt[N][2], s[N][2];
ll ans = 0;
int eu = 1, ev = 1;

inline int find(int x) { return x == uni[x] ? x : uni[x] = find(uni[x]); }

inline void dfs(int u, int fa) {
	dep[u] = dep[fa] ^ 1;
	cnt[u][dep[u]] = 1;
	cnt[u][dep[u]^1] = 0;
	cnt[u][0] += s[u][0];
	cnt[u][1] += s[u][1];

	for(int v : adj[u]) if(v != fa) {
		dfs(v, u);
		cnt[u][0] += cnt[v][0];
		cnt[u][1] += cnt[v][1];
	}
	ans += abs(cnt[u][0] - cnt[u][1]);
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> m;
	rep(i, 1, n) uni[i] = i;
	rep(i, 1, m) {
		int u, v; cin >> u >> v;
		int x = find(u), y = find(v);
		if(x == y) {
			eu = u, ev = v;
		} else {
			adj[u].pb(v);
			adj[v].pb(u);
			uni[x] = y;
		}
	}

	dfs(1, 0);
	if(n & 1) {
		cout << -1 << "\n";
		return 0;
	}
	if(dep[eu] == dep[ev]) {
		ans = 0;

		if(eu != ev) {
			int x = abs(cnt[1][0] - cnt[1][1]) / 2;
			if((cnt[1][0] < cnt[1][1]) ^ (dep[eu] & 1)) {
				s[eu][dep[eu]] += x;
				s[ev][dep[ev]] += x;
			} else {
				s[eu][dep[eu]^1] += x;
				s[ev][dep[ev]^1] += x;
			}
			ans += x;
		}

		dfs(1, 0);

		
		if(cnt[1][0] != cnt[1][1]) {
			cout << -1 << "\n";
			return 0;
		}
		cout << ans << "\n";
	} else {
	}


	
	return 0;
}

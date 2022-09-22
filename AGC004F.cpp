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
int uni[N];
int eu = 1, ev = 1;

inline int find(int x) { return x == uni[x] ? x : uni[x] = find(uni[x]); }

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
		}
	}
	
	return 0;
}

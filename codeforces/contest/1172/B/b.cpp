
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

const int N = 2e5 + 5;
const int P = 998244353;

int n;
vector<int> adj[N];
int siz[N], fac[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n;
	rep(i, 2, n) {
		int u, v; cin >> u >> v;
		adj[u].pb(v), adj[v].pb(u);
	}

	fac[0] = 1;
	rep(i, 1, n) fac[i] = 1ll * fac[i-1] * i % P;

	int ans = n;
	rep(i, 1, n) ans = 1ll * ans * fac[adj[i].size()] % P;
	cout << ans << "\n";
	
	return 0;
}

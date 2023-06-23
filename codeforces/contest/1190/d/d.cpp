/*
 * Author: ChenKaifeng@codeforces
 * Create Time: 2023.06.23, 13:15:03 (UTC +8)
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

const int N = 2e5 + 5;

int n;
int a[N], b[N], c[N], d[N];
vector<int> adj[N];
bool vis[N];
int t[N];

inline int lowbit(int x) { return x & (-x); }
inline void add(int x, int val) { for(int x0 = x; x0 <= n; x0 += lowbit(x0)) t[x0] += val; }
inline int query(int x) { int ret = 0; for(int x0 = x; x0; x0 -= lowbit(x0)) ret += t[x0]; return ret; }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n;
	rep(i, 1, n) cin >> a[i] >> b[i], c[i] = b[i], d[i] = a[i];
	sort(c + 1, c + n + 1);
	sort(d + 1, d + n + 1);
	int m = unique(c + 1, c + n + 1) - c - 1;
	int k = unique(d + 1, d + n + 1) - d - 1;

	rep(i, 1, n) {
		a[i] = lower_bound(d + 1, d + k + 1, a[i]) - d;
		b[i] = lower_bound(c + 1, c + m + 1, b[i]) - c;
	}

	rep(i, 1, n) adj[b[i]].pb(a[i]);
	int t = 0;
	ll ans = 0;
	per(i, 1, m) {
		sort(adj[i].begin(), adj[i].end());
		adj[i].pb(k+1);
		for(int k = 0; k+1 < adj[i].size(); ++k) {
			int j = adj[i][k];
			if(!vis[j]) {
				add(j, 1);
				vis[j] = 1;
			}
			ans += 1ll * query(j) * (query(adj[i][k+1]-1) - query(j-1));

		}
	}
	cout << ans << "\n";
	
	return 0;
}

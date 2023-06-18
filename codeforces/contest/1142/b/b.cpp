/*
 * Author: ChenKaifeng@codeforces
 * Create Time: 2023.06.17, 21:08:$%s$ (UTC +8)
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

int n, m, q;
int a[N], b[N], c[N], pos[N];
int f[N], g[N], lst[N];
vector<pair<int, int>> adj[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> m >> q;
	rep(i, 1, n) cin >> a[i], c[a[i]] = i;
	rep(i, 1, m) cin >> b[i], b[i] = c[b[i]];
	rep(i, 1, m) {
		if(b[i] == 1) f[i] = i, lst[1] = i;
		else {
			if(lst[b[i]-1]) f[i] = f[lst[b[i]-1]], lst[b[i]] = i;
			else f[i] = -1;
		}
	}
	memset(lst, 0, sizeof lst);
	per(i, 1, m) {
		if(b[i] == n) g[i] = i, lst[n] = i;
		else {
			if(lst[b[i]+1]) g[i] = g[lst[b[i]+1]], lst[b[i]] = i;
			else g[i] = -1;
		}
	}
	rep(i, 1, m) if(g[i] != -1) adj[b[i]].emplace_back(g[i], i);
	rep(i, 1, m) {
		if(f[i] == -1) {
			pos[i] = -1;
		} else if(b[i] == n) {
			pos[i] = f[i];
		} else {
			int j = f[i];
			auto it = lower_bound(adj[b[i]+1].begin(), adj[b[i]+1].end(), mp(j, 0));
			if(it == adj[b[i]+1].begin()) pos[i] = -1;
			else pos[i] = (it-1)->se;
		}
	}
	rep(i, 1, m) pos[i] = max(pos[i], pos[i-1]);
	while(q--) {
		int l, r; cin >> l >> r;
		cout << (l <= pos[r]);
	}

	
	return 0;
}

/*
 * Author: zhengguoge@codeforces
 * Create Time: 2023.06.18, 16:05:04 (UTC +8)
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

const int N = 105;

int n;
char s1[N], s2[N];
int f[N][2][2];
bool vis[N][2][2];

inline int dfs(int i, bool a, bool b) {
	if(i == n+1) return 0;
	if(vis[i][a][b]) return f[i][a][b];
	int r = a ? s2[i] - '0' : 9;
	int l = b ? s1[i] - '0' : 0;
	rep(x, l, r) rep(y, l, r) {
		bool a0 = a && x == r;
		bool b0 = b && y == l;
		if(a && b && l > r) continue;
		f[i][a][b] = max(f[i][a][b], dfs(i+1, a0, b0) + abs(x-y));
	}
	vis[i][a][b] = 1;
	return f[i][a][b];
}

void solve() {
	cin >> (s1 + 1) >> (s2 + 1);
	n = max(strlen(s1 + 1), strlen(s2 + 1));
	if(strlen(s1 + 1) < n) {
		int m = strlen(s1 + 1);
		per(i, n-m+1, n) s1[i] = s1[i-(n-m)];
		rep(i, 1, n-m) s1[i] = '0';
	}
	memset(f, 0, sizeof f);
	memset(vis, 0, sizeof vis);
	cout << dfs(1, 1, 1) << "\n";
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

// Problem: A - Copy and Paste Graph
// Contest: AtCoder - AtCoder Regular Contest 159
// URL: https://atcoder.jp/contests/arc159/tasks/arc159_a
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Create Time: 2023-04-12 19:19:46
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

const int N = 205;
const int inf = 0x3f3f3f3f;

int n, k, q;
int d[N][N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> k;
	rep(i, 1, n) rep(j, 1, n) {
		int w; cin >> w;
		if(w == 0) w = inf;
		d[i][j] = d[i+n][j] = d[i][j+n] = d[i+n][j+n] = d[i][j] = w;
	}
	rep(k, 1, 2*n) rep(i, 1, 2*n) rep(j, 1, 2*n) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

	cin >> q;
	while(q--) {
		ll x, y; cin >> x >> y;
		x = (x - 1) % n + 1;
		y = (y - 1) % n + 1 + n;
		cout << (d[x][y] == inf ? -1 : d[x][y]) << "\n";
	}
	
	return 0;
}


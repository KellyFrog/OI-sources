// Problem: D - Colorful Balls
// Contest: AtCoder - AtCoder Grand Contest 012
// URL: https://atcoder.jp/contests/agc012/tasks/agc012_d
// Memory Limit: 256 MB
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

const int N = 2e5 + 5;
const int P = 1e9 + 7;

int n, x, y;
int c[N], w[N], cnt[N], fac[N], ifac[N];
vector<int> adj[N];

int qpow(int x, int p) {
	int res = 1, base = x;
	while(p) {
		if(p & 1) res = 1ll * res * base % P;
		base = 1ll * base * base % P;
		p >>= 1;
	}
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> x >> y;
	rep(i, 1, n) {
		cin >> c[i] >> w[i];
		adj[c[i]].pb(w[i]);
	}

	int p1 = 0, p2 = 0;
	rep(i, 1, n) {
		if(!adj[i].empty()) {
			sort(adj[i].begin(), adj[i].end());
			if(p1 == 0 || adj[i][0] < adj[p1][0]) p2 = p1, p1 = i;
			else if(p2 == 0 || adj[i][0] < adj[p2][0]) p2 = i;
		}
	}
	fac[0] = ifac[0] = fac[1] = ifac[1] = 1;
	rep(i, 2, n) fac[i] = 1ll * fac[i-1] * i % P;
	ifac[n] = qpow(fac[n], P-2);
	per(i, 2, n-1) ifac[i] = 1ll * ifac[i+1] * (i+1) % P;
	int ans = 1, sum = 0;
	rep(i, 1, n) {
		if(!adj[i].empty()) {
			int p = p1 == i ? p2 : p1;
			if(p == 0) continue;
			if(adj[i][0] + adj[p][0] <= y) {
				int cc = 0;
				for(int j = 0; j < adj[i].size(); ++j) if(adj[i][j] + adj[p][0] <= y) cc = max(cc, j+1);
				for(int j = 1; j < adj[i].size(); ++j) if(adj[i][j] + adj[i][0] <= x) cc = max(cc, j+1);
				sum += cc;
				ans = 1ll * ans * ifac[cc] % P;
			}
		}
	}
	ans = 1ll * ans * fac[sum] % P;
	cout << ans << "\n";

	
	return 0;
}

// Problem: CF771E Bear and Rectangle Strips
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF771E
// Memory Limit: 250 MB
// Time Limit: 3000 ms
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

const int N = 3e5 + 5;

int n;
ll a[2][N], s[2][N];
int nxt[3][N];
map<int, int> f[N][2];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n;
	rep(i, 0, 1) rep(j, 1, n) cin >> a[i][j];
	rep(i, 0, 1) rep(j, 1, n) s[i][j] = s[i][j-1] + a[i][j];
	rep(s, 0, 3) {
		map<ll, int> lst;
		per(j, 1, n) {
			ll v1 = (s & 1) * s[0][j] + (s >> 1 & 1) * s[1][j];
			ll v2 = (s & 1) * s[0][j-1] + (s >> 1 & 1) * s[1][j-1];
			lst[v1] = j;
			if(lst.count(v2)) nxt[s][j] = lst[v2];
		}
	}
	f[0][1][0] = 0;

	auto upd = [&](int i, int j, int v) {
		if(i < j) f[i][0][j] = max(f[i][0][j], v);
		else f[j][1][i] = max(f[j][1][i], v);
	};

	rep(i, 0, n-1) {
		int p1 = -1, p2 = -1;
		int fv = f[i][1][i];
		for(auto [j, v] : f[i][0]) if(v == fv + 1) {
			p1 = j;
			break;
		}
		for(auto [j, v] : f[i][1]) if(v == fv + 1) {
			p2 = j;
			break;
		}
		upd(i+1, i, fv);
		upd(i, i+1, fv);
		if(p1 != -1) {
			upd(p1, p1, fv + 1);
			if(nxt[1][i+1]) upd(nxt[1][i+1], p1, fv + 2);
		}
		if(p2 != -1) {
			upd(p2, p2, fv + 1);
			if(nxt[0][i+1]) upd(nxt[0][i+1], p2, fv + 2);
		}

	}

	cout << f[n][1][n] << "\n";

	return 0;
}

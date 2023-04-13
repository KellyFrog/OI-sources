// Problem: AT_agc006_c [AGC006C] Rabbit Exercise
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_agc006_c
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

const int N = 1e5 + 5;

int n, m;
ll k, a[N], b[N], c[N];
int f[64][N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n;
	rep(i, 1, n) cin >> a[i], b[i] = a[i] - a[i-1];
	cin >> m >> k;
	rep(i, 1, n) f[0][i] = i;
	rep(i, 1, m) {
		int x; cin >> x;
		swap(f[0][x], f[0][x+1]);
	}
	rep(j, 1, 63) rep(i, 1, n) f[j][i] = f[j-1][f[j-1][i]];
	rep(i, 1, n) {
		int p = i;
		per(j, 0, 63) if(k >> j & 1) p = f[j][p];
		c[i] = b[p];
	}
	c[1] = a[1];
	rep(i, 2, n) c[i] += c[i-1];
	rep(i, 1, n) cout << c[i] << "\n";

	
	return 0;
}

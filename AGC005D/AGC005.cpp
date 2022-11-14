// Problem: D - ~K Perm Counting
// Contest: AtCoder - AtCoder Grand Contest 005
// URL: https://atcoder.jp/contests/agc005/tasks/agc005_d
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

const int N = 2e3 + 5;
const int P = 924844033;

int n, k, a[N];
int f[N][N], g[N][N], fac[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> k;
	rep(i, 1, n) a[i] = i % k + 1;
	sort(a + 1, a + n + 1);
	g[0][0] = f[0][0] = 1;
	int last = 0;
	rep(i, 1, n) {
		if(a[i] != a[i-1]) last = i;
		rep(j, 0, i) {
			if(j >= 1) {
            	f[i][j] = (f[i][j] + f[i-1][j-1]) % P;
              f[i][j] = (f[i][j] + ((i & 1) ? 2ll : -2ll) * (g[i-2][j-1] - (last == 1 ? 0 : g[last-2][j-1]))) % P;
            }
			if(a[i] == a[i-1]) f[i][j] = (f[i][j] + f[i-2][j]) % P;
			
			g[i][j] = (g[i-1][j] + ((i & 1) ? -1 : 1) * f[i][j]) % P;
		}
	}

	fac[0] = 1;
	rep(i, 1, n) fac[i] = 1ll * fac[i-1] * i % P;

	int ans = 0;
	rep(i, 0, n) ans = (ans + 1ll * f[n][i] * fac[i]) % P;
	cout << (ans + P) % P << "\n";
	
	return 0;
}

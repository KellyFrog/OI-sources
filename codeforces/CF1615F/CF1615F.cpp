// Problem: CF1615F LEGOndary Grandmaster
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1615F
// Memory Limit: 500 MB
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
const int P = 1e9 + 7;

int n;
char s[N], t[N];
int a[N], b[N];
int f[N][2*N], g[N][2*N];

void solve() {
	cin >> n;
	cin >> (s + 1) >> (t + 1);
	rep(i, 1, n) {
		a[i] = s[i] == '?' ? -1 : ((i & 1) ^ (s[i] - '0'));
		b[i] = t[i] == '?' ? -1 : ((i & 1) ^ (t[i] - '0'));
	}
	rep(i, 0, n+1) rep(j, 0, 2*n+1) f[i][j] = 0, g[i][j] = 0;
	f[0][n] = g[n+1][n] = 1;
	rep(i, 1, n) {
	   rep(x, 0, 1) rep(y, 0, 1) {
	   	   if(a[i] != -1 && a[i] != x) continue;
		   if(b[i] != -1 && b[i] != y) continue;
		   int d = x - y;
		   rep(j, 1, 2*n+1) f[i][j] = (f[i][j] + f[i-1][j+d]) % P;
	   }
	}
	per(i, 1, n) {
		rep(x, 0, 1) rep(y, 0, 1) {
	   	   if(a[i] != -1 && a[i] != x) continue;
		   if(b[i] != -1 && b[i] != y) continue;
		   int d = x - y;
		   rep(j, 1, 2*n+1) g[i][j] = (g[i][j] + g[i+1][j+d]) % P;
		}
	}
	int ans = 0;
	rep(i, 1, n-1) rep(j, -n, n) ans = (ans + 1ll * f[i][n+j] * g[i+1][n-j] % P * abs(j)) % P;
	cout << ans << "\n";
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

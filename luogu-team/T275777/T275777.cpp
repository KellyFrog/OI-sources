// Problem: T275777 Sultan Rage
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T275777?contestId=85210
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// Create Time: 2022-10-03 14:42:18
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
const int P = 998244353;

int n, m, q;
ll a[N];
int f[N][N*N], g[N][N];
bool vis[N];
int s[N], suf[N];

void solve() {
	cin >> m >> q;
	memset(a, 0, sizeof a);
	memset(f, 0, sizeof f);
	memset(vis, 0, sizeof vis);
	memset(s, 0, sizeof s);
	memset(suf, 0, sizeof suf);
	rep(i, 1, m) cin >> a[i];
	per(i, 1, m) suf[i] = suf[i+1] + a[i];
	n = m;
	
	do {
		++n;
		rep(j, 1, m) a[n] = min((ll)1e18 + 5, a[n] + a[n-j]);
	} while(a[n] <= (ll)1e18);
	a[n] = 0;
	--n;
	int k = 1e4;
	f[0][0] = 1;
	rep(i, 1, m) {
		rep(j, 0, k) {
			f[i][j] = f[i-1][j];
			if(j >= a[i]) f[i][j] = (f[i][j] + f[i-1][j-a[i]]) % P;
		}
	}

	while(q--) {
		memset(vis, 0, sizeof vis);
		
		ll x; cin >> x;
		per(i, m+1, n) if(x >= a[i]) {
			vis[i] = 1, x -= a[i];
		}

		rep(i, m+1, n) s[i] = s[i-1] + vis[i];
		memset(g, 0, sizeof g);
		g[n+1][n+1] = 1;
		per(i, m+1, n) {
			rep(j, 1, n+1) g[i][j] = (g[i][j] + g[i+1][j]) % P;
			if(vis[i]) {
				if(s[i] - s[i-m] == 1)g[i-m][i-m] = (g[i-m][i-m] + g[i][i]) % P;
				g[i][i] = 0;
				rep(j, i+1, n+1) g[i][i] = (g[i][i] + g[i+1][j]) % P, g[i][j] = 0;
				if(s[i] - s[i-m] == 1)g[i-m][i-m] = (g[i-m][i-m] + g[i][i]) % P;
			} else if(s[i-1] - s[i-m] == 0) g[i-m][i-m] = (g[i-m][i-m] + g[i][i]) % P;
		}

		int ans = 0;
		rep(j, 1, n+1) {
			int jj = x + suf[min(m+1, j)];
			if(jj > k) break;
			rep(i, 1, m+1) {
				ans = (ans + 1ll * 
				g[i][j] * 
				f[m][jj]) % P;
			}
		}
		cout << ans << "\n";
	}
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

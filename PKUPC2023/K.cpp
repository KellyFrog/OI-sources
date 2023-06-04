#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define rep(i, s, t) for(int i = (s); i <= (t); ++i)
#define per(i, s, t) for(int i = (t); i >= (s); --i)
#define fi first
#define se second
#define mp make_pair
#define pb push_back

const int N = 25;
const int M = 3000 + 5;

int n, m = 3000, k;
int a[N];
long double f[N][M], g[M][M];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	cout << fixed << setprecision(15);

	cin >> n >> k;
	rep(i, 1, n) cin >> a[i];
	if(k > m) {
		cout << 0 << "\n";
		return 0;
	}
	g[0][0] = g[1][0] = g[2][0] = 1;
	rep(i, 3, m) rep(j, 1, m) {
		if(i % 3 == 2) {
			g[i][j] = 0.25 * g[i-2][j-1] + 0.75 * g[i-3][j-1];
		} else {
			g[i][j] = 0.10 * (j >= 2 ? g[i-3][j-2] : 0) + 0.90 * g[i-3][j-1];
		}
	}
	f[1][0] = 1;
	rep(i, 1, n) {
		per(j, a[i], m) f[i][j] = f[i][j-a[i]];
		rep(j, 0, a[i]-1) f[i][j] = 0;
		rep(j, 0, m) {
			if(f[i][j] < 1e-9) continue;
			rep(k, 0, m) f[i+1][k] += f[i][j] * g[j][k];
		}
	}
	long double ans = 0;
	rep(i, k, m) ans += f[n][i];
	cout << ans << "\n";

	return 0;
}

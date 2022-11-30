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

const int N = 1e3 + 5;
const int P = 998244353;

int n, m;
char s[N][N];
int f[N][N], g[N][N], h[N][N];

void solve() {
	int t1, t2;
	cin >> n >> m >> t1 >> t2;
	rep(i, 1, n) cin >> (s[i] + 1);
	memset(f, 0, sizeof f);
	memset(g, 0, sizeof g);
	memset(h, 0, sizeof h);
	rep(i, 1, n) per(j, 1, m) f[i][j] = s[i][j] == '0' ? f[i][j+1] + 1 : 0;
	rep(i, 1, n) rep(j, 1, m) f[i][j] = max(f[i][j]-1, 0);
	rep(i, 1, n) rep(j, 1, m) g[i][j] = s[i][j] == '0' ? g[i-1][j] + f[i][j] : 0;
	rep(i, 1, n) rep(j, 1, m) if(s[i][j] == '0' && s[i-1][j] == '0') h[i][j] = 1ll * g[i-2][j] * f[i][j] % P;
	int ans1 = 0, ans2 = 0;
	rep(i, 1, n) rep(j, 1, m) {
		ans1 = (ans1 + h[i][j]) % P;
		if(s[i][j] == '0') {
			h[i][j] = (h[i][j] + h[i-1][j]) % P;
			ans2 = (ans2 + h[i][j]) % P;
		}
	}
	ans2 -= ans1;
	ans2 = (ans2 + P) % P;
	cout << t1 * ans1 << " " << t2 * ans2 << "\n";

}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	int t, id; cin >> t >> id;
	while(t--) solve();

	return 0;
}

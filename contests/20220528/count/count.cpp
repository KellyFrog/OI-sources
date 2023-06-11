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

mt19937_64 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

const int P = 998244353;

int qpow(int x, ll p) {
	int res = 1, base = x;
	while(p) {
		if(p & 1) res = 1ll * res * base % P;
		base = 1ll * base * base % P;
		p >>= 1;
	}
	return res;
}

int n, m;

namespace sub1 {
	const int N = 1e6 + 5;

	int f[N];

	void solve() {
		assert(m == 1);
		f[1] = 0, f[2] = 1;
		rep(i, 3, n) {
			f[i] = 1ll * (i-1) * (f[i-1] + f[i-2]) % P;
		}
		int ans = 0;
		rep(i, 1, n) ans ^= f[i];
		cout << ans << "\n";
	}
}

namespace sub2 {
	const int N = 5e3 + 5;
	int fac[N], ifac[N];
	int f[N], g[2][N];

	void solve() {
		int t = n * m;
		fac[0] = ifac[0] = fac[1] = ifac[1] = 1;
		rep(i, 2, t) fac[i] = 1ll * fac[i-1] * i % P;
		ifac[t] = qpow(fac[t], P - 2);
		per(i, 2, t-1) ifac[i] = 1ll * ifac[i+1] * (i+1) % P;

		rep(i, 0, m) {
			f[i] = 1ll * fac[m] * ifac[i] % P * ifac[m-i] % P * ifac[m-i] % P;
		}

		g[0][0] = 1;
		int ans0 = 0;
		rep(i, 1, n) {
			int ans = 0;
			rep(j, 0, i*m) {
				g[i&1][j] = 0;
				rep(k, 0, m) {
					if(k > j) break;
					g[i&1][j] = (g[i&1][j] + 1ll * g[i-1&1][j-k] * f[k]) % P;
				}
				ans = (ans + ((j & 1) ? (-1ll) : (1ll)) * fac[i*m-j] * g[i&1][j]) % P;
			}
			if(ans < 0) ans += P;
			ans0 ^= ans;
		}
		cout << ans0 << "\n";
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	freopen("count.in", "r", stdin);
	freopen("count.out", "w", stdout);

	cin >> n >> m;

	if(m == 1) {
		sub1::solve();
	} else {	
		sub2::solve();
	}
	
	return 0;
}
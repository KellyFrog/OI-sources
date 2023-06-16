/*
 * Author: chenkaifeng @BDFZ
 */
 
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

std::mt19937 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

const int N = 5e2 + 1;
const int mod = 998244353;

int n, a[N], win[N][N], cob[N][N], fac[N], ifac[N], inv[N];
int f[N][N][N], g[N][N][N];

int qpow(int x, ll p) {
    int res = 1, base = x;
    while(p) {
	if(p & 1) res = 1ll * res * base % mod;
	base = 1ll * base * base % mod;
	p >>= 1;
    }
    return res;
}

namespace sub2 {

    int f[N][N], g[N][N];
    
    void solve() {
	rep(i, 1, n) {
	    f[1][i] = 1;
	    rep(j, 1, n) g[1][j] = win[j][i];
	}

	rep(i, 1, n) inv[i] = qpow(i, mod-2);
	
	rep(len, 2, n) {
	    int sum = 0;
	    int r = len, l = 1;
	    rep(i, 1, len) {
		__int128 res = 0;
		rep(k, l, r-1) {
		    if(i <= k) {
			res += 1ll * f[k-l+1][i] * g[r-k][i];
		    } else {
			res += 1ll * g[k-l+1][i] * f[r-k][i];
		    }
		}
		f[r-l+1][i] = res * inv[r-l] % mod;
	    }
	    rep(j, 1, n) {
		if(l <= j && j <= r) continue;
		__int128 res = 0;
		rep(i, l, r) {
		    res += 1ll * f[r-l+1][i] * win[j][i];
		}
		g[r-l+1][j] = res % mod;
	    }
	}
	rep(i, 1, n) cout << f[n][i] << " \n"[i == n];
    }
}

int main() {
    freopen("tournament.in", "r", stdin);
    freopen("tournament.out", "w", stdout);
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    cin >> n;
    rep(i, 1, n) cin >> a[i];
    rep(i, 1, n) rep(j, i+1, n) {
	if(i != j) {
	    int inv = qpow((a[i]+a[j]) % mod, mod-2);
	    win[i][j] = 1ll * a[i] * inv % mod;
	    win[j][i] = 1ll * a[j] * inv % mod;
	}
    }

    rep(i, 1, n) {
	f[i][i][i] = 1;
	rep(j, 1, n) g[i][i][j] = win[j][i];
    }

    rep(i, 1, n) inv[i] = qpow(i, mod-2);

    if(n > 150) {
	sub2::solve();
	return 0;
    }
    rep(len, 2, n) {
	rep(l, 1, n) {
	    int sum = 0;
	    int r = l + len - 1;
	    if(r > n) break;
	    rep(i, l, r) {
		__int128 res = 0;
		rep(k, l, r-1) {
		    if(i <= k) {
			res += 1ll * f[l][k][i] * g[k+1][r][i];
		    } else {
			res += 1ll * g[l][k][i] * f[k+1][r][i];
		    }
		}
		f[l][r][i] = res * inv[r-l] % mod;
		sum += f[l][r][i];
		if(sum >= mod) sum -= mod;
	    }
	    rep(j, 1, n) {
		if(l <= j && j <= r) continue;
		__int128 res = 0;
		rep(i, l, r) {
		    res += 1ll * f[l][r][i] * win[j][i];
		}
		g[l][r][j] = res % mod;
	    }
	}
    }
    

    rep(i, 1, n) cout << f[1][n][i] << "\n";
    
    return 0;
}
    

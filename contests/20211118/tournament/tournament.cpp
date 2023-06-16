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
const int inv2 = (mod+1)>>1;

int n, a[N], win[N][N], cob[N][N], fac[N], ifac[N], inv[N];
int f[N][N];

int qpow(int x, ll p) {
    int res = 1, base = x;
    while(p) {
	if(p & 1) res = 1ll * res * base % mod;
	base = 1ll * base * base % mod;
	p >>= 1;
    }
    return res;
}

int main() {
    // freopen("tournament.in", "r", stdin);
    // freopen("tournament.out", "w", stdout);
    
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

    rep(i, 1, n) inv[i] = qpow(i, mod-2);
    fac[0] = ifac[0] = fac[1] = ifac[1] = 1;
    rep(i, 2, n) fac[i] = 1ll * fac[i-1] * i % mod;
    ifac[n] = qpow(fac[n], mod-2);
    per(i, 2, n-1) ifac[i] = 1ll * ifac[i+1] * (i+1) % mod;

    cob[0][0] = 1;
    rep(i, 1, n) {
	cob[i][0] = 1;
	rep(j, 1, i) {
	    cob[i][j] = cob[i-1][j] + cob[i-1][j-1];
	    if(cob[i][j] >= mod) cob[i][j] -= mod;
	}
    }


    
    auto calc = [&](int i, int j, int k) {
		    int ret = 0;
		    if(j == 0) ret = win[k][i];
		    else if(k == n+1) ret = win[j][i];
		    else ret = 1ll * inv2 * (win[k][i] + win[j][i]) % mod;
		    return ret;
		};

    rep(i, 1, n) f[i][i] = calc(i, i-1, i+1);
    rep(i, 1, n+1) f[i][i-1] = 1;
    rep(len, 2, n) {
	rep(l, 1, n) {
	    int r = l + len - 1;
	    if(r > n) break;

	    rep(k, l, r) {
		//	fprintf(stderr, "f[%d][%d] += k = %d, %d * %d * %d\n", l, r, k, f[l][k-1], f[k+1][r], calc(k, l-1, r+1));
		f[l][r] = (1ll * f[l][k-1] * f[k+1][r] % mod * calc(k, l-1, r+1) % mod
			   * cob[r-l][k-l] % mod
			   * (k!=1 && k!= n ? 1 : inv[r-l+1])
			   + f[l][r]) % mod;
	    }

//	    f[l][r] = 1ll * f[l][r] * ifac[r-l] % mod;
	}
    }
    /*
    rep(l, 1, n) rep(r, l, n) 
	    fprintf(stderr, "f[%d][%d] = %d\n", l, r, f[l][r]);
    */
    rep(i, 1, n) {
	cout << 1ll * f[1][i-1] * f[i+1][n]%mod * cob[n-1][i-1] % mod <<"\n";
    }
    
    return 0;
}
    

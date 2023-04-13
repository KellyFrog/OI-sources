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

const int mod = 998244353;
const int N = 5e3 + 5;
const int inv2 = (mod+1) / 2;
const double eps = 1e-6;

int f[N][N];
double g[N][N];
int n, m;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    cin >> n >> m;

    ++n;

    g[0][0] = f[0][0] = 1;

    rep(i, 1, m) {

	rep(j, 1, n) {
	    f[i][j] = (1ll * inv2 * f[i][j-1] + f[i-1][j-1]) % mod;
	    g[i][j] = (g[i][j-1]) / 2 + g[i-1][j-1];
	    if(j <= i) f[i][j] = g[i][j] = 1;
	}
	rep(j, 1, n-1) {
	    f[i][j] = 1ll * f[i][j] * inv2 % mod;
	    g[i][j] /= 2;
	}
    }
    
    rep(i, 1, m) cout << f[i][n] << "\n";
    rep(i, 1, m) cerr << g[i][n] - g[i-1][n] << "\n";
    
    return 0;
}
    

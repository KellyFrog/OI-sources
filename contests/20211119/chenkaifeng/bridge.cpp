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
const int N = 1e5 + 5;
const int inv2 = (mod+1)>>1;

int n, m;
int fac[N], ifac[N];

int qpow(int x, ll p) {
    int res = 1, base = x;
    while(p) {
	if(p & 1) res = 1ll * res * base % mod;
	base = 1ll * base * base % mod;
	p >>= 1;
    }
    return res;
}

int ans[N];

inline int cob(int n, int m) {
    return 1ll * fac[n] * ifac[m] % mod * ifac[n-m] % mod;
}

int main() {
    freopen("bridge.in", "r", stdin);
    freopen("bridge.out", "w", stdout);
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    cin >> n >> m;

    ifac[0] = fac[0] = ifac[1] = fac[1] = 1;
    rep(i, 2, n) fac[i] = 1ll * fac[i-1] * i % mod;
    ifac[n] = qpow(fac[n], mod-2);
    per(i, 2, n-1) ifac[i] = 1ll * ifac[i+1] * (i+1) % mod;
    
    ans[1] = qpow(inv2, n);
    rep(i, 2, n+1) {
	ans[i] = 1ll * ans[1] * cob(n, i-1) % mod;
    }
    rep(i, 2, n+1) {
	ans[i] += ans[i-1];
	if(ans[i] >= mod) ans[i] -= mod;
    }

    rep(i, 1, m) {
	cout << (i <= n ? ans[i] : 1) << "\n";
    }
    cout.flush();
    
    return 0;
}
    

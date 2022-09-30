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

const int mod = 1e9 + 7;
const int N = 55;

ll n;
int q;
vector<ll> prm, fac;
vector<int> val, f;
int inv[N];

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
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    cin >> n >> q;

    int nn = n;
    for(ll i = 2; i * i <= n; ++i) {
	if(nn % i == 0) {
	    prm.pb(i);
	    nn /= i;
	    while(nn % i == 0) nn /= i;
	}
    }
    if(nn != 1) prm.pb(nn);

    for(ll i = 1; i * i <= n; ++i) {
	if(n % i == 0) {
	    fac.pb(i);
	    if(i * i != n) fac.pb(n/i);
	}
    }

    sort(fac.begin(), fac.end());

    val.resize(fac.size());
    f.resize(fac.size());
    for(auto& x : val) cin >> x;

    rep(i, 1, 50) inv[i] = qpow(i, mod-2);

    auto find = [&](ll x) {
		    return lower_bound(fac.begin(), fac.end(), x) - fac.begin();
		};



    f[f.size()-1] = 1;
    
    for(int i = fac.size() - 1; i >= 0; --i) {
	int cnt = 0;
	for(int p : prm) if(fac[i] % p == 0) ++cnt;
	for(int p : prm) if(fac[i] % p == 0) {
		int pp = find(fac[i] / p);
		f[pp] = (1ll * f[i] * inv[cnt] + f[pp]) % mod;
	    }
    }

    int ans = 0;
    for(int i = 0; i < fac.size(); ++i) ans = (1ll * f[i] * val[i] + ans) % mod;

    cout << ans << "\n";

    --q;
    while(q--) {
	ll v, x;
	cin >> v >> x;
	int p = find(v);
	ans = (1ll * (x - val[p] + mod) * f[p] + ans) % mod;
	val[p] = x;
	cout << ans << "\n";
    }

    cout.flush();
    
    return 0;
}
    

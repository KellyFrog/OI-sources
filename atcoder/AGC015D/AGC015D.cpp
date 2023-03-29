// Problem: AT_agc015_d [AGC015D] A or...or B Problem
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_agc015_d
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Creaate Time: 2023/3/29
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

ll solve(ll a, ll b) {
	cerr << "solve(" << a << ", " << b << ")\n";
	per(i, 0, 60) {
		ll x = a & (1ll << i), y = b & (1ll << i);
		if(x != y) break;
		a ^= x, b ^= y;
	}
	cerr << a << " " << b << "\n";
	bool ok = 0, f = 0;
	ll ans = 0;
	per(i, 0, 60) {
		ll x = a & (1ll << i), y = b & (1ll << i);
		ok |= x && y;
		f |= x || y;
		cerr << i << " " << a << " " << b << " " << x << " " << y << " " << ok <<  "\n";
		if(!f) continue;
		if(y) continue;
		if(ok) {
			ans += (1ll << i);
		} else {
			if(x == 0) {
				ll a0 = (a >> i | 1) << i;
				assert(a0 <= b);
				ll t = a0 + (1ll << i) - 1;
				if(t <= b) ans += (1ll << i);
				else ans += solve(a0 & ((1ll << i-1) - 1), b & ((1ll << i-1) - 1));
			} else {
				if(i == 0) {
					ans += 1;
					break;
				}
				ans += solve(a & ((1ll << i-1) - 1), b & ((1ll << i-1) - 1));
				break;
			}
		}
	}
	return ans + b - a + 1;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	ll a, b; cin >> a >> b;
	per(i, 0, 7) cerr << (a >> i & 1); cerr << "\n";
	per(i, 0, 7) cerr << (b >> i & 1); cerr << "\n";
	cout << solve(a, b) << "\n";
	
	return 0;
}


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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	freopen("xor.in", "r", stdin);
	freopen("xor.out", "w", stdout);
	
	int t;
	// cin >> t;
	t = 1;
	while(t--) {
	
		ll n;
		cin >> n;
		
		if(n == 1 || n == 2) {
			cout << -1 << "\n";
			continue;
		}
		
		if(n % 4 == 1) {
			ll x = n + 3;
			if(__builtin_popcount(x) == 1) {
				if(n == 5) {
					cout << x+1 << "\n";
					cout << 6 << "\n" << 4 << "\n" << 2 << "\n" << 1 << "\n";
				} else {
					cout << x+1 << "\n";
					cout << 6 << "\n" << 4 << "\n" << 2 << "\n" << 1 << "\n";
				}
			} else if(__builtin_popcount(x) == 2) {
				ll a = x & (x - 1);
				ll b = x ^ a;
				cout << x << "\n";
				cout << 1 << "\n" << a << "\n" << b+1 << "\n";
				// cout << x + 1 << "\n";
				// cout << 2 << "\n" << 6 << "\n" << 1 << "\n" << 4 << "\n";
			} else {
				vector<ll> a;
				cout << x << "\n";
				per(i, 0, 60) if(x >> i & 1) {
					if(a.size() < 3) a.pb(1ll << i);
					else a[2] |= 1ll << i;
				}
				for(ll v : a) cout << v << "\n";
				
			}
		} else if(n % 4 == 2) {
			ll x = n + 2;
			if((x & (x-1)) == 0) {
				cout << n + 3 << "\n";
				cout << n + 1 << "\n" << 2 << "\n" << (2 ^ n) << "\n";
			} else {
				cout << n+2 << "\n";
				ll a = x & (x - 1);
				cout << a << "\n" << (x ^ a) << "\n";
			}
		} else if(n % 4 == 3) {
			cout << n << "\n";
		} else if(n % 4 == 0) {
			cout << n+1 << "\n";
			cout << 1 << "\n";
		}
	
	}
	
	cout.flush();
	
	return 0;
}

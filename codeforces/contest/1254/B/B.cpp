
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

const int N = 1e6 + 5;

int n, a[N];
ll b[N];

ll solve(ll d) {
	rep(i, 1, n) b[i] = a[i] % d;
	ll sum = 0;
	rep(i, 1, n-1) {
		sum += min(d - b[i], b[i]);
		b[i+1] = (b[i+1] + b[i]) % d;
	}
	return sum;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n;
	rep(i, 1, n) cin >> a[i];
	ll s = 0;
	rep(i ,1, n) s += a[i];
	ll s0 = s;
	vector<ll> prm;
	for(int i = 2; 1ll * i * i <= s0; ++i) {
		if(s % i == 0) {
			prm.pb(i);
			while(s % i == 0) s /= i;
		}
	}
	if(s != 1) prm.pb(s);
	ll ans = 1e18;
	for(auto x : prm) ans = min(ans, solve(x));
	cout << (ans == (ll)1e18 ? -1 : ans) << "\n";
	
	return 0;
}

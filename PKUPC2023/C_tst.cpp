#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define rep(i, s, t) for(int i = (s); i <= (t); ++i)
#define per(i, s, t) for(int i = (t); i >= (s); --i)
#define fi first
#define se second
#define mp make_pair
#define pb push_back

mt19937 mtrnd(chrono::steady_clock::now().time_since_epoch().count());

ll a[3];

void solve(int i, int j, ll t) {
	map<pair<ll, ll>, ll> v;
	ll k = 1;
	for(; k <= t; ++k) {
		int i0 = i, j0 = j;
		if(a[i0] > a[j0]) swap(i0, j0);
		ll x = a[i0];
		a[i0] += x, a[j0] -= x;
		if(v.count(mp(a[i], a[j]))) {
			ll T = k - v[mp(a[i], a[j])];
			ll tt = t - i;
			t -= tt / T * T;
			cerr << "get T = " << T << "\n";
			break;
		}
		v[mp(a[i], a[j])] = k;
	}
	for(; k <= t; ++k) {
		int i0 = i, j0 = j;
		if(a[i0] > a[j0]) swap(i0, j0);
		ll x = a[i0];
		a[i0] += x, a[j0] -= x;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	int t = 1000;
	while(t--) {
		ll m = (ll)3e13;
		a[0] = mtrnd() % m + 1;
		a[1] = mtrnd() % m + 1;
		a[2] = mtrnd() % m + 1;
		cerr << a[0] << " " << a[1] << " " << a[2] << "\n";
		solve(0, 1, (ll)1e18);
	}

	return 0;
}

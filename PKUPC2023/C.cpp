#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define rep(i, s, t) for(int i = (s); i <= (t); ++i)
#define per(i, s, t) for(int i = (t); i >= (s); --i)
#define fi first
#define se second
#define mp make_pair
#define pb push_back

ll a[3];

mt19937 mtrnd(0x1145);

int solve(int i, int j) {
	if(!a[i] || !a[j]) return 1;
	if(a[i] > a[j]) swap(i, j);
	int t = 0;
	while(a[i] <= a[j]) {
		ll x = a[i];
		a[i] += x, a[j] -= x;
		++t;
	}
	return t;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	cin >> a[0] >> a[1] >> a[2];
	int t = 200;
	cout << t << "\n";
	while(t--) {
		int op = mtrnd() % 3 + 1;
		if(op == 1) cout << 1 << " " << solve(0, 1) << "\n";
		if(op == 2) cout << 2 << " " << solve(2, 1) << "\n";
		if(op == 3) cout << 3 << " " << solve(0, 2) << "\n";
	}

	return 0;
}

dfsahgiure

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define rep(i, s, t) for(int i = (s); i <= (t); ++i)
#define per(i, s, t) for(int i = (t); i >= (s); --i)
#define fi first
#define se second
#define mp make_pair
#define pb push_back

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

int main(int argc, char** argv) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	assert(argc == 3);
	ifstream inf(argv[1]);
	ifstream ouf(argv[2]);
	inf >> a[0] >> a[1] >> a[2];
	cerr << a[0] << " " << a[1] << " " << a[2] << "\n";
	int t; ouf >> t;
	assert(1 <= t && t <= 200);
	ll t0 = -1;
	rep(i, 1, t) {
		ll op, x; ouf >> op >> x;
		if(i == 1) t0 = x;
		if(op == 1) solve(0, 1, x);
		else if(op == 2) solve(1, 2, x);
		else solve(0, 2, x);
	}
	if(!a[0] || !a[1] || !a[2]) {
		cerr << "ok " << t0 << " " << a[0] << " " << a[1] << " " << a[2] << "\n";
	} else {
		cerr << "wa " << t0 << " " << a[0] << " " << a[1] << " " << a[2] << "\n";
		return 1;
	}

	return 0;
}

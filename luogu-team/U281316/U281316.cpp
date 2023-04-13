// Problem: AT_agc011_f [AGC011F] Train Service Planning
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/U281316
// Memory Limit: 256 MB
// Time Limit: 2000 ms
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

ll n;
int b;
ll ans1 = 0, ans2 = -1;

void solve(int s) {
	vector<int> v1, v2;
	rep(i, 0, b-1) {
		if(s >> i & 1) v1.pb(i);
		else v2.pb(i);
	}
	map<ll, pair<ll, ll>> v;
	auto upd = [&](ll x) {
		if(x%n == 0) {
			if(x > ans1) ans2 = ans1, ans1 = x;
			else if(x != ans1 && x > ans2) ans2 = x;
		}
	};
	do {
		ll x = 0;
		for(int y : v1) {
			x = b * x + y;
			upd(x);
		}
		auto e = v[x%n];
		if(x > e.fi) e.se = e.fi, e.fi = x;
		else if(x != e.fi && x > e.se) e.se = x;
		v[x%n] = e;
	} while(next_permutation(v1.begin(), v1.end()));
	int h = v1.size();
	ll p = 1;
	while(h--) p *= b;
	do {
		ll x = 0;
		for(int y : v2) {
			x = b * x + y;
			auto e = v[(n-x*p%n)%n];
			ll x1 = x * p + e.fi;
			ll x2 = x * p + e.se;
			if(e.fi) upd(x1);
			if(e.se) upd(x2);

		}
	} while(next_permutation(v2.begin(), v2.end()));
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> b;
	rep(s, 1, (1<<b)-1) if(__builtin_popcount(s) <= 6 && b-__builtin_popcount(s) <= 6) solve(s);
	cerr << ans1 << " " << ans2 << "\n";
	cout << ans2 << "\n";

	return 0;
}


// Problem: B - GCD Subtraction
// Contest: AtCoder - AtCoder Regular Contest 159
// URL: https://atcoder.jp/contests/arc159/tasks/arc159_b
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Create Time: 2023-04-12 19:33:04
// Input/Output: stdin/stdout
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

ll solve(ll x, ll y) {
	if(x == 0) return 0;
	ll g = __gcd(x, y);
	x /= g, y /= g;
	ll mx = 0;
	auto upd = [&](ll v) {
		if(v == 1) return;
		if(v >= x) return;
		ll z = x / v * v;
		mx = max(mx, z);
	};
	for(ll i = 1; i * i <= y; ++i) {
		if(y % i == 0) upd(i), upd(y/i);
	}
	return solve(mx, y) + x - mx;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	ll a, b; cin >> a >> b;
	if(a < b) swap(a, b);
	cout << solve(b, a-b) << "\n";
	
	return 0;
}

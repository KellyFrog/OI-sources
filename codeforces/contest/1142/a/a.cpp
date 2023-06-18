/*
 * Author: ChenKaifeng@codeforces
 * Create Time: 2023.06.17, 21:08 (UTC +8)
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

const int N = 1e5 + 5;

int n, k;
int a, b;
ll mi = LONG_LONG_MAX, mx = 0;

void solve(int x, int y) {
	rep(i, 1, n) {
		ll d = 1ll * i * k + y - x;
		if(d != 0) {
			ll g = __gcd(1ll * n * k, d);
			ll v = 1ll * n * k  / g;
			mi = min(mi, v);
			mx = max(mx, v);
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> k >> a >> b;
	
	solve(a, b);
	solve(-a, b);
	solve(a, -b);
	solve(-a, -b);

	cout << mi << " " << mx << "\n";
	
	return 0;
}

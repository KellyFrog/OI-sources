/*
 * Author: zhengguoge@codeforces
 * Create Time: 2023.06.18, 16:05:04 (UTC +8)
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

void solve() {
	int n;
	cin >> n;
	int c1 = 0, c2 = 0;
	rep(i, 1, n) {
		int x; cin >> x;
		if(x == 1) ++c1;
		else ++c2;
	}
	int t = max(0, (n+1) / 2 - c1);
	int ans = t;
	c1 += t, c2 -= t;
	if(c2 & 1) ++ans;
	cout << ans << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	int t; cin >> t;
	while(t--) solve();
	
	return 0;
}

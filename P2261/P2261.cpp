// Problem: P2261 [CQOI2007]余数求和
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P2261
// Memory Limit: 125 MB
// Time Limit: 1000 ms
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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	int n, k;
	cin >> n >> k;
	ll ans = 1ll * n * k;
	for(int l = 1, r; l <= n && l <= k; l = r + 1) {
		r = min(n, k / (k / l));
		ans -= 1ll * (k / l) * (1ll * (l + r) * (r - l + 1) / 2);
	}
	cout << ans << "\n";
	
	return 0;
}

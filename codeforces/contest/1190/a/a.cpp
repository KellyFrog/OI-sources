/*
 * Author: ChenKaifeng@codeforces
 * Create Time: 2023.06.23, 13:15:03 (UTC +8)
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

ll n, k;
int m;
ll a[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> m >> k;
	rep(i, 1, m) cin >> a[i];
	int ans = 0;
	for(int i = 1; i <= m; ) {
		ll p = (a[i] - (i-1) - 1) % k + 1;
		int j = i;
		while(j <= m && a[j] - a[i] <= k - p) ++j;
		i = j;
		++ans;
	}
	cout << ans << "\n";

	return 0;
}

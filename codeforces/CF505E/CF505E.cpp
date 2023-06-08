// Problem: Mr. Kitayuta vs. Bamboos
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF505E
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// Create Time: 2023-06-06 19:47:15
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

const int N = 1e5 + 5;

int n, m, k, p;
int a[N], b[N];
ll c[N], d[N];

bool check(ll lim) {
	rep(i, 1, n) d[i] = max(0ll, c[i] - lim);

}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> m >> k >> p;
	rep(i, 1, n) cin >> a[i] >> b[i], c[i] = a[i] + 1ll * (m-1) * b[i];

	ll L = 0, R = 1e18;
	ll res = -1;
	while(L <= R) {
		ll mid = L + R >> 1;
		if(check(mid)) res = mid, R = mid - 1;
		else L = mid + 1;
	}

	cout << res << "\n";
	
	return 0;
}


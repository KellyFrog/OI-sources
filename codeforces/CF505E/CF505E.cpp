// Problem: CF505E Mr. Kitayuta vs. Bamboos
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF505E
// Memory Limit: 250 MB
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

const int N = 1e5 + 5;

int n, m, k, p;
ll a[N], b[N], t[N], c[N], d[N];

ll gett(int i) {
	return b[i] == 0 ? -1 : t[i] - c[i] / b[i];
}

bool check(ll lim) {
	rep(i, 1, n) c[i] = lim;
	rep(i, 1, n) t[i] = m+1;
	rep(i, 1, n) d[i] = 0;
	priority_queue<pair<ll, int>> pq;
	rep(i, 1, n) pq.emplace(gett(i), i);
	per(i, 1, m) {
		int k0 = k;
		while(k0--) {
			int j = pq.top().se; pq.pop();
			c[j] -= (t[j] - i) * b[j];
			if(c[j] < 0) return 0;
			c[j] += p;
			++d[j];
			t[j] = i;
			pq.emplace(gett(j), j);
		}
	}
	rep(i, 1, n) c[i] -= (t[i] - 1) * b[i];
	ll cc = 0;
	rep(i, 1, n) {
		if(c[i] < a[i]) cc -= (a[i] - c[i] + p - 1) / p;
		else cc += min(d[i], (c[i] - a[i]) / p);
	}
	return cc >= 0;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> m >> k >> p;
	rep(i, 1, n) cin >> a[i] >> b[i];

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

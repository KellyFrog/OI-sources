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

const int N = 3e5 + 5;
const int M = 1e7 + 5;

int n;
ll a[N];
int vis[M];
int id;

void solve(int l, int r) {
	if(l == r) {
		if(a[l] <= 1e7) vis[a[l]] = id;
		return;
	}
	int mid = l + r >> 1;
	vector<int> v1, v2;
	ll x = a[mid];
	v1.pb(x);
	per(i, l, mid-1) {
		ll g = __gcd(x, a[i]);
		if(g == a[i]) continue;
		x = 1ll * x * a[i] / g;
		if(x > 1e7) break;
		v1.pb(x);
	}
	x = a[mid+1];
	v2.pb(x);
	rep(i, mid+1, r) {
		ll g = __gcd(x, a[i]);
		if(g == a[i]) continue;
		x = 1ll * x * a[i] / g;
		if(x > 1e7) break;
		v2.pb(x);
	}
	for(int x : v1) for(int y : v2) {
		int g = __gcd(x, y);
		ll v = 1ll * x * y / g;
		if(v <= 1e7) vis[v] = id;
	}
	solve(l, mid);
	solve(mid + 1, r);
}

void solve(int id) {
	::id = id;
	cin >> n;
	rep(i, 1, n) cin >> a[i];
	solve(1, n);
	for(int i = 1; ; ++i) if(vis[i] != id) {
		cout << i << "\n";
		return;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	int t; cin >> t;
	rep(i, 1, t) solve(i);
	
	return 0;
}

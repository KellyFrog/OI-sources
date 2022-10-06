// Problem: P1484 种树
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P1484
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

const int N = 5e5 + 5;
const ll inf = 0x3f3f3f3f3f3f3f3f;

struct T {
	ll val;
	int cnt;
};

bool operator < (const T& x, const T& y) {
	return x.val == y.val ? x.cnt > y.cnt : x.val < y.val;
}

T operator + (const T& x, const T& y) {
	return {x.val + y.val, x.cnt + y.cnt};
}

int n, k;
T f[N][2];
int a[N];

T calc(ll k) {
	f[0][0] = {0, 0};
	f[0][1] = {-inf, 0};
	rep(i, 1, n) {
		f[i][0] = max(f[i-1][0], f[i-1][1]);
		f[i][1] = f[i-1][0] + (T){a[i] - k, 1};
	}
	return max(f[n][0], f[n][1]);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> k;
	rep(i, 1, n) cin >> a[i];
	
	auto [val0, cnt0] = calc(0);
	
	if(cnt0 <= k) {
		cout << val0 << "\n";
		return 0;
	}
	
	ll L = -1e18, R = 1e18, res = 0;

	while(L <= R) {
		ll mid = L + R >> 1;
		auto [val, cnt] = calc(mid);
		if(cnt < k) R = mid - 1, res = val + 1ll * k * mid;
		else L = mid + 1;
	}

	cout << res << "\n";

	return 0;
}
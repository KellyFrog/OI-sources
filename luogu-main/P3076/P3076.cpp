// Problem: P3076 [USACO13FEB]Taxi G
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3076
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

const int N = 2e5 + 5;

int n, m;
int a[N], b[N], d1[N], d2[N], c[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> m;
	rep(i, 1, n) cin >> a[i] >> b[i];
	++n;
	a[n] = m, b[n] = 0;
	rep(i, 1, n) c[i] = a[i], c[i+n] = b[i];
	sort(c + 1, c + 2*n + 1 + 1);
	int k = unique(c + 1, c + 2*n+1 + 1) - c - 1;
	rep(i, 1, n) {
		a[i] = lower_bound(c + 1, c + k + 1, a[i]) - c;
		b[i] = lower_bound(c + 1, c + k + 1, b[i]) - c;
	}
	rep(i, 1, n) {
		if(a[i] < b[i]) ++d1[a[i]+1], --d1[b[i]+1];
		else ++d2[b[i]+1], --d2[a[i]+1];
	}
	rep(i, 1, k) d1[i] += d1[i-1], d2[i] += d2[i-1];
	ll ans = 0;
	rep(i, 1, k) {
		ans += 2ll * max(d1[i], d2[i]) * (c[i] - c[i-1]);
	}
	cout << ans - m << "\n";
	
	return 0;
}

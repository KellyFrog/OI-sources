// Problem: CF449D Jzzhu and Numbers
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF449D
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

const int N = 1 << 20 | 5;
const int P = 1e9 + 7;

int n, a[N], pw[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n;

	rep(i, 1, n) {
		int x; cin >> x; ++a[x];
	}
	pw[0] = 1;
	rep(i, 1, n) pw[i] = 2 * pw[i-1] % P;
	int m = 1 << 20;
	rep(i, 1, 20) rep(s, 0, m-1) if(s >> i-1 & 1) a[s ^ (1 << i-1)] += a[s];
	int ans = 0;
	rep(s, 0, m) {
		ans = (ans + ((__builtin_popcount(s) & 1) ? -1 : 1) * (pw[a[s]] - 1)) % P;
	}
	cout << (ans + P) % P << "\n";

	return 0;
}

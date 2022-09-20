// Problem: AT2061 [AGC005C] Tree Restoring
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT2061
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

const int N = 105;

int n, a[N], cnt[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n;
	rep(i, 1, n) cin >> a[i];
	int mx = 0;
	rep(i, 1, n) mx = max(mx, a[i]);
	if(mx == 1) {
		if(n == 2) {
			cout << "Possible" << "\n";
			return 0;
		} else {
			cout << "Impossible" << "\n";
			return 0;
		}
	}
	rep(i, 1, n) ++cnt[a[i]];
	rep(i, 1, n) if(2 * i < mx && cnt[i]) {
		cout << "Impossible" << "\n";
		return 0;
	}
	if(mx % 2 == 0) {
		if(cnt[mx/2] != 1) {
			cout << "Impossible" << "\n";
			return 0;
		}
		rep(i, mx/2+1, mx) if(cnt[i] < 2) {
			cout << "Impossible" << "\n";
			return 0;
		}
	} else {
		if(cnt[mx/2+1] != 2) {
			cout << "Impossible" << "\n";
			return 0;
		}
		rep(i, mx/2+1, mx) if(cnt[i] < 2) {
			cout << "Impossible" << "\n";
			return 0;
		}
	}
	cout << "Possible" << "\n";
	
	return 0;
}

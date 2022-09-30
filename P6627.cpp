// Problem: P6627 [省选联考 2020 B 卷] 幸运数字
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6627
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// Create Time: 2022-07-12 11:12:06
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

const int N = 1e6 + 5;

int n, m;
int a[N], op[N], x[N], y[N], z[N];
int pre[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n;
	a[++m] = -1e9-1;
	a[++m] = 1e9+1;
	rep(i, 1, n) {
		cin >> op[i];
		if(op[i] == 1) {
			cin >> x[i] >> y[i] >> z[i];
			a[++m] = x[i]-1;
			a[++m] = x[i];
			a[++m] = y[i];
			a[++m] = y[i]+1;
		} else {
			cin >> x[i] >> z[i];
			a[++m] = x[i]-1;
			a[++m] = x[i];
			a[++m] = x[i]+1;
		}
	}
	sort(a + 1, a + m + 1);
	m = unique(a + 1, a + m + 1) - a - 1;
	int sum = 0, ans = 0, ansp = -1e9-10;
	rep(i, 1, n) {
		if(op[i] == 1) {
			int l = lower_bound(a + 1, a + m + 1, x[i]) - a;
			int r = lower_bound(a + 1, a + m + 1, y[i]+1) - a;
			pre[l] ^= z[i];
			pre[r] ^= z[i];
		} else if(op[i] == 2) {
			int l = lower_bound(a + 1, a + m + 1, x[i]) - a;
			int r = lower_bound(a + 1, a + m + 1, x[i]+1) - a;
			pre[l] ^= z[i];
			pre[r] ^= z[i];
		} else {
			int l = lower_bound(a + 1, a + m + 1, x[i]) - a;
			int r = lower_bound(a + 1, a + m + 1, x[i]+1) - a;
			pre[l] ^= z[i];
			pre[r] ^= z[i];
			pre[1] ^= z[i];
		}
	}
	rep(i, 1, m) pre[i] ^= pre[i-1];
	per(i, 1, m) {
		auto get = [&]() {
			int l = a[i], r = a[i+1]-1;
			int res = -1e9-10;
			if(l <= 0 && 0 <= r) res = 0;
			else if(0 < l) res = l;
			else res = r;
			return res;
		};
		if(pre[i] > ans) {
			ans = pre[i];
			ansp = get();
		} else if(pre[i] == ans) {
			int r = get();
			if(abs(r) < ansp) ansp = r;
			else if(abs(r) == ansp && r > ansp) ansp = r;
		}
	}
	cout << ans << " " << ansp << "\n";
	
	return 0;
}

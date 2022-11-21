// Problem: AT_agc006_e [AGC006E] Rotate 3x3
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_agc006_e
// Memory Limit: 256 MB
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

int n, a[3][N], b[N], t[N];

inline int lowbit(int x) { return x & (-x); }
inline void add(int x, int v) { for(int x0 = x; x0 <= n; x0 += lowbit(x0)) t[x0] += v; }
inline int query(int x) { int ret = 0; for(int x0 = x; x0; x0 -= lowbit(x0)) ret += t[x0]; return ret; }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n;
	rep(j, 0, 2) rep(i, 1, n) cin >> a[j][i];
	rep(i, 1, n) {
		if(abs(a[1][i] - a[0][i]) != 1 || abs(a[1][i] - a[2][i]) != 1) {
			cout << "No" << "\n";
			return 0;
		} else {
			b[i] = (a[1][i] - a[0][i]) * (a[1][i] / 3 + 1);
			if((b[i] & 1) != (i & 1)) {
				cout << "No" << "\n";
				return 0;
			}
		}
	}
	ll x = 0, y = 0, ax = 0, ay = 0;
	rep(i, 1, n) {
		if(i & 1) {
			ax += b[i] < 0;
			x += query(n) - query(abs(b[i]));
			add(abs(b[i]), 1);
		}
	}
	memset(t, 0, sizeof t);
	rep(i, 1, n) {
		if(!(i & 1)) {
			ay += b[i] < 0;
			y += query(n) - query(abs(b[i]));
			add(abs(b[i]), 1);
		}
	}
	if((x & 1) == (ay & 1) && (y & 1) == (ax & 1)) {
		cout << "Yes" << "\n";
	} else {
		cout << "No" << "\n";
	}

	return 0;
}

// Problem: T275824 Magenta Potion
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T275824?contestId=85210
// Memory Limit: 128 MB
// Time Limit: 1000 ms
// Create Time: 2022-10-03 14:02:38
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

const int N = 2e5 + 5;

int n, q;
int a[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> q;
	rep(i, 1, n) cin >> a[i];
	while(q--) {
		int op; cin >> op;
		if(op == 1) {
			int x, y; cin >> x >> y;
			a[x] = y;
		} else {
			int l, r; cin >> l >> r;
			if(r - l + 1 > 70) cout << "Too large" << "\n";
			else {
				auto calc = [&](int l, int r) {
					ll res = 1, cur = 1;
					rep(i, l, r) {
						cur = cur * a[i];
						if(cur < -(1 << 30)) cur = -(1 << 30 | 5);
						if(cur > (1 << 30)) cur = 1 << 30 | 5;
						res = max(res, cur);
					}
					return res;
				};

				ll res = 1;
				rep(i, l, r) res = max(res, calc(i, r));
				if(res > (1 << 30)) cout << "Too large" << "\n";
				else cout << res << "\n";
			}
		}
	}
	return 0;
}

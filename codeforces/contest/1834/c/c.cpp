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

const int N = 1e5 + 5;

int n;
char s[N], t[N];

void solve() {
	cin >> n;
	cin >> (s+1) >> (t+1);
	int c = 0, d = 0;
	rep(i, 1, n) c += s[i] != t[i];
	rep(i, 1, n) d += s[i] != t[n-i+1];
	if(c == 0) {
		cout << 0 << "\n";
		return;
	}
	rep(i, 1, 2*n) {
		if((i >> 1) & 1) {
			if((i + 1 >> 1) >= d) {
				cout << i << "\n";
					return;
			}
		} else {
			if((i + 1 >> 1) >= c) {
				cout << i << "\n";
				return;
			}
		}
	}
	
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	int t; cin >> t;
	while(t--) solve();
	
	return 0;
}

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

const int N = 3e3 + 5;

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
		int op, l, r; cin >> op >> l >> r;
		if(op == 1) {
			rep(i, l, r-1) a[i] = max(a[i], a[i+1]);
		} else {
			int mx = 0;
			ll ans = 0;
			rep(i, l, r) {
				if(a[i] > mx) {
					mx = a[i], ans += a[i];
				}
			}
			cout << ans << "\n";
		}
	}
	
	return 0;
}

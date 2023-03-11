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

mt19937_64 mtrnd(chrono::steady_clock::now().time_since_epoch().count());


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cout << 10 << '\n';
	rep(t, 1, 10) {
		int n = 10, m = 5;
		cout << n << "\n";
		rep(i, 2, n) cout << i << " " << mtrnd() % (i-1) + 1 << " " << mtrnd() % 10 + 1 << "\n";
		cout << m << '\n';
		while(m--) {
			int x, y;
			do { x = mtrnd() % n + 1, y = mtrnd() % n + 1; } while(x == y);
			cout << x << " " << y << " " << mtrnd() % 10 + 1 << "\n";

		}
	}

	return 0;
}

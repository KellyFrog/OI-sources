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

mt19937 mtrnd(chrono::steady_clock::now().time_since_epoch().count());

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	int n = 15, m = 10;
	cout << n << " " << m << "\n";
	rep(i, 2, n) {
		cout << mtrnd() % (i-1) + 1 << " " << i << "\n";
	}
	rep(i, 1, m) {
		int x = mtrnd() % n + 1, y = mtrnd() % n + 1, w = mtrnd() % 10 + 1;
		cout << x << " " << y << " " << w << "\n";
	}
	
	return 0;
}

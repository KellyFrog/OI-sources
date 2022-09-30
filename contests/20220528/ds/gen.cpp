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

mt19937_64 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	int n = 1e5, q = 1e5, b = mtrnd() % 998244352 + 1;
	cout << n << " " << b << " " << q << "\n";
	rep(i, 1, n) cout << mtrnd() % n + 1 << " \n"[i == n];
	while(q--) {
		int l, r, x, y;
		l = mtrnd() % n + 1;
		r = mtrnd() % n + 1;
		x = mtrnd() % n + 1;
		y = mtrnd() % n + 1;
		if(l > r) swap(l, r);
		if(x > y) swap(x, y);
		cout << l << " " << r << " " << x << " " << y << "\n";
	}
	
	return 0;
}
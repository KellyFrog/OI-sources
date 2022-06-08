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

mt19937 mtrnd(chrono::steady_clock().now().time_since_epoch().count());

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	int n = 5, q = 10;
	cout << n << " " << q << "\n";
	rep(i, 1, n) cout << mtrnd()%10; cout << "\n";
	while(q--) {
		int op = mtrnd() % 2 + 1;
		if(op == 1) {
			int l = mtrnd() % n + 1;
			int r = mtrnd() % n + 1;
			if(l > r) swap(l, r);
			cout << op << " " << l << " " << r << "\n";
		} else {
			int l = mtrnd() % n + 1, r = mtrnd() % n + 1;
			int x = mtrnd() % (min(n-l, n-r)+1);
			cout << op << " " << l << " " << r << " " << x << "\n";
		}
	}
	
	return 0;
}
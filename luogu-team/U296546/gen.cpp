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

	int n = mtrnd() % 6 + 1, m = mtrnd() % 6 + 1, q = 300;
	cout << n << " " << m << " " << q << "\n";
	rep(i, 1, m) {
		cout << mtrnd() % n + 1 << " " << mtrnd() % n + 1 << " " << 1 << "\n";
	}
	
	return 0;
}

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

int a[5000000];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	int t = 1;
	cout << t << "\n";
	while(t--) {
		int n = 2;
		int m = 1e6;
		int k = 2 * n - 1;
		cout << n << " " << 2 * m << " " << k << "\n";
		rep(i, 1, m) a[i] = a[i+m] = mtrnd() % k + 1;
		shuffle(a + 1, a + 2*m + 1, mtrnd);
		rep(i, 1, 2*m) cout << a[i] << " \n"[i == 2*m];
	}
	
	return 0;
}

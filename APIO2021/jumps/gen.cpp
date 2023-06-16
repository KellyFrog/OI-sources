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

	int n = mtrnd() % 6 + 4;
	int q = n * n;
	cout << n << " " << q << "\n";
	vector<int> a(n);
	rep(i, 1, n) a[i-1] = i;
	shuffle(a.begin(), a.end(), mtrnd);
	for(int x : a) cout << x << " "; cout << "\n";
	while(q--) {
		int a, b, c, d;
		do {
			a = mtrnd() % n;
			b = mtrnd() % n;
			c = mtrnd() % n;
			d = mtrnd() % n;
		} while(!(a < b && b < c && c < d));
		cout << a << " " << b << " " << c << " " << d << "\n";
	}
	
	return 0;
}

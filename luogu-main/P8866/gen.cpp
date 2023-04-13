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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	mt19937 mtrnd(chrono::steady_clock::now().time_since_epoch().count());

	int t = 10;
	cout << t << "\n";
	while(t--) {
		int n = mtrnd() % 5 + 1;
		int k = 2 * n - 1;
		vector<int> v;
		rep(i, 1, 10) {
			int x = mtrnd() % k + 1;
			v.pb(x), v.pb(x);
		}
		shuffle(v.begin(), v.end(), mtrnd);
		cout << n << " " << v.size() << " " << k << "\n";
		for(auto x : v) cout << x << " "; cout << "\n";
	}

	return 0;
}

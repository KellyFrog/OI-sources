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
	int n = mtrnd() % 10 + 1;
	cout << n << "\n";
	rep(i, 1, n) cout << mtrnd() % 1000 + 1 << "\n";
	
	return 0;
}

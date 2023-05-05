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

set<unsigned long long> s;
mt19937_64 mtrnd(chrono::steady_clock::now().time_since_epoch().count());

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	unsigned long long x = mtrnd(), y = mtrnd(), z = mtrnd();
	
	set<unsigned long long> s = {
		4688917757846091486ull,
		8002816246663122031ull,
		10559652277640766752ull,
		13589256659382263697ull,
		15247229107491296254ull,
		18267969209591441743ull
	};
	cout << s.count(4688917757846091486ull) << "\n";

	for(auto x : s) cout << x << "\n";
	return 0;
}

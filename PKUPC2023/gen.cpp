#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define rep(i, s, t) for(int i = (s); i <= (t); ++i)
#define per(i, s, t) for(int i = (t); i >= (s); --i)
#define fi first
#define se second
#define mp make_pair
#define pb push_back

mt19937_64 mtrnd(chrono::steady_clock::now().time_since_epoch().count());

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	ll m = (ll)1e7;
	cout << mtrnd() % m + 1 << " " << mtrnd() % m + 1 << " " << mtrnd() % m + 1 << "\n";

	return 0;
}

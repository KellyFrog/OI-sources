#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define rep(i, s, t) for(int i = (s); i <= (t); ++i)
#define per(i, s, t) for(int i = (t); i >= (s); --i)
#define fi first
#define se second
#define mp make_pair
#define pb push_back

const int N = 2e5 + 5;

int n, pos;
string s[N], t;
ll a[N];

bool check(ll x) {
	ll y = a[pos] + x;
	ll c = 0;
	rep(i, 1, n) if(i != pos) c += max(0ll, a[i] - (y-1));
	return c <= x;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	cin >> n;
	cin >> t;
	rep(i, 1, n) cin >> s[i] >> a[i];
	rep(i, 1, n) if(s[i] == t) pos = i;
	ll L = 0, R = 1e18;
	ll res = -1;
	while(L <= R) {
		ll mid = L + R >> 1;
		if(check(mid)) res = mid, R = mid - 1;
		else L = mid + 1;
	}
	cout << res << "\n";

	return 0;
}

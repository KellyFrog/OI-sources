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
const int M = sqrt(N) + 5;

int n, m;
vector<vector<ll>> a, s1, s2;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	cin >> n >> m;
	if(n <= m) {
		a = vector<vector<ll>>(n+1, vector<ll>(m+1));
		rep(i, 1, n) rep(j, 1, m) cin >> a[i][j];
	} else {
		a = vector<vector<ll>>(m+1, vector<ll>(n+1));
		rep(i, 1, n) rep(j, 1, m) cin >> a[j][i];
		swap(n, m);
	}
	s1 = s2 = a;
	rep(i, 1, n) rep(j, 1, m) s1[i][j] += s1[i][j-1];
	rep(i, 1, n) rep(j, 1, m) s2[i][j] += s2[i-1][j];
	ll ans = -1e18;
	rep(i, 1, n) rep(j, 1, i-1) {
		ll mx = -1e18;
		rep(k, 1, m) {
			ans = max(ans, mx + s1[i][k] + s1[j][k] + s2[i-1][k] - s2[j][k]);
			mx = max(mx, -s1[i][k-1] - s1[j][k-1] + s2[i-1][k] - s2[j][k]);
		}
	}
	cout << ans << "\n";

	return 0;
}

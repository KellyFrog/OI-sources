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

const int N = 105;

int n, m, k;
char s[N][N], t[N][N];
char id[N] = " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

void solve() {
	cin >> n >> m >> k;
	int c = 0;
	rep(i ,1, n) rep(j, 1, m) {
		cin >> s[i][j];
		c += s[i][j] == 'R';
	}
	int d = c / k, e = c % k;
	vector<pair<int, int>> v;
	rep(i, 1, n) {
		if(i & 1) rep(j ,1, m) v.emplace_back(i, j);
		else per(j, 1, m) v.emplace_back(i, j);
	}
	int pos = 0;
	auto solve = [&](int k, char c) {
		int sum = 0;
		while(sum < k) {
			auto [i, j] = v[pos];
			t[i][j] = c;
			sum += s[i][j] == 'R';
			++pos;
		}
	};
	rep(i, 1, e) solve(d+1, id[i]);
	rep(i, e+1, k) solve(d, id[i]);
	rep(i, pos, v.size()-1) {
		auto [i1, j1] = v[i];
		auto [i0, j0] = v[i-1];
		t[i1][j1] = t[i0][j0];
	}
	rep(i, 1, n) {
		rep(j, 1, m) cout << t[i][j];
		cout << "\n";
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	int t; cin >> t;
	while(t--) solve();
	
	return 0;
}

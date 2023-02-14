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

const int N = 1e3 + 5;

int n;
char s[N];

int solve(int l, int r) {
	vector<int> v;
	rep(i, l, r) {
		if(s[i] == 'G') v.pb(i);
	}
	if(v.size() % 2 == 1 && (r-l+1) % 2 == 0) return -1;
	int res = 0;
	for(int i = 0; i < v.size(); ++i) {
		res += abs((r-l+1)+1-v[i]-v[v.size()-i-1]+2*(l-1));
	}
	return res/2;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> (s+1);
	n = strlen(s+1);
	int ans = 0;
	rep(i, 1, n) rep(j, 1, n) {
		if(i > j) cout << 0 << " \n"[j == n];
		else {
			int res = solve(i, j);
			ans += res;
			cout << res << " \n"[j == n];
		}
	}
	cout << ans << "\n";
	
	return 0;
}

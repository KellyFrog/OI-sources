/*
   /*
 * Author: ChenKaifeng@codeforces
 * Create Time: 2023.06.23, 13:15:03 (UTC +8)
 */
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

const int N = 4e5 + 5;
const long double eps = 1e-7;
const long double pi = acos(-1);

int n, k;
int a[N], b[N], pos[N], f[20][N];
long double dis[N];
long double l[N], r[N];

bool check(long double d) {
	vector<long double> v;
	rep(i, 1, n) {
		long double theta = atan2(b[i], a[i]);
		long double delta = acos(d / dis[i]);
		l[i] = theta - delta;
		r[i] = theta + delta;
		if(l[i] < 0) {
			l[i] += 2 * pi;
			r[i] += 2 * pi;
		}
		v.pb(l[i]);
		v.pb(l[i] + 2 * pi);
	}
	sort(v.begin(), v.end());
	vector<pair<int, int>> ps;
	auto getpos = [&](long double theta) { return upper_bound(v.begin(), v.end(), theta) - v.begin(); };
	int m = v.size();
	rep(i, 0, m) pos[i] = m+1;
	rep(i, 1, n) {
		int l1 = getpos(l[i]), l2 = getpos(l[i] + 2 * pi);
		int r1 = getpos(r[i]), r2 = getpos(r[i] + 2 * pi);
		pos[l1] = min(pos[l1], r1);
		pos[l2] = min(pos[l2], r2);
		ps.emplace_back(l1, l2);
	}
	per(i, 0, m-1) pos[i] = min(pos[i], pos[i+1]);
	rep(i, 0, m) f[0][i] = pos[i+1];
	rep(j, 1, 19) rep(i, 0, m) if(f[j-1][i]) f[j][i] = f[j-1][f[j-1][i]];
	auto solve = [&](int s, int t) {
		int res = 1;
		per(i, 0, 19) if(f[i][s] && f[i][s] < t) res += (1 << i), s = f[i][s];
		return res;
	};
	for(auto [s, t] : ps) if(solve(s, t) <= k) return 1;
	return 0;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15);
	cerr << fixed << setprecision(15);

	cin >> n >> k;
	rep(i, 1, n) cin >> a[i] >> b[i];
	rep(i, 1, n) dis[i] = sqrt(1ll * a[i] * a[i] + 1ll * b[i] * b[i]);
	long double L = 0, R = *min_element(dis + 1, dis + n + 1);
	long double res = 0;
	int t = 45;
	while(t-- && fabs(R - L) > eps) {
		long double mid = (L + R) / 2;
		if(check(mid)) L = mid, res = mid;
		else R = mid;
	}
	cout << res << "\n";

	return 0;
}




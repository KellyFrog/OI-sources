/*
 * Author: ChenKaifeng@codeforces
 * Create Time: 2023.06.17, 21:08:$%s$ (UTC +8)
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

const int N = 1e6 + 5;

int n;
pair<ll, ll> p[N];
int que[N], ph = 1, pt = 0;

inline long double slope(int i, int j) {
	return (long double)(p[i].se - p[j].se) / (p[i].fi - p[j].fi);
}

inline bool comp(int i, int j, int k) {
	return (p[i].se - p[j].se) * (p[i].fi - p[k].fi) >= (p[i].se - p[k].se) * (p[i].fi - p[j].fi);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15);
	cerr << fixed << setprecision(15);

	cin >> n;
	rep(i, 1, n) {
		ll x, y; cin >> x >> y;
		p[i] = mp(x, -y + x * x);
	}
	sort(p + 1, p + n + 1);
	rep(i, 1, n) {
		while(ph < pt && comp(que[pt-1], que[pt], i)) --pt;
		que[++pt] = i;
		ll x = p[i].fi;
		while(i+1 <= n && p[i+1].fi == x) ++i;
	}
	cout << pt - ph << "\n";


	return 0;
}


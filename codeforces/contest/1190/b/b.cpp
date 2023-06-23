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

const int N = 1e5 + 5;

int n, a[N];

void Alice() {
	cout << "sjfnb" << "\n";
}

void Bob() {
	cout << "cslnb" << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n;
	rep(i, 1, n) cin >> a[i];
	map<int, int> cnt;
	rep(i, 1, n) ++cnt[a[i]];
	int c2 = 0, c3 = 0;
	for(auto [x, y] : cnt) {
		c2 += y == 2;
		c3 += y >= 3;
	}
	if(c3 > 0 || c2 > 1) {
		Bob();
		return 0;
	}
	if(c2 == 1) {
		rep(i, 1, n) if(a[i] && cnt[a[i]] == 2) {
			--cnt[a[i]];
			++cnt[a[i]-1];
			break;
		}
		rep(i, 1, n) if(cnt[a[i]] == 2) {
			Bob();
			return 0;
		}
	}
	ll sum = 0;
	rep(i, 1, n) sum += a[i];
	sum -= 1ll * n * (n-1) / 2;
	if(sum & 1) {
		Alice();
	} else {
		Bob();
	}
	
	return 0;
}

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
ll val[N];

int qs(int i, int j, int k) {
	if(i == j || i == k || j == k) return -1;
	cout << 2 << " " << i << " " << j << " " << k << endl;
	int x; cin >> x;
	return x;
}

ll qp(int i, int j, int k) {
	if(i == j || i == k || j == k) return 0;
	cout << 1 << " " << i << " " << j << " " << k << endl;
	ll x; cin >> x;
	return x;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n;
	int p = 2;
	rep(i, 3, n) {
		if(qs(1, p, i) == 1) p = i;
	}
	vector<pair<ll, int>> v, v1, v2;
	rep(i, 2, n) {
		v.emplace_back(val[i] = qp(1, p, i), i);
	}
	p = max_element(v.begin(), v.end())->se;
	rep(i, 2, n) {
		int s = qs(1, p, i);
		if(s < 0) v1.emplace_back(val[i], i);
		else v2.emplace_back(val[i], i);
	}
	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());
	reverse(v2.begin(), v2.end());
	cout << "0 " << 1 << " ";
	for(auto [y, x] : v1) cout << x << " ";
	for(auto [y, x] : v2) cout << x << " ";
	cout << endl;
	
	return 0;
}

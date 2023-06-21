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

int n, q, a[N<<1];
int ans1[N], ans2[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> q;
	rep(i, 1, n) cin >> a[i];
	int p = max_element(a + 1, a + n + 1) - a;
	deque<int> dq;
	rep(i, 1, n) dq.push_back(a[i]);
	rep(i, 1, p) {
		int x = dq.front(); dq.pop_front();
		int y = dq.front(); dq.pop_front();
		dq.push_front(max(x, y));
		dq.push_back(min(x, y));
		a[n+i] = min(x, y);
		ans1[i] = x, ans2[i] = y;
	}
	while(q--) {
		ll m; cin >> m;
		if(m <= p) {
			cout << ans1[m] << " " << ans2[m] << "\n";
		} else {
			m -= p;
			m %= n-1;
			cout << a[p] << " " << a[p+m+1] << "\n";
		}
	}

	
	return 0;
}

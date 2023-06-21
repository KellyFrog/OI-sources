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

const int N = 3e5 + 5;

int n, m;
int a[N];

bool check(int k) {
	int mx = 0;
	rep(i, 1, n) {
		int l = a[i], r = a[i] + k;
		if(l <= mx && mx <= r) continue;
		if(mx < l) {
			if(r - m >= mx) continue;
			else mx = l;
		} else if(mx > r) {
			return 0;
		}
	}
	return 1;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> m;
	rep(i ,1, n) cin >> a[i];
	int L = 0, R = m;
	int res = -1;
	while(L <= R) {
		int mid = L + R >> 1;
		if(check(mid)) res = mid, R = mid - 1;
		else L = mid + 1;
	}
	cout << res << "\n";
	
	return 0;
}

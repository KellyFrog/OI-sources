// Problem: E - Modulo Pairing
// Contest: AtCoder - AtCoder Grand Contest 032
// URL: https://atcoder.jp/contests/agc032/tasks/agc032_e
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Create Time: 2022-07-14 16:19:50
// Input/Output: stdin/stdout
// 
// Powered by CP Editor (https://cpeditor.org)

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

const int N = 2e5 + 5;

int n, m;
int a[N];

bool check(int k) {
	rep(i, 1, k) {
		int p1 = 2*n-k+i;
		int p2 = 2*n-k-i+1;
		if(a[p1] + a[p2] < m) return 0;
	}
	return 1;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> m;
	rep(i, 1, 2*n) cin >> a[i];
	sort(a + 1, a + 2*n + 1);
	int L = 1, R = n, res = 0;
	
	while(L <= R) {
		int mid = L + R >> 1;
		if(check(mid)) res = mid, L = mid + 1;
		else R = mid - 1;
	}
	
	int ans = 0;
	rep(i, 1, n-res) {
		int p1 = n-res+i;
		int p2 = n-res-i+1;
		ans = max(ans, a[p1] + a[p2]);
	}
	rep(i, 1, res) {
		int p1 = 2*n-res+i;
		int p2 = 2*n-res-i+1;
		assert(a[p1] + a[p2] >= m);
		ans = max(ans, a[p1] + a[p2] - m);
	}
	cout << ans << "\n";
	
	return 0;
}

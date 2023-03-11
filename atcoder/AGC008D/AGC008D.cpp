// Problem: AT_agc008_d [AGC008D] K-th K
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_agc008_d
// Memory Limit: 256 MB
// Time Limit: 2000 ms
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

const int N = 500 * 500 + 100;

int n, a[N], c[N], cnt[N], p[N], b[N];
vector<int> v[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n;
	rep(i, 1, n) cnt[i] = n-1;
	rep(i, 1, n) {
		cin >> a[i];
		b[a[i]] = i;
		c[i] = a[i];
		a[i] -= i;
	}
	rep(i, 1, n) p[i] = i;
	sort(p + 1, p + n + 1, [&](int i, int j) { return c[i] < c[j]; });
	int pos = 0;
	rep(i, 1, n) {
		rep(j, 1, p[i]-1) {
			++pos;
			while(b[pos]) ++pos;
			b[pos] = p[i];
		}
	}
	rep(i, 1, n) {
		rep(j, 1, n-p[i]) {
			++pos;
			while(b[pos]) ++pos;
			b[pos] = p[i];
		}
	}
	rep(i, 1, n*n) v[b[i]].pb(i);
	rep(i, 1, n) if(c[i] != v[i][i-1]) {
		cout << "No" << "\n";
		return 0;
	}
	cout << "Yes" << "\n";
	rep(i, 1, n*n) cout << b[i] << " \n"[i == n*n];

	
	return 0;
}


// Problem: CF148E Porcelain
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF148E
// Memory Limit: 250 MB
// Time Limit: 1000 ms
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

const int N = 105;
const int M = 10005;

int n, m;
vector<int> a[N], s[N], val[N];
int dp[M];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> m;
	rep(i, 1, n) {
		int k; cin >> k;
		vector<int> a(k, 0), val(k+1, 0);
		for(int& x : a) cin >> x;
		vector<int> s = a, t = a;
		reverse(t.begin(), t.end());
		for(int j = 1; j < k; ++j) s[j] += s[j-1];
		for(int j = 1; j < k; ++j) t[j] += t[j-1];
		for(int j = 0; j <= k; ++j) {
			for(int jj = -1; jj < j; ++jj) val[j] = max(val[j], (jj >= 0 ? s[jj] : 0) + (j-jj-2 >= 0 ? t[j-jj-2] : 0));
		}
		per(j, 1, m) rep(jj, 1, min(j, k)) dp[j] = max(dp[j], dp[j-jj] + val[jj]);
	}
	cout << dp[m] << "\n";

	return 0;
}

// Problem: C - Permutation Addition
// Contest: AtCoder - AtCoder Regular Contest 159
// URL: https://atcoder.jp/contests/arc159/tasks/arc159_c
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Create Time: 2023-04-12 19:59:45
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

const int N = 55;

int n, a[N];
vector<vector<int>> ans;

void ins(const vector<int>& v) {
	ans.pb(v);
	rep(i, 1, n) a[i] += v[i-1];
}

inline void solve(int x, int y, int& t) {
	vector<int> a(n);
	a[x-1] = 2, a[y-1] = 1;
	int p = 3;
	rep(i, 1, n) if(!a[i-1]) a[i-1] = p++;
	rep(i, 1, n) {
		rep(i, 1, n) a[i-1] = a[i-1] % n + 1;
		vector<int> b = a;
		if(t && b[x-1] == b[y-1] + 1) {
			swap(b[x-1], b[y-1]);
			--t;
		}
		ins(b);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n;
	rep(i, 1, n) cin >> a[i];
	int s = 0;
	rep(i, 1, n) s += a[i];
	if(s % n != 0) {
		vector<int> a(n);
		rep(i, 1, n) a[i-1] = i;
		ins(a);
		s = 0;
		rep(i, 1, n) s += ::a[i];
		if(s % n != 0) {
			cout << "No" << "\n";
			return 0;
		}
	}
	while(1) {
		int x = min_element(a + 1, a + n + 1) - a;
		int y = max_element(a + 1, a + n + 1) - a;
		if(a[x] == a[y]) break;
		int s = 0;
		rep(i, 1, n) s += a[i];
		s /= n;
		int t = min(s - a[x], a[y] - s);
		while(t) solve(y, x, t);
	}
	cout << "Yes" << "\n";
	cout << ans.size() << "\n";
	for(auto& v : ans) {
		for(int x : v) cout << x << " "; cout << "\n";
	}
	
	return 0;
}

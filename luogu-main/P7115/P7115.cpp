// Problem: P7115 [NOIP2020] 移球游戏
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7115
// Memory Limit: 512 MB
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

const int N = 55;
const int M = 405;

int n, m;
int a[N][M], top[N], tmp[M];
vector<pair<int, int>> ans;

inline void solve(int i, int j) {
	assert(top[j] < m);
	a[j][++top[j]] = a[i][top[i]];
	a[i][top[i]--] = 0;
	ans.emplace_back(i, j);
}

int solve(vector<int> v, int l, int r, int p) {
	if(v.empty()) return p;
	if(l == r) return p;
	assert(v.size() == r-l+1);
	int mid = l + r >> 1;
	for(int i : v) {
		int c0 = 0, c1 = 0;
		int p1 = -1;
		if(1 != i && 1 != p) p1 = 1;
		if(2 != i && 2 != p) p1 = 2;
		if(3 != i && 3 != p) p1 = 3;
		rep(j, 1, m) {
			c0 += a[i][j] <= mid;
			c1 += a[i][j] > mid;
		}
		rep(j, 1, c0) solve(p1, p);
		per(j, 1, m) {
			if(a[i][j] <= mid) solve(i, p1);
			else solve(i, p);
		}
		rep(j, 1, c0) solve(p1, i);
		rep(j, 1, c1) solve(p, i);
		rep(j, 1, c0) solve(p, p1);
	}
	int j = v[0];
	v.pb(p);
	for(int e = 1; e+1 < v.size(); ++e) {
		int i = v[e];
		int ci0 = 0, ci1 = 0, cj0 = 0, cj1 = 0;
		rep(k, 1, m) {
			ci0 += a[i][k] <= mid;
			ci1 += a[i][k] > mid;
			cj0 += a[j][k] <= mid;
			cj1 += a[j][k] > mid;
		}
		if(ci0 + cj0 >= m) {
			rep(k, 1, ci1) solve(i, p);
			rep(k, 1, cj1) solve(j, p);
			int t = m-ci0;
			rep(k, 1, t) solve(j, i);
			while(top[p]) solve(p, j);
		} else {
			rep(k, 1, m) solve(j, p);
			rep(k, 1, m) solve(i, j);
			rep(k, 1, ci0) solve(j, i);
			rep(k, 1, cj0) solve(p, i);
			int t = m-cj1;
			rep(k, 1, t) solve(j, p);
			rep(k, 1, ci1-t) solve(j, i);
			p = j;
			j = i;
		}
	}

	vector<int> v0, v1;
	for(int i : v) {
		assert(top[i] == 0 || top[i] == m);
		if(top[i] == 0) p = i;
		else {
			//print(i);
			if(a[i][1] <= mid) {
				v0.pb(i);
				rep(j, 1, m) assert(a[i][j] <= mid);
			} else {
				v1.pb(i);
				rep(j, 1, m) assert(a[i][j] > mid);
			}
		}
	}
	p = solve(v0, l, mid, p);
	p = solve(v1, mid+1, r, p);
	return p;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> m;
	rep(i, 1, n) rep(j, 1, m) cin >> a[i][j];
	rep(i, 1, n) top[i] = m;

	vector<int> v;
	rep(i, 1, n) v.pb(i);
	solve(v, 1, n, n+1);

	cout << ans.size() << "\n";
	for(auto [x, y] : ans) cout << x << " " << y << "\n";

	return 0;
}


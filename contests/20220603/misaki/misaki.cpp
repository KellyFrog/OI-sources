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

int n, m;
int a[N], b[N];

void genf(int l, int r, int pre, int dep, int a[]) {
	if(l == r) {
		a[l] = pre;
		return;
	}
	int mid = l + r >> 1;
	genf(l, mid, pre, dep + 1, a);
	rep(i, mid+1, r) a[i] = a[i-(mid+1-l)] | 1 << dep;
	reverse(a + mid + 1, a + r + 1);
}

void gen(int n, int a[]) {
	int p = 1, pre = 0;
    bool rev = 1;
    rep(i, 0, 20) {
		if(n >> i & 1) {
			int pre = n >> i+1 << i+1;
			int l = pre;
			int r = pre + (1<<i) - 1;

			genf(l, r, pre, 0, a);

			if(r != n && __builtin_popcount(a[r] ^ a[r+1]) != 1) reverse(a+l, a+r+1);
		}
    }
}

int main() {
	freopen("misaki.in", "r", stdin);
	freopen("misaki.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> m;
	gen(n, a);
	gen(m, b);

	vector<vector<int>> ans1(n, vector<int>(m)), ans2(n, vector<int>(m));
	int t1 = 0, t2 = 0;
	while((1 << t1) < n) ++t1;
	while((1 << t2) < m) ++t2;
	rep(i, 0, n-1) rep(j, 0, m-1) {
		ans1[i][j] = a[i] | b[j] << t1;
		ans2[i][j] = b[j] | a[i] << t2;
	}

	auto solve = [&](vector<vector<int>>& ans) {
		per(i, 0, 23) {
			int mx1 = 0, mx2 = 0;
			for(auto& vec : ans) for(int x : vec) mx1 = max(mx1, x), mx2 = max(mx2, x ^ (1 << i));
			if(mx2 < mx2) {
				for(auto& vec : ans) for(int& x : vec) x ^= 1 << i;
			}
		}
		int mx = 0;
		for(auto& vec : ans) for(int x : vec) mx = max(mx, x);
		return mx;
	};

	int mx1 = solve(ans1), mx2 = solve(ans2);

	if(mx1 < mx2) {
		for(auto& vec : ans1) {
			for(int x : vec) cout << x << " ";
			cout << "\n";
		}
	} else {
		for(auto& vec : ans2) {
			for(int x : vec) cout << x << " ";
			cout << "\n";
		}
	}

	cerr << min(mx1, mx2) << "\n";
	return 0;
}
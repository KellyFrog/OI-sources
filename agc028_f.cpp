// Problem: F - Reachable Cells
// Contest: AtCoder - AtCoder Grand Contest 028
// URL: https://atcoder.jp/contests/agc028/tasks/agc028_f
// Memory Limit: 1024 MB
// Time Limit: 4000 ms
// Create Time: 2022-07-18 08:25:22
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

const int N = 1.5e3 + 5;

int n;
char s[N][N];
int pl[N][N], pr[N][N], ph[N][N], ans[N][N];
vector<int> era[N], fpos[N];
int d1[N], d2[N], s1[N], s2[N];

inline void solve(int l, int r) {
	if(l == r) {
		int sum = 0;
		per(i, 1, n) {
			if(s[l][i] == '#') sum = 0;
			else sum += s[l][i] - '0';
			ans[l][i] += sum;
		}
		return;
	}
	int mid = l + r >> 1;

	cerr << "solve = " << l << " " << r << ", mid = " << mid << "\n";

	rep(i, 1, n) {
		if(s[mid+1][i] == '#') {
			pl[mid+1][i] = n+1, pr[mid+1][i] = 0;
		} else {
			pl[mid+1][i] = s[mid+1][i-1] == '#' ? i : pl[mid+1][i-1];
			pr[mid+1][i] = i;
		}
	}

	rep(i, 1, n) if(s[l][i] != '#') ph[l][i] = l;
	rep(i, l, mid) era[i].clear();
	rep(i, l+1, mid+1) rep(j, 1, n) {
		ph[i][j] = mid+1;
		if(s[i-1][j] != '#') ph[i][j] = min(ph[i][j], ph[i-1][j]);
		if(s[i][j-1] != '#') ph[i][j] = min(ph[i][j], ph[i][j-1]);
	}
	rep(i, 1, n) era[ph[mid+1][i]+1].pb(i);

	rep(i, 1, n+1) d1[i] = d2[i] = 0;

	rep(i, mid+2, r) {
		rep(j, 1, n) {
			pl[i][j] = n+1, pr[i][j] = 0;

			if(s[i][j] == '#') continue;

			pl[i][j] = min(pl[i][j], pl[i][j-1]), pr[i][j] = max(pr[i][j], pr[i][j-1]);
			pl[i][j] = min(pl[i][j], pl[i-1][j]), pr[i][j] = max(pr[i][j], pr[i-1][j]);
		}
	}

	rep(i, mid+1, r) rep(j, 1, n) {
		if(pl[i][j] <= pr[i][j]) {
			d1[pl[i][j]] += s[i][j] - '0';
			d1[pr[i][j]+1] -= s[i][j] - '0';
			d2[pl[i][j]+1] += s[i][j] - '0';
			d2[pr[i][j]+1] -= s[i][j] - '0';
		}
	}

	rep(i, 1, n) d1[i] += d1[i-1], d2[i] += d2[i-1];
	rep(i, 1, n) d1[i] += d1[i-1], d2[i] += d2[i-1];

	per(i, 1, n) {
		if(s[mid+1][i] == '#') continue;
		pl[mid+1][i] = i;
		pr[mid+1][i] = s[mid+1][i+1] == '#' ? i : pr[mid+1][i+1];
	}

	per(i, l, mid) {
		per(j, 1, n) {
			pl[i][j] = n+1, pr[i][j] = 0;
			if(s[i][j] == '#') continue;
			
			pl[i][j] = min(pl[i][j], pl[i][j+1]), pr[i][j] = max(pr[i][j], pr[i][j+1]);
			pl[i][j] = min(pl[i][j], pl[i+1][j]), pr[i][j] = max(pr[i][j], pr[i+1][j]);

			if(pl[i][j] <= pr[i][j]) {
				ans[i][j] += (d1[pr[i][j]] - d1[pl[i][j]-1]) - (d2[pr[i][j]] - d2[pl[i][j]]);
			}
		}
	}

	solve(l, mid);
	solve(mid+1, r);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n;
	rep(i, 1, n+1) {
		s[n+1][i] = s[i][n+1] = s[0][i] = s[i][0] = '#';
		pl[n+1][i] = pl[i][n+1] = pl[0][i] = pl[i][0] = n+1;
		pr[n+1][i] = pr[i][n+1] = pr[0][i] = pr[i][0] = 0;
	}
	rep(i, 1, n) rep(j, 1, n) cin >> s[i][j];

	solve(1, n);
	
	rep(i, 1, n) rep(j, 1, n) cerr << ans[i][j] << " \n"[j == n];

	ll res = 0;
	rep(i, 1, n) rep(j, 1, n) if(s[i][j] != '#') res += (s[i][j] - '0') * (ans[i][j] - (s[i][j] - '0'));
	cout << res << "\n";
	
	return 0;
}

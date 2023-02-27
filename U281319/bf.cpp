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

const int N = 5e4 + 5;
const int M = 1e3 + 5;
const int inf = 0x3f3f3f3f;
const ll P = 2.5e9 + 1;
const int step[4][2] = {
	{-1, 0}, {1, 0}, {0, -1}, {0, 1}
};

ll qpow(ll x, ll p) {
	ll res = 1, base = x;
	while(p) {
		if(p & 1) res = res * base % P;
		base = base * base % P;
		p >>= 1;
	}
	return res;
}

int n, m, k;
pair<int, int> a[M];

namespace bf {
	int cnt[N<<1];
	void solve() {
		cin >> n >> m >> k;
		vector<vector<int>> d(n+1, vector<int>(m+1, inf));
		queue<pair<int, int>> q;
		while(k--) {
			int x, y; cin >> x >> y;
			d[x][y] = 0;
			q.emplace(x, y);
		}
		while(!q.empty()) {
			int x = q.front().fi, y = q.front().se; q.pop();
			rep(i, 0, 3) {
				int nx = x + step[i][0];
				int ny = y + step[i][1];
				if(1 <= nx && nx <= n && 1 <= ny && ny <= m && d[nx][ny] > d[x][y] + 1) {
					d[nx][ny] = d[x][y] + 1;
					q.emplace(nx, ny);
				}
			}
		}
		rep(i, 0, n+m) cnt[i] = 0;
		rep(i, 1, n) rep(j, 1, m) cerr << d[i][j] << " \n"[j == m];
		rep(i, 1, n) rep(j, 1, m) ++cnt[d[i][j]];
		ll ans = 1;
		rep(i, 1, n+m) cnt[i] += cnt[i-1];
		rep(i, 0, n+m-2) ans = ans * (cnt[i]-i) % P * qpow(n*m-i, P-2) % P;
		cout << ans << "\n";
	}
}

namespace sol {

	int t1[N][8], t2[N][8];

	inline int lowbit(int x) { return x & (-x); }
	inline void add(int id, int x, int val, int pos) { for(int x0 = x; x0 <= m || x0 <= n; x0 += lowbit(x0)) if(t1[id][x0] > val) t1[id][x0] = val, t2[id][x0] = pos; }
	inline int query(int id, int x) { int val = inf, pos = -1; for(int x0 = x; x0; x0 -= lowbit(x0)) if(t1[id][x0] < val) val = t1[id][x0], pos = t2[id][x0]; return pos; }

	void solve() {
		cin >> n >> m >> k;
		rep(i, 1, k) cin >> a[i].fi >> a[i].se;
		sort(a + 1, a + k + 1);

	}

}

int main() {
// 	freopen("cannon.in", "r", stdin);
// 	freopen("cannon.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	int t; cin >> t;
	while(t--) bf::solve();

	return 0;
}

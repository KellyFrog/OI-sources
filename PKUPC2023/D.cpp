#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define rep(i, s, t) for(int i = (s); i <= (t); ++i)
#define per(i, s, t) for(int i = (t); i >= (s); --i)
#define fi first
#define se second
#define mp make_pair
#define pb push_back

const int N = 1e3 + 5;
const int inf = 0x3f3f3f3f;

int n;
int a[N][N], d[N][N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	cin >> n;
	int c1 = 0, c2 = 0;
	rep(i, 1, n) rep(j, 1, n) {
		cin >> a[i][j];
		if(a[i][j] == 1) ++c1;
		else if(a[i][j] == 2) ++c2;
	}
	int p = c1 == c2 ? 1 : 2;
	rep(i, 1, n) rep(j, 1, n) {
		if(a[i][j] == p) a[i][j] = 0;
		else if(a[i][j] == 0) a[i][j] = 1;
		else a[i][j] = inf;
	}
	if(p == 1) {
		rep(i, 1, n) rep(j, 1, i-1) swap(a[i][j], a[j][i]);
	}
	memset(d, 0x3f, sizeof d);
	priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
	rep(i, 1, n) {
		pq.emplace(d[i][1] = a[i][1], mp(i, 1));
	}
	while(!pq.empty()) {
		auto [x, y] = pq.top().se; pq.pop();

		auto upd = [&](int nx, int ny) {
			if(nx < 1 || nx > n || ny < 1 || ny > n) return;
			if(d[x][y] + a[nx][ny] < d[nx][ny]) {
				pq.emplace(d[nx][ny] = d[x][y] + a[nx][ny], mp(nx, ny));
			}
		};

		upd(x, y-1), upd(x, y+1);
		upd(x+1, y), upd(x+1, y+1);
		upd(x-1, y-1), upd(x-1, y);
	}
	int ans = inf;
	rep(i, 1, n) ans = min(ans, d[i][n]);
	cout << (ans == inf ? -1 : ans) << '\n';

	return 0;
}

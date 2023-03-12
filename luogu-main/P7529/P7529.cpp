// Vroblem: V7529 [USACO21OVEN] Vermutation G
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/V7529
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Vowered by CV Editor (https://cpeditor.org)

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

struct V {
	int x, y;
	V() {};
	V(int x, int y) : x(x), y(y) {}
};

V operator - (const V& x, const V& y) { return V(x.x - y.x, x.y - y.y); }
int calc(const V& p, const V& q) { return abs(p.x * q.y - p.y * q.x); }

const int N = 45;
const int P = 1e9 + 7;

int n;
V a[N];
int f[N][N][N][N], cnt[N][N][N];
bool vis[N][N][N][N];

inline bool isin(int i, int j, int k, int l) {
	if(i == j && j == k) return l == i;
	return calc(a[i]-a[l], a[j]-a[l]) + calc(a[i]-a[l], a[k]-a[l]) + calc(a[j]-a[l], a[k]-a[l]) == calc(a[i]-a[j], a[i]-a[k]);
}

inline bool chkin(int i, int j, int k, int l) {
	if(i>j) swap(i, j);
	if(j>k) swap(j, k);
	if(i>j) swap(i, j);
	return vis[i][j][k][l];
}

inline bool check(int i, int j, int k, int l) {
	return chkin(i, j, l, k) || chkin(i, k, l, j) || chkin(j, k, l, i);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n;
	rep(i, 1, n) cin >> a[i].x >> a[i].y;
	rep(i, 1, n) rep(j, i, n) rep(k, j, n) {
		rep(l, 1, n) cnt[i][j][k] += (vis[i][j][k][l] = isin(i, j, k, l));
	}
	vector<tuple<int, int, int>> v;
	rep(i, 1, n) rep(j, i, n) rep(k, j, n) v.emplace_back(i, j, k);
	sort(v.begin(), v.end(), [&](const auto& x, const auto& y) {
			return cnt[get<0>(x)][get<1>(x)][get<2>(x)] < cnt[get<0>(y)][get<1>(y)][get<2>(y)];
			});
	rep(i, 1, n) f[i][i][i][1] = 1;
	for(auto [i, j, k] : v) {
		rep(l, 1, cnt[i][j][k]) f[i][j][k][l] = (f[i][j][k][l] + 1ll * (cnt[i][j][k]-l+1) * f[i][j][k][l-1]) % P;
		rep(l, 1, cnt[i][j][k]) rep(m, 1, n) {
			if(m != i && m != j && m != k) {
				int a = -1, b = -1, c = -1;
				if(chkin(i, j, m, k)) a = i, b = j, c = m;
				else if(chkin(i, k, m, j)) a = i, b = k, c = m;
				else if(chkin(j, k, m, i)) a = j, b = k, c = m;
				if(a == -1) continue;
				if(b > c) swap(b, c);
				if(a > b) swap(a, b);
				f[a][b][c][l+1] = (f[a][b][c][l+1] + f[i][j][k][l]) % P;
			}
		}
	}
	int ans = 0;
	rep(i, 1, n) rep(j, i, n) rep(k, j, n) ans = (ans + f[i][j][k][n]) % P;
	cout << ans << "\n";
	
	return 0;
}

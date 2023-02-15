// Problem: P7528 [USACO21OPEN] Portals G
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7528
// Memory Limit: 256 MB
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

const int N = 4e5 + 5;

int n;
int uni[N], c[N], p[N][4], pe[N];
vector<int> eg[N];

inline int find(int x) { return x == uni[x] ? x : uni[x] = find(uni[x]); }
inline void merge(int x, int y) { x = find(x), y = find(y); if(x != y) uni[x] = y; }
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n;
	rep(i, 1, n) {
		cin >> c[i] >> p[i][0] >> p[i][1] >> p[i][2] >> p[i][3];
		eg[p[i][0]].pb(i), eg[p[i][1]].pb(i), eg[p[i][2]].pb(i+n), eg[p[i][3]].pb(i+n);
	}
	rep(i, 1, 2*n) assert(eg[i].size() == 2);
	rep(i, 1, 2*n) uni[i] = i;
	rep(i, 1, n) {
		merge(i, eg[p[i][0]][0]), merge(i, eg[p[i][0]][1]);
		merge(i, eg[p[i][1]][0]), merge(i, eg[p[i][1]][1]);
		merge(i+n, eg[p[i][2]][0]), merge(i+n, eg[p[i][2]][1]);
		merge(i+n, eg[p[i][3]][0]), merge(i+n, eg[p[i][3]][1]);
	}
	rep(i, 1, n) pe[i] = i;
	sort(pe + 1, pe + n + 1, [&](int i, int j) { return c[i] < c[j]; });
	int ans = 0;
	rep(i, 1, n) {
		int u = pe[i];
		if(find(u) != find(u+n)) {
			merge(u, u+n), ans += c[u];
		}
	}
	cout << ans << "\n";
	
	return 0;
}

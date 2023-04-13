// Problem: AT3957 [AGC023F] 01 on Tree
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT3957
// Memory Limit: 250 MB
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

const int N = 2e5 + 5;

int n;
int a[N], uni[N], cnt[2][N], fat[N];
ll ans;

inline int find(int x) { return x == uni[x] ? x : uni[x] = find(uni[x]); }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n;
	rep(i, 2, n) cin >> fat[i];
	rep(i, 1, n) cin >> a[i];
	rep(i, 1, n) uni[i] = i, cnt[a[i]][i] = 1;
	set<pair<double, int>> s;
	
	auto div = [&](int x, int y) { return y == 0 ? 1e18 : 1.0 * x / y;; };
	rep(i, 1, n) s.emplace(div(cnt[1][i], cnt[0][i]), i);
	rep(i, 2, n) {
		auto it = s.begin();
		if(it->se == 1) ++it;
		int u = it->se;
		int f = find(fat[u]);
		s.erase(mp(div(cnt[1][u], cnt[0][u]), u));
		s.erase(mp(div(cnt[1][f], cnt[0][f]), f));
		ans += 1ll * cnt[1][f] * cnt[0][u];
		uni[u] = f;
		cnt[0][f] += cnt[0][u];
		cnt[1][f] += cnt[1][u];
		s.emplace(div(cnt[1][f], cnt[0][f]), f);
	}
	cout << ans << "\n";
	
	return 0;
}

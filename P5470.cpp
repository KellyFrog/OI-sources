// Problem: P5470 [NOI2019] 序列
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5470
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// Create Time: 2022-07-03 09:21:40
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

const int N = 2e5 + 5;
const int inf = 0x3f3f3f3f;

int n, a[N], b[N];
bool era[5][N];
int k, l;

void solve() {
	// cerr << "---solve---" << "\n";
	cin >> n >> k >> l;
	rep(i, 1, n) cin >> a[i];
	rep(i, 1, n) cin >> b[i];
	rep(j, 0, 4) rep(i, 1, n) era[j][i] = 0;
	int t = k - l;
	priority_queue<pair<int, int>> pq[5];
	rep(i, 1, n) {
		pq[0].emplace(a[i], i);
		pq[1].emplace(b[i], i);
		pq[2].emplace(a[i]+b[i], i);
	}
	ll ans = 0;
	while(k--) {
		int val[5], curans[5];
		rep(i, 0, 4) {
			while(!pq[i].empty() && era[i][pq[i].top().se]) pq[i].pop();
			val[i] = pq[i].empty() ? -inf : pq[i].top().fi;
		}
		curans[0] = val[2];
		curans[1] = val[3] + val[4];
		curans[2] = val[4] + val[0];
		curans[3] = val[3] + val[1];
		curans[4] = t ? val[0] + val[1] : -inf;
		int res = -inf, op = -1;
		rep(i, 0, 4) if(curans[i] > res) res = curans[i], op = i;
		ans += res;
		// cerr << "t = " << t << ", " << "get res = " << res << ", op = " << op << "\n";
		// rep(i, 0, 4) cerr << val[i] << " \n"[i == 4];
		if(op == 0) {
			int i = pq[2].top().se;
			era[0][i] = 1;
			era[1][i] = 1;
			era[2][i] = 1;
		} else if(op == 1) {
			++t;
			int i = pq[4].top().se;
			int j = pq[3].top().se;
			era[0][j] = 1;
			era[1][i] = 1;
			era[3][j] = 1;
			era[4][i] = 1;
		} else if(op == 2) {
			int i = pq[4].top().se;
			int j = pq[0].top().se;
			era[0][j] = 1;
			era[1][i] = 1;
			era[2][j] = 1;
			pq[4].emplace(b[j], j);
			era[4][i] = 1;
		} else if(op == 3) {
			int i = pq[1].top().se; //b[i]
			int j = pq[3].top().se;
			era[0][j] = 1;
			era[1][i] = 1;
			era[2][i] = 1;
			pq[3].emplace(a[i], i);
			era[3][j] = 1;
		} else {
			--t;
			int i = pq[0].top().se;
			int j = pq[1].top().se;
			era[0][i] = 1;
			era[1][j] = 1;
			era[2][i] = era[2][j] = 1;
			pq[3].emplace(a[j], j);
			pq[4].emplace(b[i], i);
		}
	}
	cout << ans << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	int t;
	cin >> t;
	while(t--) solve();
	
	return 0;
}
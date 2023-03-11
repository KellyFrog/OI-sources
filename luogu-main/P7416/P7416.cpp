// Problem: P7416 [USACO21FEB] No Time to Dry P
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7416
// Memory Limit: 250 MB
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

const int N = 2e5 + 5;

int n, q;
int a[N], t[N], ans[N];
int stk[N], top;
vector<pair<int, int>> qr[N];

inline int lowbit(int x) { return x & (-x); }
inline void add(int x, int val) { for(int x0 = x; x0 <= n; x0 += lowbit(x0)) t[x0] += val; }
inline int query(int x) { int res = 0; for(int x0 = x; x0; x0 -= lowbit(x0)) res += t[x0]; return res; }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> q;
	rep(i, 1, n) cin >> a[i];
	rep(i, 1, q) {
		int l, r; cin >> l >> r;
		qr[r].emplace_back(l, i);
	}
	rep(i, 1, n) {
		while(top && a[stk[top]] > a[i]) --top;
		if(a[stk[top]] == a[i]) {
			add(stk[top]+1, 1);
			add(i+1, -1);
		} else {
			add(1, 1);
			add(i+1, -1);
		}
		stk[++top] = i;
		for(auto e : qr[i]) ans[e.se] = query(e.fi);
	}
	rep(i, 1, q) cout << ans[i] << "\n";
	
	return 0;
}

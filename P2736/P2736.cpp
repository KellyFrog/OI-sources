// Problem: P2736 [USACO3.4]“破锣摇滚”乐队 Raucous Rockers
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P2736
// Memory Limit: 125 MB
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

const int N = 25;

int n, m, t;
int a[N];

bool check(int s) {
	int cnt = 1, cur = 0;
	rep(i, 1, n) if(s >> i-1 & 1) {
		if(a[i] > t) return 0;
		if(cur + a[i] > t) {
			++cnt;
			cur = a[i];
		} else {
			cur += a[i];
		}
	}
	return cnt <= m;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> t >> m;
	rep(i, 1, n) cin >> a[i];
	int u = (1 << n) - 1;
	int ans = 0;
	rep(s, 0, u) if(check(s)) ans = max<int>(ans, __builtin_popcount(s));
	cout << ans << "\n";

	return 0;
}

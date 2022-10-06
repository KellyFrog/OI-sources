// Problem: P6625 [省选联考 2020 B 卷] 卡牌游戏
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6625
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// Create Time: 2022-07-12 11:06:28
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

const int N = 1e5 + 5;

int n;
ll pre[N], ans;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n;
	rep(i, 1, n) cin >> pre[i], pre[i] += pre[i-1];
	rep(i, 2, n) ans += max(0ll, pre[i]);
	cout << ans << "\n";
	
	return 0;
}

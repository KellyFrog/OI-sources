// Problem: P4369 [Code+#4]组合数问题
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4369
// Memory Limit: 128 MB
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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	int n, k;
	cin >> n >> k;
	rep(i, 1, k-1) cout << i << " " << 0 << "\n";
	cout << n-k+1 << " " << 1 << "\n";
	
	return 0;
}

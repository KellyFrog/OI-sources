// Problem: P7517 [省选联考 2021 B 卷] 数对
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7517
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// Create Time: 2022-07-12 11:30:37
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

const int N = 5e5 + 5;

int n;
int a[N], b[N];
bool vis[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n;
	rep(i, 1, n) {
		int x; cin >> x;
		++a[x], ++b[x];
	}
	int m = 5e5;
	rep(i, 2, m) {
		if(!vis[i]) {
			for(int j = i + i; j <= m; j += i) {
				vis[j] = 1;
				b[j] += b[j/i];
			}
		}
	}
	rep(i, 2, m) b[i] += a[1];
	ll ans = 0;
	rep(i, 1, m) ans += 1ll * a[i] * b[i];
	cout << ans - n << "\n";
	
	return 0;
}

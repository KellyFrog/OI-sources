// Problem: AT_agc007_f [AGC007F] Shik and Copying String
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_agc007_f
// Memory Limit: 256 MB
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

const int N = 1e6 + 5;

int n;
char s[N], t[N];
int f[N], pos[N], lst[27];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n;
	cin >> (s + 1) >> (t + 1);

	int p = n;
	per(i, 1, n) {
		p = min(p, i);
		while(p && s[p] != t[i]) --p;
		if(!p) {
			cout << -1 << "\n";
			return 0;
		}
		pos[i] = p;
	}
	rep(i, 1, n) f[i] = pos[i] == i ? 0 : f[pos[i]] + 1;
	int ans = 0;
	rep(i, 1, n) ans = max(ans, f[i]);
	cout << ans << "\n";
	
	return 0;
}


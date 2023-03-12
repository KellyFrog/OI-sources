// Problem: P8189 [USACO22FEB] Redistributing Gifts G
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P8189
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

const int N = 18 + 5;
const int M = 1 << 18 | 5;

int n, q, a[N][N];
char s[N];
bool e[N][N];
int low[M];
ll f[M], g[M][N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n;
	rep(i, 1, n) rep(j, 1, n) {
		int x; cin >> x; a[i][x] = j;
	}
	rep(i, 1, n) rep(j, 1, n) if(a[i][j] <= a[i][i]) e[i][j] = 1;
	
	int u = (1 << n) - 1;
	rep(s, 1, u) low[s] = (s & 1) ? 1 : low[s>>1] + 1;

	f[0] = 1;
	rep(i, 1, n) g[1<<i-1][i] = 1;

	rep(s, 1, u) {
		rep(i, 1, n) if(s >> i-1 & 1) if(e[i][low[s]]) f[s] += g[s][i];
		rep(i, 1, n) if(s >> i-1 & 1) rep(j, low[s]+1, n) if(!(s >> j-1 & 1) && e[i][j]) g[s|1<<j-1][j] += g[s][i];
		rep(i, 1, low[s]-1) g[s|1<<i-1][i] += f[s];
	}
	
	cin >> q;
	while(q--) {
		cin >> (s + 1);
		int s1 = 0, s2 = 0;
		rep(i, 1, n) {
			if(s[i] == 'H') s1 |= 1 << i-1;
			else s2 |= 1 << i-1;
		}
		cout << f[s1] * f[s2] << "\n";
	}
	return 0;
}

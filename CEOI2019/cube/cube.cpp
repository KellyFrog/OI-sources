// Problem: P6090 [CEOI2019] 立方填词
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6090
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// Create Time: 2023-06-19 11:18:36
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
const int M = 13;
const int K = 65;
const int P = 998244353;

int n, m = 62;
int f[M][K][K], g[K][K][K];
vector<string> v;

inline int toint(char c) {
	if('0' <= c && c <= '9') return c - '0' + 1;
	if('a' <= c && c <= 'z') return c - 'a' + 11;
	if('A' <= c && c <= 'Z') return c - 'A' + 37;
	return -1;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n;
	rep(i, 1, n) {
		string str; cin >> str;
		v.pb(str);
		reverse(str.begin(), str.end());
		v.pb(str);
	}
	sort(v.begin(), v.end());
	for(int i = 0; i < v.size(); ++i) {
		if(i && v[i] == v[i-1]) continue;
		int m = v[i].size();
		int a = toint(v[i][0]);
		int b = toint(v[i][m-1]);
		++f[m][a][b];
	}
	int ans = 0;
	rep(i, 3, 10) {
		memset(g, 0, sizeof g);
		rep(a, 1, m) rep(b, 1, m) rep(c, 1, m) rep(d, 1, m) g[b][c][d] = (g[b][c][d] + 1ll * f[i][a][b] * f[i][a][c] % P * f[i][a][d]) % P;
		rep(a, 1, m) rep(b, 1, m) rep(c, 1, m) rep(d, 1, m) ans = (ans + 1ll * g[a][b][c] * g[a][b][d] % P * g[a][c][d] % P * g[b][c][d]) % P;
	}
	cout << ans << "\n";
	
	return 0;
}


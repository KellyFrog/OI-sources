// Problem: CF506E Mr. Kitayuta's Gift
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF506E
// Memory Limit: 750 MB
// Time Limit: 6000 ms
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

const int N = 205;
const int P = 1e4 + 7;

int n, m;
char s[N];
int f[N][N][N], g[N][N];
int pw[N][N], res[N][N], tmp[N][N];

void mul(int a[N][N], int b[N][N], int c[N][N]) {
	memset(tmp, 0, sizeof tmp);
	rep(k, 0, n+1) rep(i, 0, n+1) rep(j, 0, n+1) tmp[i][j] = (tmp[i][j] + 1ll * a[i][k] * b[k][j]) % P;
	memcpy(c, tmp, sizeof tmp);
}

int solve(int k) {
	cerr << "k=" << k << "\n";
	++k;
	rep(i, 0, n+1) rep(j, 0, n+1) cerr << g[i][j] << " \n"[j == n+1];
	memcpy(pw, g, sizeof pw);
	memset(res, 0, sizeof res);
	rep(i, 0, n+1) res[i][i] = 1;
	while(k) {
		if(k & 1) mul(res, pw, res);
		mul(pw, pw, pw);
		k >>= 1;
	}
	return res[0][n+1];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> (s+1) >> m;
	n = strlen(s+1);

	f[1][n][0] = 1;
	rep(i, 1, n) per(j, i, n) {
		if(s[i] == s[j]) {
			rep(k, 0, n) f[i+1][j-1][k+1] = (f[i+1][j-1][k+1] + f[i][j][k]) % P;
		} else {
			rep(k, 0, n) {
				f[i+1][j][k+1] = (f[i+1][j][k+1] + f[i][j][k]) % P;
				f[i][j-1][k+1] = (f[i][j-1][k+1] + f[i][j][k]) % P;
			}
		}
	}

	rep(i, 1, n) g[i-1][i] = 1, g[i][i] = 25;
	g[0][0] = 26;

	cerr << n + m << "\n";

	int ans = 0;
	if((n + m) % 2 == 0) {
		rep(i, 1, n+1) rep(j, 1, n) g[j][n+1] = (g[j][n+1] + f[i][i-1][j]) % P;
		rep(i, 1, n) rep(j, 1, n) g[j+1][n+1] = (g[j+1][n+1] + f[i][i][j]) % P;
		ans = (ans + solve(n + m >> 1)) % P;
	} else {
		rep(i, 1, n+1) rep(j, 1, n) g[j][n+1] = (g[j][n+1] + f[i][i-1][j]) % P;
		rep(i, 1, n) rep(j, 1, n) g[j+1][n+1] = (g[j+1][n+1] + f[i][i][j]) % P;
		rep(i, 1, n-1) if(s[i] == s[i+1]) rep(j, 0, n-1) g[j+1][n+1] = (g[j+1][n+1] - f[i][i+1][j]) % P;
		ans = (ans + solve(n + m + 1 >> 1)) % P;
		rep(i, 1, n) g[i][n+1] = 0;
		rep(i, 1, n-1) if(s[i] == s[i+1]) rep(j, 0, n-1) g[j+1][n+1] = (g[j+1][n+1] + f[i][i+1][j]) % P;
		ans = (ans + 26ll * solve(n + m >> 1)) % P;
	}

	cout << (ans + P) % P << "\n";
	
	return 0;
}

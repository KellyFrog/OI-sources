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
const int M = N << 1;
const int P = 1e4 + 7;

int n, m;
char s[N];
int f[N][N][N], g[M][M];
int pw[M][M], res[M][M], tmp[M][M];

void mul(int a[M][M], int b[M][M], int c[M][M]) {
	memset(tmp, 0, sizeof tmp);
	rep(k, 0, 2*n) rep(i, 0, 2*n) rep(j, 0, 2*n) tmp[i][j] = (tmp[i][j] + a[i][k] * b[k][j]) % P;
	memcpy(c, tmp, sizeof tmp);
}

int solve(int k) {
	cerr << "k=" << k << "\n";
	
	rep(i, 0, 2*n) rep(j, 0, 2*n) cerr << g[i][j] << " \n"[j == 2*n];
	memset(res, 0, sizeof res);
	rep(i, 0, 2*n) res[i][i] = 1;
	rep(t, 1, k) {
		mul(res, g, res);
		rep(i, 0, 2*n) cerr << res[0][i] << " \n"[i == 2*n];
	}

	memcpy(pw, g, sizeof pw);
	memset(res, 0, sizeof res);
	rep(i, 0, 2*n) res[i][i] = 1;
	while(k) {
		if(k & 1) mul(res, pw, res);
		mul(pw, pw, pw);
		k >>= 1;
	}
	rep(i, 0, 2*n) cerr << res[0][i] << " \n"[i == 2*n];
	return res[0][2*n];
}

int sum[N];

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


	int ans = 0;
	if((n + m) % 2 == 0) {
		rep(i, 1, n) g[i-1][i] = 1, g[i][i] = 24;
		rep(i, n+2, 2*n) g[i-1][i] = 1;
		rep(i, n+1, 2*n) g[i][i] = 25;
		g[2*n][2*n] = 26, g[0][0] = 24;

		rep(i, 1, n+1) rep(j, n/2, n) sum[j] = (sum[j] + f[i][i-1][j]) % P;
		rep(i, 1, n) rep(j, 0, n) sum[j+1] = (sum[j+1] + f[i][i][j]) % P;
		rep(i, 1, n) cerr << sum[i] << " \n"[i == n];


		rep(i, 1, n+1) rep(j, n/2, n) g[2*j-n-2][j+n-1] = (g[2*j-n-2][j+n-1] + f[i][i-2][j]) % P;
		rep(i, 1, n) rep(j, 1, n) g[2*(j+1)-n-2][j+1+n-1] = (g[2*(j+1)-n-2][j+1+n-1] + f[i][i][j]) % P;

		ans = (ans + solve(n + m >> 1)) % P;
	} else {
		rep(i, 1, n) g[i-2][i] = 1, g[i][i] = 24;
		rep(i, n+2, 2*n) g[i-2][i] = 1;
		rep(i, n+1, 2*n) g[i][i] = 25;
		g[2*n][2*n] = 26, g[0][0] = 24;
		rep(i, 1, n+1) rep(j, n/2, n) g[2*j-n-2][j+n] = (g[2*j-n-2][j+n] + f[i][i-2][j]) % P;
		rep(i, 1, n) rep(j, 1, n) g[2*(j+1)-n-2][j+1+n] = (g[2*(j+1)-n-2][j+1+n] + f[i][i][j]) % P;
		rep(i, 1, n-2) if(s[i] == s[i+1]) rep(j, 0, n-2) g[2*(j+1)-n-2][j+1+n] = (g[2*(j+1)-n-2][j+1+n] - f[i][i+1][j]) % P;
		ans = (ans + solve(n + m + 1 >> 1)) % P;

		memset(g, 0, sizeof g);
		rep(i, 1, n) g[i-2][i] = 1, g[i][i] = 24;
		rep(i, n+2, 2*n) g[i-2][i] = 1;
	   	rep(i, n+1, 2*n) g[i][i] = 25;
		g[2*n][2*n] = 26, g[0][0] = 24;
		rep(i, 1, n-2) if(s[i] == s[i+1]) rep(j, 0, n-2) g[2*(j+1)-n-2][j+1+n] = (g[2*(j+1)-n-2][j+1+n] + f[i][i+1][j]) % P;
		ans = (ans + 26ll * solve(n + m >> 1)) % P;
	}

	cout << (ans + P) % P << "\n";
	
	return 0;
}

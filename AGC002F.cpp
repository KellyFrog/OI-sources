// Problem: AT2000 [AGC002F] Leftmost Ball
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT2000
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// Create Time: 2022-07-27 20:02:04
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

const int N = 2e3 + 5;
const int P = 1e9 + 7;

int qpow(int x, int p) {
	int res = 1, base = x;
	while(p) {
		if(p & 1) res = 1ll * res * base % P;
		base = 1ll * base * base % P;
		p >>= 1;
	}
	return res;
}

int n, k;
int fac[N*N], ifac[N*N];
int f[N][N];

int cob(int n, int m) {
	return 1ll * fac[n] * ifac[m] % P * ifac[n-m] % P;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> k;
	
	if(k == 1) {
		cout << 1 << "\n";
		return 0;
	}
	
	int m = n * k;
	fac[0] = ifac[0] = fac[1] = ifac[1] = 1;
	rep(i, 2, m) fac[i] = 1ll * fac[i-1] * i % P;
	ifac[m] = qpow(fac[m], P - 2);
	per(i, 2, m-1) ifac[i] = 1ll * ifac[i+1] * (i+1) % P;
	
	f[1][0] = 1;
	rep(i, 1, n) rep(j, 0, i) {
		f[i+1][j] = (f[i+1][j] + f[i][j]) % P;
		f[i][j+1] = (f[i][j+1] + 1ll * f[i][j] * (n-j) % P * cob(n*k - i - j*(k-1) - 1, k-2)) % P;
	}
	
	cout << f[n][n] << "\n";
	
	return 0;
}

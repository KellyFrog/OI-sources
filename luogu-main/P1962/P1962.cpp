// Problem: P1962 斐波那契数列
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P1962
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

const int P = 1e9 + 7;

int a[2][2], b[2][2], c[2][2];

void mul(int a[2][2], int x[2][2], int y[2][2]) {
	c[0][0] = (1ll * x[0][0] * y[0][0] + 1ll * x[0][1] * y[1][0]) % P;
	c[0][1] = (1ll * x[0][0] * y[0][1] + 1ll * x[0][1] * y[1][1]) % P;
	c[1][0] = (1ll * x[1][0] * y[0][0] + 1ll * x[1][1] * y[1][0]) % P;
	c[1][1] = (1ll * x[1][0] * y[0][1] + 1ll * x[1][1] * y[1][1]) % P;
	a[0][0] = c[0][0];
	a[0][1] = c[0][1];
	a[1][0] = c[1][0];
	a[1][1] = c[1][1];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	ll p; cin >> p;
	if(p <= 2) {
		cout << 1 << "\n";
		return 0;
	}
	p -= 1;
	
	a[0][0] = a[1][1] = 1;
	b[0][0] = b[1][0] = b[0][1] = 1;
	while(p) {
		if(p & 1) {
			mul(a, a, b);
		}
		mul(b, b, b);
		p >>= 1;
	}
	cout << a[0][0] << "\n";
	
	return 0;
}

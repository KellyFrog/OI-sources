// Problem: U105217 整数拆分
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/U105217
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

const int N = 5e4 + 5;
const int P = 1e9 + 7;

int n, f[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n;
	f[0] = 1;
	rep(i, 1, n) {
		rep(j, 0, i-1) f[i] = (f[i] + f[j]) % P;
		rep(j, 0, i-1) if(i-j+1&1) f[i] = (f[i] - f[j]) % P;
		cerr << f[i] << " \n"[i == n];
	}
	cout << (f[n] + P) % P << '\n';
	
	return 0;
}

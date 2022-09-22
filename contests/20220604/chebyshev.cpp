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

const int N = 1e7 + 5;
const int P = 1e9 + 7;

int k, n;
int y[N], ifac[N];
int pre[N], suf[N];

int qpow(int x, int p) {
	int res = 1, base = x;
	while(p) {
		if(p & 1) res = 1ll * res * base % P;
		base = 1ll * base * base % P;
		p >>= 1;
	}
	return res;
}

int query(int x) {
	pre[0] = 1, suf[k+3] = 1;
	rep(i, 1, k+2) pre[i] = 1ll * pre[i-1] * (x - i) % P;
	per(i, 1, k+2) suf[i] = 1ll * suf[i+1] * (x - i) % P;
	int ans = 0;
	rep(i, 1, k+2) {
		ans = (ans + (k+2-i & 1 ? -1ll : 1ll) * pre[i-1] * suf[i+1] % P * y[i] % P * ifac[i-1] % P * ifac[k+2-i]) % P;
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	freopen("chebyshev.in", "r", stdin);
	freopen("chebyshev.out", "w", stdout);

	cin >> k >> n;
	rep(i, 1, k+2) {
		y[i] = (y[i-1] + qpow(i, k)) % P;
	}
	int fac = 1;
	rep(i, 2, k+2) fac = 1ll * fac * i % P;
	ifac[k+2] = qpow(fac, P - 2);
	ifac[0] = 1;
	per(i, 1, k+1) ifac[i] = 1ll * ifac[i+1] * (i+1) % P;

	int ans = (1ll * n * qpow(2 * n + 1, k) - (query(2 * n) - 1ll * qpow(2, k) * query(n))) % P;
	cout << (ans + P) % P << "\n";
	
	return 0;
}
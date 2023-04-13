// Problem: CF794G Replace All
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF794G
// Memory Limit: 250 MB
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

const int N = 6e5 + 5;
const int P = 1e9 + 7;

inline int qpow(int x, ll p) {
	int res = 1, base = x;
	while(p) {
		if(p & 1) res = 1ll * res * base % P;
		base = 1ll * base * base % P;
		p >>= 1;
	}
	return res;
}

int n, m, k;
char s[N], t[N];
int ans, cnt[N];
int fac[N], ifac[N], pw[N];

inline int cob(int n, int m) {
	if(n < m || m < 0) return 0;
	return 1ll * fac[n] * ifac[m] % P * ifac[n-m] % P;
}

int solve(int lena, int lenb) {
	if(lena < 0) lena *= -1, lenb *= -1;
	if(lena <= 0 || lenb <= 0) return 0;
	int g = __gcd(lena, lenb);
	lena /= g, lenb /= g;
	int t = k / max(lena, lenb);
	g = 1;
	return 1ll * (qpow(2, (t+1)*g) - qpow(2, g)) * qpow(qpow(2, g)-1, P-2) % P;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> (s+1) >> (t+1) >> k;
	n = strlen(s+1), m = strlen(t+1);

	fac[0] = ifac[0] = fac[1] = ifac[1] = 1;
	rep(i, 2, n+m) fac[i] = 1ll * fac[i-1] * i % P;
	ifac[n+m] = qpow(fac[n+m], P-2);
	per(i, 2, n+m-1) ifac[i] = 1ll * ifac[i+1] * (i+1) % P;

	int qs = 0, qt = 0, as = 0, at = 0;
	rep(i, 1, n) {
		qs += s[i] == '?';
		as += s[i] == 'A';
	}
	rep(i, 1, m) {
		qt += t[i] == '?';
		at += t[i] == 'A';
	}

	if(n == m) {
		int c = 1;
		rep(i, 1, n) {
			if(s[i] == '?' && ::t[i] == '?') c = 2 * c % P;
			else if(s[i] != '?' && ::t[i] != '?' && s[i] != ::t[i]) c = 0;
		}
		int v = 2 * (qpow(2, k) - 1) % P;
		ans = (ans + 1ll * c * v % P * v) % P;
		int t = cob(qs+qt, qt+at-as) - c;
		rep(i, 1, k) cnt[i] = 1ll * (k/i) * (k/i) % P;
		per(i, 1, k) {
			for(int j = i+i; j <= k; j += i) cnt[i] = (cnt[i] - cnt[j]) % P;
			ans = (ans + 1ll * t * cnt[i] % P * qpow(2, i)) % P;
		}
	}

	rep(i, as-at-qt, as-at+qs) {
		if(i == 0) continue;
		ans = (ans + 1ll * cob(qs+qt, i+qt+at-as) * solve(i, i+m-n)) % P;
	}
	cout << (ans + P) % P << "\n";
	
	return 0;
}

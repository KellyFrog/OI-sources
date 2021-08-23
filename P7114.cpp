// Happy Chinese new year! (Feb. 12th, 2021)

/*
 * Codeforces @Chenkaifeng
 * Luogu @longer_name
 */

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define fi first
#define se second
#define rg register
#define mp make_pair
#define pb push_back
#define pf push_front

#define rep(i, s, t) for (rg int i = s; i <= t; i++)
#define per(i, s, t) for (rg int i = t; i >= s; i--)
#define OK cerr << "OK!\n"

namespace fastio {
	const int SIZE = (1 << 20) + 1;
	char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = obuf + SIZE - 1;
	char _st[55];
	int _qr = 0;

	inline char getchar() {
		return (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin),
		        (iS == iT ? EOF : *iS++) : *iS++);
	}
	inline void qread() {}
	template <typename T1, typename... T2>
	inline void qread(T1 &x, T2 &...ls) {
		x = 0;
		rg char ch = ' ';
		rg int ps = 1;
		while (!isdigit(ch) && ch != '-') ch = getchar();
		if (ch == '-') ps = -1, ch = getchar();
		while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
		x *= ps;
		qread(ls...);
	}

	inline void flush() {
		fwrite(obuf, 1, oS - obuf, stdout);
		oS = obuf;
		return;
	}
	inline void putchar(char _x) {
		*oS++ = _x;
		if (oS == oT) flush();
	}
	template <typename T>
	inline void qwrite(T x) {
		if (x < 0) putchar('-'), x = -x;
		if (x < 10) return putchar('0' + x), void();
		qwrite(x / 10), putchar('0' + (x % 10));
	}

	template <typename T>
	inline void qwrite(T x, char ch) {
		qwrite(x), putchar(ch);
	}
};  // namespace fastio

#ifndef ONLINE_JUDGE

void debug(const char *s) {
	cerr << s;
}
template <typename T1, typename... T2>
void debug(const char *s, const T1 x, T2... ls) {
	int p = 0;
	while (*(s + p) != '\0') {
		if (*(s + p) == '{' && *(s + p + 1) == '}') {
			cerr << x;
			debug(s + p + 2, ls...);
			return;
		}
		cerr << *(s + p++);
	}
}

#else
#define debug(...) void(0)
#endif

ll qpow(ll x, ll p, ll mod) {
	rg ll base = x, res = 1;
	while (p) {
		if (p & 1) res = (res * base) % mod;
		base = (base * base) % mod;
		p >>= 1;
	}
	return res;
}

const int N = (1 << 20) + 5;

int n;
char S[N];
int z[N];
int pre[N], suf[N], cnt1[26], cnt2[26];
int sum[N][28];
int presum[28];

void exKMP() {
	z[0] = n;
	int cur = 0;
	while(cur < n - 1 && S[cur] == S[cur+1]) cur++;
	z[1] = cur;
	int p = 0;
	rep(i, 2, n-1) {
		if(i + z[i-p] < p + z[p]) z[i] = z[i-p];
		else {
			cur = p + z[p] - i;
			while(cur + i < n && S[cur] == S[cur+1]) cur++;
			z[i] = cur, p = i;
		}
	}
}

void Solve() {
	scanf("%s", S+1);
	n = strlen(S+1);
	exKMP();
	memset(pre, 0, sizeof pre);
	memset(suf, 0, sizeof suf);
	memset(cnt1, 0, sizeof cnt1);
	memset(cnt2, 0, sizeof cnt2);
	rep(i, 1, n) {
		if(cnt1[S[i]-'a']) pre[i] = pre[i-1]-1;
		else pre[i] = pre[i-1]+1;
		cnt1[i] ^= 1;
	}
	per(i, 1, n) {
		if(cnt2[S[i]-'a']) suf[i] = suf[i+1]-1;
		else suf[i] = suf[i+1]+1;
		cnt2[i] ^= 1;
	}
	OK;
	per(i, 1, n) {
		rep(j, 0, 26) sum[i][j] = sum[i+1][j];
		sum[i][suf[i]]++;
	}
	ll ans = 0;
	rep(i, 1, n) {
		int x = i / z[i] + 1;
		ans += 1ll * (x/2) * i;
		rep(j, 0, 25) {
			ans += 1ll * ((x+1)/2) * sum[i+1][j] * presum[j];
		}
		rep(i, pre[i], 26) presum[i]++;
	}
	cout << ans << endl;
}

int main() {
	int t;
	scanf("%d", &t);
	while(t--) Solve();
	return 0;
}
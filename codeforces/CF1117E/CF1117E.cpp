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

const int N = 1e4 + 5;

int n, p, pos[N];
char S[N], S1[N], S2[N], S3[N], ans[N], T[N];
bitset<N> tar[3][27];

int main() {
	cin >> S + 1;
	n = strlen(S + 1);
	{
		rep(i, 1, n) S1[i] = (i % 26 + 'a');
		cout << "? " << S1+1 << endl;
		
		cin >> T + 1;
		rep(i, 1, n) tar[0][T[i]-'a'][i] = 1;
	}
	{
		rep(i, 1, n) S2[i] = ((i / 26) % 26 + 'a');
		cout << "? ";
		rep(i, 1, n) cout << S2[i]; cout << endl;
		fflush(stdout);
		
		cin >> T + 1;
		rep(i, 1, n) tar[1][T[i]-'a'][i] = 1;
	}
	{
		rep(i, 1, n) S3[i] = ((i / 26 / 26) % 26 + 'a');
		cout << "? ";
		rep(i, 1, n) cout << S3[i]; cout << endl;
		fflush(stdout);
		cin >> T + 1;
		rep(i, 1, n) tar[2][T[i]-'a'][i] = 1;
	}
	
	rep(i, 1, n) {
		int p = (tar[0][S1[i]-'a'] & tar[1][S2[i]-'a'] & tar[2][S3[i]-'a'])._Find_first();
		ans[i] = S[p];
	}
	cout << "! " << ans+1 << endl;
	fflush(stdout);
	return 0;
}
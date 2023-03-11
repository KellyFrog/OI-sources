
// Problem: P3966 [TJOI2013]单词
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3966?contestId=41161
// Memory Limit: 500 MB
// Time Limit: 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

/*
 * Codeforces @Chenkaifeng
 * Luogu @longer_name
 * AC自动机上DP（大概
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

const int N = 1e6 + 5;

int tot, rt;
int son[N][26], fail[N], fat[N], ch[N];
int cnt[N], pos[N];
int que[N], head = 1, tail;
int n;
string str[N];

void Insert(string s, int p) {
	if(rt == 0) rt = ++tot;
	int cur = rt;
	rep(i, 0, s.length()-1) {
		if(!son[cur][s[i]-'a']) son[cur][s[i]-'a'] = ++tot;
		fat[son[cur][s[i]-'a']] = cur;
		cur = son[cur][s[i]-'a'];
		ch[cur] = s[i];
		cnt[cur]++;
	}
	pos[p] = cur;
}

void BuildFail() {
	fail[rt] = rt;
	rep(i, 0, 25) {
		if(son[rt][i]) {
			fail[son[rt][i]] = rt;
			int cur = son[rt][i];
			rep(j, 0, 25) if(son[cur][j]) que[++tail] = son[cur][j];
		}
	}
	while(head <= tail) {
		int cur = que[head++];
		int curf = fail[fat[cur]];
		while(curf != rt && !son[curf][ch[cur]-'a']) curf = fail[curf];
		if(son[curf][ch[cur]-'a']) curf = son[curf][ch[cur]-'a'];
		fail[cur] = curf;
		rep(i, 0, 25) if(son[cur][i]) que[++tail] = son[cur][i];
	}
}

int main() {
	cin >> n;
	rep(i, 1, n) cin >> str[i], Insert(str[i], i);
	BuildFail();
	per(i, 1, tot) cnt[fail[que[i]]] += cnt[que[i]];
	rep(i, 1, n) cout << cnt[pos[i]] << "\n";
	return 0;
}
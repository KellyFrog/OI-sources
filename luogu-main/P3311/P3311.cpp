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
	template <typename T1>
	inline void qwrite(T1 x) {
		if (x < 0) putchar('-'), x = -x;
		if (x < 10) return putchar('0' + x), void();
		qwrite(x / 10), putchar('0' + (x % 10));
	}

	template <typename T1>
	inline void qwrite(T1 x, char ch) {
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

const int N = 2e3 + 5;

int son[N][11], fail[N], rt, tot, cnt[N], fat[N];
char ch[N];
ll dp[N][N][2];
char S[N], A[N];
int que[N], head=1, tail;
int n, m;

void Insert(char* str) {
	debug("str={} : ", str+1);
	int len = strlen(str + 1);
	if(rt == 0) rt = ++tot;
	int cur = rt;
	rep(i, 1, len) {
		if(!son[cur][str[i] - '0']) son[cur][str[i] - '0'] = ++tot;
		fat[son[cur][str[i] - '0']] = cur;
		cur = son[cur][str[i] - '0'];
		ch[cur] = str[i];
		debug("{} ", cur);
	}
	debug("\n");
	cnt[cur]++;
}

void BuildFail() {
	fail[rt] = rt;
	rep(i, 0, 9) {
		if(son[rt][i]) {
			fail[son[rt][i]] = rt;
			que[++tail] = son[rt][i];
		} else {
			son[rt][i] = rt;
		}
	}
	while(head <= tail) {
		int cur = que[head++];
		rep(i, 0, 9) {
			if(son[cur][i]) {
				que[++tail] = son[cur][i];
				fail[son[cur][i]] = son[fail[cur]][i];
			} else {
				son[cur][i] = son[fail[cur]][i];
			}
		}
	}
}

const ll mod = 1e9 + 7;

int main() {
	scanf("%s", S+1);
	n = strlen(S+1);
	scanf("%d", &m);
	rep(i, 1, m) {
		scanf("%s", A+1);
		Insert(A);
	}
	BuildFail();
	rep(i, 1, tot) {
		debug("fail[{}] = {} end={} son: ", i, fail[i], cnt[i]);
		rep(j, 0, 9) debug("{} ", son[i][j]); debug("\n");
	}
	rep(i, 1, tot) cnt[que[i]] += cnt[fail[que[i]]];
	dp[0][1][0] = 1;
	son[rt][0] = rt;
	rep(i, 0, n-1) {
		rep(j, 1, tot) {
			debug("dp[{}][{}] = {},{}\n", i, j, dp[i][j][0], dp[i][j][1]);
			if(cnt[j]) continue;
			rep(k, 0, 9) {
				if(cnt[son[j][k]]) continue;
				debug("-> {} {}\n", k, son[j][k]);
				if(k == S[i+1] - '0') (dp[i+1][son[j][k]][0] += dp[i][j][0]) %= mod;
				if(k < S[i+1] - '0') (dp[i+1][son[j][k]][1] += dp[i][j][0]) %= mod;
				(dp[i+1][son[j][k]][1] += dp[i][j][1]) %= mod;
			}
		}
	}
	ll ans = 0;
	rep(i, 1, tot) {
		(ans += dp[n][i][0] + dp[n][i][1]) %= mod;
	}
	cout << (ans-1+mod)%mod << endl;
	return 0;
}

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

const int N = 5e5 + 5;

vector<int> adj[N];
int anc[N][21], dep[N];

void Dfs(int u, int fa) {
	dep[u] = dep[fa] + 1;
	anc[u][0] = fa;
	rep(i, 1, 20) anc[u][i] = anc[anc[u][i-1]][i-1];
	for(int v : adj[u]) {
		if(v != fa) Dfs(v, u);
	}
}

pair<pair<int, int>, int> cur[N], tmp[N];
int cnt[N], m = 5e5;
int rk[N], sa[N];
int a[N];
int n;
char S[N];
int ans[N];

void RSort() {
	memset(cnt, 0, sizeof cnt);
	rep(i, 1, n) cnt[cur[i].fi.se]++;
	rep(i, 1, m) cnt[i] += cnt[i-1];
	per(i, 1, n) tmp[cnt[cur[i].fi.se]--] = cur[i];
	rep(i, 1, n) cur[i] = tmp[i];
	
	memset(cnt, 0, sizeof cnt);
	rep(i, 1, n) cnt[cur[i].fi.fi]++;
	rep(i, 1, m) cnt[i] += cnt[i-1];
	per(i, 1, n) tmp[cnt[cur[i].fi.fi]--] = cur[i];
	rep(i, 1, n) cur[i] = tmp[i];
	
	int p = 1;
	rk[cur[1].se] = 1;
	rep(i, 2, n) {
		if(cur[i].fi != cur[i-1].fi) p++;
		rk[cur[i].se] = p;
		ans[cur[i].se] = i;
	}
	
	rep(i, 1, n) cerr << rk[i] << " \n"[i == n];
}

void SA() {
	rep(i, 1, n) rk[i] = a[i];
	for(int i = 1; (1 << i-1) <= n; i++) {
		debug("len={}\n", i);
		rep(j, 1, n) {
			cur[j] = mp(mp(rk[j], rk[anc[j][i-1]]), j);
			debug("[{}] {} {} {}\n", j, rk[j], rk[anc[j][i-1]], j);
		}
		RSort();
	}
	int p = 0;
	rep(i, 1, n) rk[cur[i].se] = ++p;
	rep(i, 1, n) sa[rk[i]] = i;
}

int main() {
	scanf("%d", &n);
	rep(i, 2, n) {
		int x; scanf("%d", &x);
		adj[x].pb(i);
	}
	scanf("%s", S+1);
	rep(i, 1, n) a[i] = S[i] - 'a' + 1;
	Dfs(1, 0);
	SA();
	rep(i, 1, n) sa[ans[i]] = i;
	rep(i, 1, n) printf("%d ", sa[i]); puts("");
	return 0;
}
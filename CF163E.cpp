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

const int N = 1e6 + 5;

int son[N][26], fail[N], rt, tot, cnt[N], fat[N];
char ch[N];
string a[N];
int que[N], head=1, tail;
int n, q;
vector<int> adj[N];
int pos[N];

int Insert(string str) {
	int len = str.length() - 1;
	if(rt == 0) rt = ++tot;
	int cur = rt;
	rep(i, 0, len) {
		if(!son[cur][str[i] - 'a']) son[cur][str[i] - 'a'] = ++tot;
		fat[son[cur][str[i] - 'a']] = cur;
		cur = son[cur][str[i] - 'a'];
		ch[cur] = str[i];
	}
	cnt[cur]++;
	return cur;
}

int Get(string str) {
	int len = str.length() - 1;
	int cur = rt;
	rep(i, 0, len) {
		if(!son[cur][str[i] - 'a']) return cur;
		cur = son[cur][str[i] - 'a'];
	}
	return cur;
}

void BuildFail() {
	fail[rt] = rt;
	rep(i, 0, 25) {
		if(son[rt][i]) {
			fail[son[rt][i]] = rt;
			que[++tail] = son[rt][i];
		} else {
			son[rt][i] = rt;
		}
	}
	while(head <= tail) {
		int cur = que[head++];
		rep(i, 0, 25) {
			if(son[cur][i]) {
				que[++tail] = son[cur][i];
				fail[son[cur][i]] = son[fail[cur]][i];
			} else {
				son[cur][i] = son[fail[cur]][i];
			}
		}
	}
	rep(i, 2, tot) adj[fail[i]].pb(i);
}

int sum[N];

int lowbit(int x) {
	return x & (-x);
}

void Add(int x, int p) {
	while(x <= tot) {
		sum[x] += p;
		x += lowbit(x);
	}
}

void Add(int l, int r, int p) {
	debug("add [{}, {}] {}\n", l, r, p);
	Add(l, p);
	Add(r+1, -p);
}

int Sum(int x) {
	int res = 0, x0 = x;
	while(x) {
		res += sum[x];
		x -= lowbit(x);
	}
	debug("sumed {} = {}\n", x0, res);
	return res;
}

int dfn[N], siz[N], dfncnt;

void Dfs(int u, int fa) {
	debug("dfs={} {}\n", u, fa);
	dfn[u] = ++dfncnt;
	siz[u] = 1;
	for(int v : adj[u]) {
		if(v != fa) Dfs(v, u), siz[u] += siz[v];
	}
}

void Solve(string str) {
	int cur = rt;
	ll ans = 0;
	rep(i, 0, str.length()-1) {
		cur = son[cur][str[i] - 'a'];
		ans += Sum(dfn[cur]);
	}
	printf("%d\n", ans);
}

bool vis[N];

int main() {
	cin >> q >> n;
	rep(i, 1, n) cin >> a[i], pos[i] = Insert(a[i]);
	BuildFail();
	Dfs(1, 0);
	rep(i, 1, n) Add(dfn[pos[i]], dfn[pos[i]] + siz[pos[i]] - 1, 1);
	rep(i, 1, tot) {
		debug("fail[{}] = {} {}\nson = ", i, fail[i], ch[i]);
		rep(j, 0, 25) debug("{} ", son[i][j]); debug("\n");
	}
	while(q--) {
		char op;
		cin >> op;
		if(op == '+') {
			int x;
			cin >> x;
			if(!vis[x]) continue;
			vis[x] = 0;
			debug("pos={} {} {}\n", pos[x]);
			Add(dfn[pos[x]], dfn[pos[x]] + siz[pos[x]] - 1, 1);
		} else if(op == '-') {
			int x;
			cin >> x;
			if(vis[x]) continue;
			vis[x] = 1;
			debug("pos={}\n", pos[x]);
			Add(dfn[pos[x]], dfn[pos[x]] + siz[pos[x]] - 1, -1);
		} else {
			string str;
			cin >> str;
			Solve(str);
		}
	}
	return 0;
}
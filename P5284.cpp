// Problem: P5284 [十二省联考2019]字符串问题
// Contest: Luogu
// Author: chenkaifeng
// 
// 
// Powered by CP Editor (https://cpeditor.org)

/*
 * Author: chenkaifeng @BDFZ
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

#if __cplusplus < 201703L
#define register
#else
#define rg
#endif

#define mp make_pair
#define pb push_back
#define pf push_front

#define rep(i, s, t) for (int i = s; i <= t; i++)
#define per(i, s, t) for (int i = t; i >= s; i--)
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
		char ch = ' ';
		int ps = 1;
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

const ll mod = 1e9 + 7;
// const ll mod = 1e9 + 9;
// const ll mod = 19260817;
// const ll mod = 998244353;
// const int mod =2017;

template <typename T>
inline void chkadd(T& x, T y) {
	x = x + y >= mod ? x + y - mod : x + y;
}
template <typename T>
inline void chkadd(T& x, T y, T z) {
	x = y + z >= mod ? y + z - mod : y + z;
}
template <typename T>
inline void chkmns(T& x, T y) {
	x = x - y < 0 ? x - y + mod : x - y;
}
template <typename T>
inline void chkmns(T& x, T y, T z) {
	x = y - z < 0 ? y - z + mod : y - z;
}
template <typename T>
inline void chkmax(T& x, T y) {
	x = x < y ? y : x;
}
template <typename T>
inline void chkmax(T& x, T y, T z) {
	x = y > z ? y : z;
}
template <typename T>
inline void chkmin(T& x, T y) {
	x = x < y ? x : y;
}
template <typename T>
inline void chkmin(T& x, T y, T z) {
	x = y < z ? y : z;
}

ll qpow(ll x, ll p) {
	ll base = x, res = 1;
	while (p) {
		if (p & 1) res = (res * base) % mod;
		base = (base * base) % mod;
		p >>= 1;
	}
	return res;
}

/* template ends here */

const int N = 2e5 + 5;

int tid[N *50], lson[N *50], rson[N *50], tot, tcnt, nodecnt;
int head[N*50], nxt[N*100], to[N*100], wgt[N*100], dtot;
int dhead[N*50], dnxt[N*100], dto[N*100], dwgt[N*100];
int aid[N], bid[N];
int seq[N<<1], la[N], ra[N], lb[N], rb[N], na, nb, n, m;
char s[N];
int sa[N], rk[N], h[N], st[21][N], lg2[N];
pair<pair<int, int>, int> cur[N], tmp[N];
int stk[N*50], top;
int dfn[N*50], low[N*50], scc[N*50], ins[N*50], dfncnt, scccnt;
ll ans = 0;
ll f[N*50]; int ind[N*50];

inline void addedge(int u, int v, int w) {
	if(u == 0 || v == 0) return;
	nxt[++tot] = head[u];
	to[tot] = v;
	wgt[tot] = w;
	head[u] = tot;
}

inline void daddedge(int u, int v, int w) {
	dnxt[++dtot] = dhead[u];
	dto[dtot] = v;
	dwgt[dtot] = w;
	dhead[u] = dtot;
}

inline void add(int& cur, int old, int p, int v, int w, int l, int r) {
	cur = ++tcnt;
	tid[cur] = ++nodecnt;
	addedge(tid[cur], tid[old], 0);
	lson[cur] = lson[old];
	rson[cur] = rson[old];
	if(l == r) {
		addedge(tid[cur], v, w);
		return;
	}
	int mid = l + r >> 1;
	if(p <= mid) add(lson[cur], lson[old], p, v, w, l, mid), addedge(tid[cur], tid[lson[cur]], 0);
	else add(rson[cur], rson[old], p, v, w, mid + 1, r), addedge(tid[cur], tid[rson[cur]], 0);
}

inline void connect(int cur, int nd, int w, int ql, int qr, int l, int r) {
	if(!cur) return;
	if(ql <= l && r <= qr) return addedge(nd, tid[cur], w);
	int mid = l + r >> 1;
	if(ql <= mid) connect(lson[cur], nd, w, ql, qr, l, mid);
	if(mid < qr) connect(rson[cur], nd, w, ql, qr, mid + 1, r);
}

int oldrk[N<<1], id[N], px[N], cnt[N];
inline bool cmp(int x, int y, int w) {
	return oldrk[x] == oldrk[y] && oldrk[x+w] == oldrk[y+w];
}
void SA() {	
	int i, m = 300, p, w;
	
	memset(cnt, 0, sizeof cnt);
	
	for (i = 1; i <= n; ++i) ++cnt[rk[i] = s[i]];
	for (i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
	for (i = n; i >= 1; --i) sa[cnt[rk[i]]--] = i;

	for (w = 1;; w <<= 1, m = p) {
		for (p = 0, i = n; i > n - w; --i) id[++p] = i;
		for (i = 1; i <= n; ++i)
			if (sa[i] > w) id[++p] = sa[i] - w;
		memset(cnt, 0, sizeof(cnt));
		for (i = 1; i <= n; ++i) ++cnt[px[i] = rk[id[i]]];
		for (i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
		for (i = n; i >= 1; --i) sa[cnt[px[i]]--] = id[i];
		memcpy(oldrk, rk, sizeof(rk));
		for (p = 0, i = 1; i <= n; ++i)
			rk[sa[i]] = cmp(sa[i], sa[i - 1], w) ? p : ++p;
		if (p == n) {
			for (int i = 1; i <= n; ++i) sa[rk[i]] = i;
			break;
		}
	}
}

inline void buildheight() {
	int p = 0;
	rep(i, 1, n) {
		if(p) p--;
		while(i+p <= n && sa[rk[i]-1]+p <= n && s[i+p] == s[sa[rk[i]-1]+p]) p++;
		h[rk[i]] = p;
	}
}

inline void buildST() {
	rep(i, 1, n) st[0][i] = h[i];
	rep(j, 1, 20) rep(i, 1, n) {
		if(i + (1 << j) - 1 > n) break;
		chkmin(st[j][i], st[j-1][i], st[j-1][i+(1<<j-1)]);
	}
	lg2[0] = -1;
	rep(i, 1, n) lg2[i] = lg2[i>>1] + 1;
}

inline int queryST(int l, int r) {
	return min(st[lg2[r-l+1]][l], st[lg2[r-l+1]][r-(1<<lg2[r-l+1])+1]);
}

inline int lcp(int x, int y) {
	x = rk[x], y = rk[y];
	if(x == y) return n + 1;
	if(x > y) swap(x, y);
	return queryST(x+1, y);
}

inline void tarjan(int u) {
	ins[stk[++top] = u] = 1;
	dfn[u] = low[u] = ++dfncnt;
	for(int e = head[u]; e; e = nxt[e]) {
		int v = to[e];
		if(!dfn[v]) {
			tarjan(v);
			chkmin(low[u], low[v]);
		} else if(ins[v]) {
			chkmin(low[u], low[v]);
		}
	}
	if(dfn[u] == low[u]) {
		int p = top;
		while(stk[p] != u) p--;
		scccnt++;
		rep(i, p, top) {
			scc[stk[i]] = scccnt;
			ins[stk[i]] = 0;
		}
		rep(i, p, top) {
			int u = stk[i];
			for(int e = head[u]; e; e = nxt[e]) {
				int v = to[e], w = wgt[e];
				if(w && scc[u] == scc[v]) ans = -2;
			}
		}
		top = p-1;
	}
}

inline void getrange(int s, int len, int& resL, int& resR) {
	int p = rk[s];
	resL = resR = p;
	{
		int L = 1, R = p-1;
		while(L <= R) {
			int mid = L + R >> 1;
			if(lcp(s, sa[mid]) >= len) resL = mid, R = mid - 1;
			else L = mid + 1;
		}
	}
	{
		int L = p+1, R = n;
		while(L <= R) {
			int mid = L + R >> 1;
			if(lcp(s, sa[mid]) >= len) resR = mid, L = mid + 1;
			else R = mid - 1;
		}
	}
}

inline void topo() {
	rep(u, 1, nodecnt) {
		for(int e = head[u]; e; e = nxt[e]) {
			int v = to[e], w = wgt[e];
			if(scc[u] != scc[v]) daddedge(scc[u], scc[v], w), ind[scc[v]]++;
		}
	}
	static int que[N*50]; int head = 1, tail = 0;
	rep(i, 1, scccnt) if(ind[i] == 0) que[++tail] = i;
	while(head <= tail) {
		int u = que[head++];
		for(int e = dhead[u]; e; e = dnxt[e]) {
			int v = dto[e], w = dwgt[e];
			chkmax(f[v], f[u] + w);
			if(--ind[v] == 0) que[++tail] = v;
		}
	}
}

inline void solve() {
	scanf("%s", s+1);
	n = strlen(s+1);
	
	scanf("%d", &na);
	rep(i, 1, na) scanf("%d%d", &la[i], &ra[i]);
	scanf("%d", &nb);
	rep(i, 1, nb) scanf("%d%d", &lb[i], &rb[i]);
	
	rep(i, 1, na) aid[i] = ++nodecnt;
	rep(i, 1, nb) bid[i] = ++nodecnt;
	
	scanf("%d", &m);
	rep(i, 1, m) {
		int x, y;
		scanf("%d%d", &x, &y);
		addedge(aid[x], bid[y], 0);
	}
	
	SA();
	buildheight();
	buildST();
	
	rep(i, 1, na) seq[i] = i;
	rep(i, 1, nb) seq[i+na] = -i;
	
	sort(seq + 1, seq + 1 + na + nb, [](const int& i, const int& j) {
		int len1 = i>0 ? ra[i]-la[i] : rb[-i]-lb[-i];
		int len2 = j>0 ? ra[j]-la[j] : rb[-j]-lb[-j];
		return len1 == len2 ? i>j : len1 > len2;
	} );
	
	int lastrt = 0;
	
	rep(i, 1, na + nb) {
		if(seq[i] > 0) {
			int p = seq[i];
			int L = la[p], R = ra[p];
			add(lastrt, lastrt, rk[L], aid[p], R - L + 1, 1, (int)1e7);
		} else {
			int p = -seq[i];	
			int L = lb[p], R = rb[p];
			int LL = -1, RR = -1;
			getrange(L, R-L+1, LL, RR);
			connect(lastrt, bid[p], 0, LL, RR, 1, (int)1e7);
		}
	}
	
	ans = -1;
	rep(i, 1, nodecnt) if(!dfn[i]) tarjan(i);
	if(ans == -2) {
		printf("%d\n", -1);
	} else {
		topo();
		rep(i, 1, nodecnt) chkmax(ans, f[i]);
		printf("%lld\n", ans);
	}
	
	rep(i, 1, nodecnt) head[i] = dhead[i] = 0, tid[i] = lson[i] = rson[i] = 0;
	rep(i, 1, n) sa[i] = rk[i] = h[i] = 0;
	rep(i, 1, nodecnt) ind[i] = dfn[i] = low[i] = scc[i] = f[i] = 0;
	top = tcnt = dtot = tot = scccnt = dfncnt = nodecnt = 0;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	
	int t;
	scanf("%d", &t);
	while(t--) solve();
	
	return 0;
}
#ifndef LOCAL_RUN
	#define NDEBUG
#endif
#ifdef GNU_DEBUG
	#define _GLIBCXX_DEBUG 1
	#define _GLIBCXX_DEBUG_PEDANTIC 1
	#define _GLIBCXX_SANITIZE_VECTOR 1
#endif
#include <bits/stdc++.h>
namespace {
#define mset(a, b) memset(&a, b, sizeof(a))
#define ALL(v) std::begin(v), std::end(v)
#define RANGE(a, l, r) (std::begin(a) + (l)), (std::begin(a) + ((r) + 1))
#define fir(i, a, b, ...) for (int i = (a), ##__VA_ARGS__; i <= (b); ++i)
#define firr(i, a, b, ...) for (int i = (a), ##__VA_ARGS__; i >= (b); --i)
#ifdef LOCAL_RUN
	template<class T> void dbgpr(const T& x) {std::cerr << x << std::endl;}
	template<class T, class... Args> void dbgpr(const T& x, const Args&... args) {std::cerr << x << ", ", dbgpr(args...);}
	template<class... Args> void dbgprint(const char* s, const Args&... args) {std::cerr << s << " = ", dbgpr(args...);}
	#define debug(...) dbgprint(#__VA_ARGS__, __VA_ARGS__)
	#define DEBUG if (true)
#else
	#define debug(...) void()
	#define DEBUG if (false)
#endif
typedef long long LL;
typedef long double LD;
typedef unsigned long long ULL;
template<class T1, class T2> bool cmax(T1& a, const T2& b) {return a < b ? a = b, true : false;}
template<class T1, class T2> bool cmin(T1& a, const T2& b) {return b < a ? a = b, true : false;}
using namespace std;

const LL INF = 0x3F3F3F3F3F3F3F3FLL;
const int MOD = 998244353;
const int MAXN = 3e5 + 5;
const int LOGN = 25;

LL sqr(LL x) {return x * x;}

int n, m, lgn;
array<vector<int>, MAXN> e;

array<int, MAXN> fa, dep, sz, dfn, seq;
void dfs_pre(int u, int f, int&& tot) {
	fa[u] = f, dep[u] = dep[f] + 1;
	seq[dfn[u] = ++tot] = u;
	sz[u] = 1;
	for (auto& v : e[u]) if (v != f) {
		dfs_pre(v, u, (int&&)tot), sz[u] += sz[v];
	}
}
bool inside(int u, int anc) {
	return dfn[anc] <= dfn[u] && dfn[u] < dfn[anc] + sz[anc];
}
namespace LCA {
	array<array<int, MAXN>, LOGN> f;
	int upper(int x, int y) {return dep[x] < dep[y] ? x : y;}
	void build() {
		copy(RANGE(seq, 0, n), f[0].begin());
		fir (pw, 1, lgn) {
			fir (i, 1, n - (1 << pw) + 1) {
				f[pw][i] = upper(f[pw - 1][i], f[pw - 1][i + (1 << (pw - 1))]);
			}
		}
	}
}
int getlca(int u, int v) {
	using namespace LCA;
	if (u == v) return u;
	tie(u, v) = minmax(dfn[u], dfn[v]), u++;
	int k = __lg(v - u + 1);
	return fa[upper(f[k][u], f[k][v - (1 << k) + 1])];
}

array<vector<tuple<int, int, LL>>, MAXN> chain;

namespace BIT {
	array<LL, MAXN> c;
	void add(int x, LL y) {
		for (; x <= n; x += x & -x) c[x] += y;
	}
	LL sum(int x) {
		LL ans = 0;
		for (; x; x -= x & -x) ans += c[x];
		return ans;
	}
}
void chgadd(int u, LL x) {
	BIT::add(dfn[u], x);
	BIT::add(dfn[u] + sz[u], -x);
}
LL qrysum(int u) {
	return BIT::sum(dfn[u]);
}

array<LL, MAXN> sum, f;
void dfs_f(int u) {
	for (auto& v : e[u]) if (v != fa[u]) {
		dfs_f(v), sum[u] += f[v];
	}
	f[u] = sum[u];
	for (auto& tmp : chain[u]) {
		auto& x = get<0>(tmp); auto& y = get<1>(tmp); auto& w = get<2>(tmp);
		w += sum[u] - qrysum(x) - qrysum(y);
		cmax(f[u], w);
	}
	chgadd(u, f[u] - sum[u]);
	// debug(u, f[u]);
}

namespace SGT {
	const int MAXT = 4 * ::MAXN;
	const int MAXN = -1;
	array<LL, MAXT> mx;
	#define ls (p << 1)
	#define rs (ls | 1)
	void pushup(int p) {
		mx[p] = max(mx[ls], mx[rs]);
	}
	void build(int p, int fl, int fr) {
		if (fl == fr) return mx[p] = -INF, void();
		int mid = (fl + fr) / 2;
		build(ls, fl, mid);
		build(rs, mid + 1, fr);
		pushup(p);
	}
	void chgmx(int p, int fl, int fr, int x, LL y) {
		if (fl == fr) return cmax(mx[p], y), void();
		int mid = (fl + fr) / 2;
		if (x <= mid) chgmx(ls, fl, mid, x, y);
		else chgmx(rs, mid + 1, fr, x, y);
		pushup(p);
	}
	LL qrymx(int p, int fl, int fr, int L, int R) {
		if (L > R) return -INF;
		if (L <= fl && fr <= R) return mx[p];
		int mid = (fl + fr) / 2; LL ans = -INF;
		if (L <= mid) ans = qrymx(ls, fl, mid, L, R);
		if (mid < R) cmax(ans, qrymx(rs, mid + 1, fr, L, R));
		return ans;
	}
	#undef ls
	#undef rs
}

array<LL, MAXN> g;
void dfs_g(int u) {
	for (auto& tmp : chain[u]) {
		auto& w = get<2>(tmp);
		w += g[u];
	}
	sort(ALL(chain[u]), [](auto& a, auto& b) {return get<2>(a) > get<2>(b);});
	for (auto& v : e[u]) if (v != fa[u]) {
		LL r1 = sum[u] + g[u];
		LL r2 = SGT::qrymx(1, 1, n, dfn[u], dfn[v] - 1);
		LL r3 = SGT::qrymx(1, 1, n, dfn[v] + sz[v], dfn[u] + sz[u] - 1);
		LL r4 = [u, v] {
			for (auto& tmp : chain[u]) {
				auto& x = get<0>(tmp); auto& y = get<1>(tmp); auto& w = get<2>(tmp);
				if (!inside(x, v) && !inside(y, v)) return w;
			}
			return -INF;
		}();
		g[v] = max({r1, r2, r3, r4}) - f[v];
	}
	for (auto& tmp : chain[u]) {
		auto& x = get<0>(tmp); auto& y = get<1>(tmp); auto& w = get<2>(tmp);
		SGT::chgmx(1, 1, n, dfn[x], w);
		SGT::chgmx(1, 1, n, dfn[y], w);
	}
	for (auto& v : e[u]) if (v != fa[u]) {
		dfs_g(v);
	}
	// debug(u, g[u]);
}

LL ans;

void dfs_ans(int u) {
	LL all = 0;
	for (auto& v : e[u]) if (v != fa[u]) {
		all += sqr(sz[v]);
	}
	for (auto& v : e[u]) if (v != fa[u]) {
		LL cnt = sqr(n - sz[v]) - (all - sqr(sz[v])) - sqr(n - sz[u]);
		ans += (cnt % MOD) * (f[v] % MOD) % MOD;
	}
	LL cnt = sqr(sz[u]) - all;
	ans += (cnt % MOD) * (g[u] % MOD) % MOD;
	for (auto& v : e[u]) if (v != fa[u]) {
		dfs_ans(v);
	}
}

void realmain() {
	DEBUG freopen("emotion.in", "r", stdin);
	// freopen("emotion.out", "w", stdout);
	scanf("%d %d", &n, &m), lgn = __lg(n) + 1;
	fir (i, 2, n, u, v) scanf("%d %d", &u, &v), e[u].push_back(v), e[v].push_back(u);

	dfs_pre(1, 0, 0);
	LCA::build();

	fir (i, 1, m, u, v, w) scanf("%d %d %d", &u, &v, &w), chain[getlca(u, v)].emplace_back(u, v, w);

	dfs_f(1);

	SGT::build(1, 1, n);
	dfs_g(1);

	dfs_ans(1);

	ans %= MOD;
	ans = ((LL)n * n % MOD) * (f[1] % MOD) % MOD - ans;
	if (ans < 0) ans += MOD;
	assert(0 <= ans && ans < MOD);
	printf("%d\n", (int)ans);
}}
signed main(){return realmain(),0;}

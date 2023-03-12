#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 100005;
int head[maxn], nxt[maxn << 1], to[maxn << 1], hp = 1;
int label[maxn], ban[maxn];

inline void add(int u, int v) {
	nxt[++ hp] = head[u];
	head[u] = hp;
	to[hp] = v;
}

void dfs(int u, int fa) {
	int t = 0;
	for(int i = head[u]; i; i = nxt[i])
		if(to[i] != fa) {
			dfs(to[i], u);
			t |= ban[u] & ban[to[i]];
			ban[u] |= ban[to[i]];
		}

	int k = t ? 32 - __builtin_clz(unsigned(t)) : 0;
	label[u] = __builtin_ctz(unsigned((ban[u] | ((1 << k) - 1)) + 1));
	ban[u] = (ban[u] >> label[u] | 1) << label[u];
	/* debug("%d : %d %d (%d)\n", u, label[u], ban[u], t); */
}

int main() {
	int n = read;

	for(int i = 1; i < n; i ++) {
		int u = read, v = read;
		add(u, v);
		add(v, u);
	}

	dfs(1, 0);

	int ans = 0;
	for(int i = 1; i <= n; i ++)
		ans = std::max(ans, label[i]);
	printf("%d\n", ans);
}

#include <bits/stdc++.h>

using namespace std;

#define vc vector
#define pq priority_queue
#define grt greater
#define pb push_back
#define mp make_pair
#define rg register
#define fi first
#define se second
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef grt<int> gi;
typedef grt<ll> gll;
typedef grt<pii> gii;
typedef grt<pll> gpll;

namespace IO {
	const int SIZE = (1 << 20) + 1;
	char ibuf[SIZE], *iS, *iT, obuf[SIZE],*oS = obuf, *oT = obuf + SIZE - 1;
	char _st[55];
	int _qr = 0;
#ifdef ONLINE_JUDGE
	inline char gc() {
		return (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS++) : *iS++);
	}
#else
#define gc getchar
#endif
	inline void qread() {}
	template<class T1, class ...T2>
	inline void qread(T1 &IEE, T2&... ls) {
		rg T1 __ = 0, ___ = 1;
		rg char ch;
		while(!isdigit(ch = gc())) ___ = (ch == '-') ? -___ : ___;
		do {
			__ = (__ << 1) + (__ << 3) + (ch ^ 48);
		} while(isdigit(ch = gc()));
		__ *= ___;
		IEE = __;
		qread(ls...);
		return ;
	}
	template<class T>
	inline void qreadarr(T beg, T end) {
		while(beg != end) {
			qread(*beg);
			beg++;
		}
	}
	inline void flush() {
		fwrite(obuf, 1, oS - obuf, stdout);
		oS = obuf;
		return ;
	}
#ifdef ONLINE_JUDGE
	inline void putc_(char _x) {
		*oS++ = _x;
		if(oS == oT) flush();
	}
#else
#define putc_ putchar
#endif
	inline void qwrite() {}
	template<class T1, class ...T2>
	inline void qwrite(T1 IEE, T2... ls) {
		if(!IEE) putc_('0');
		if(IEE < 0) putc_('-'), IEE = -IEE;
		while(IEE) _st[++_qr] = IEE % 10 + '0', IEE /= 10;
		while(_qr) putc_(_st[_qr--]);
		qwrite(ls...);
		return ;
	}
	inline void putstr_(const char* IEE) {
		int p = 0;
		while(IEE[p] != '\0') {
			putc_(IEE[p++]);
		}
	}
	inline void puts_(const char* IEE) {
		putstr_(IEE);
		putc_('\n');
	}
	template<class T>
	inline void qwritearr(T beg, T end, const char * IEE = {" "}, const char * EE = {"\n"}) {
		while(beg != end) {
			qwrite(*beg);
			beg++;
			putstr_(IEE);
		}
		putstr_(EE);
	}
	struct Flusher_ {
		~Flusher_() {
			flush();
		}
	} io_flusher;
}
using namespace IO;

#define rep(i, s, t) for(rg int (i) = s; (i) <= t; (i)++)
#define per(i, s, t) for(rg int (i) = t; (i) >= s; (i)--)
#define all(x) x.begin(), x.end()
#define allrev(x) x.rbegin(), x.rend()

/*templates end here*/

const int N = 1e4 + 5;

int head[N], to[N << 1], nxt[N << 1], weight[N << 1], tot;
int fa[N][20], dep[N]; ll dis[N];
int n;
char cmd[15];

void AddEdge(int u, int v, int w) {
	nxt[++tot] = head[u];
	to[tot] = v;
	weight[tot] = w;
	head[u] = tot;
}

void Dfs(int u, int f, int wgt) {
	dep[u] = dep[f] + 1;
	fa[u][0] = f;
	dis[u] = dis[f] + wgt;
	rep(i, 1, 18) fa[u][i] = fa[fa[u][i-1]][i-1];
	for(rg int i = head[u]; i; i = nxt[i]) {
		rg int v = to[i], w = weight[i];
		if(v != f) Dfs(v, u, w);
	}
}

int LCA(int x, int y) {
	if(dep[x] < dep[y]) swap(x, y);
	per(i, 0, 18) if(dep[fa[x][i]] >= dep[y]) x = fa[x][i];
	if(x == y) return x;
	per(i, 0, 18) if(fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
	return fa[x][0];
}

ll Dis(int x, int y) {
	rg int lca = LCA(x, y);
	return dis[x] + dis[y] - 2 * dis[lca];
}

int Kth(int x, int y, int k) {
	int lca = LCA(x, y);
	if(dep[x] - dep[lca] + 1 < k) {
		k -= dep[x] - dep[lca] + 1;
		k = dep[y] - dep[lca] - k;
		per(i, 0, 19) if(k >= (1 << i)) y = fa[y][i], k -= (1 << i);
		return y;
	} else {
		k--;
		per(i, 0, 19) if(k >= (1 << i)) x = fa[x][i], k -= (1 << i);
		return x;
	}
}

void Solve() {
	memset(head, 0, sizeof head); tot = 0;
	scanf("%d", &n);
	rep(i, 1, n-1) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		AddEdge(u, v, w), AddEdge(v, u, w);
	}
	Dfs(1, 0, 0);
	int x, y, k;
	while(1) {
		scanf("%s", cmd);
		if(cmd[1] == 'O') return;
		if(cmd[0] == 'D') scanf("%d%d", &x, &y), printf("%lld\n", Dis(x, y));
		else scanf("%d%d%d", &x, &y, &k), printf("%d\n", Kth(x, y, k));
	}
}

int main() {
	int t; scanf("%d", &t);
	while(t--) Solve();
	return 0;
}

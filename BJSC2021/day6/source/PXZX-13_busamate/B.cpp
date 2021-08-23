#include <bits/stdc++.h>

using namespace std;

template <typename T> void inline read(T &x) {
	x = 0; int f = 1; char s = getchar();
	while (s < '0' && s > '9') { if (s == '-') f = -1; s = getchar(); }
	while (s >= '0' && s <= '9') x = x * 10 + s - '0', s = getchar();
	x *= f;
}

template <typename T> void inline chkMax(T &x, T y) { if (y > x) x = y; }
template <typename T> void inline chkMin(T &x, T y) { if (y < x) x = y; }

typedef long long LL;

#define pb push_back
#define fi first
#define se second
#define mp make_pair

const int N = 4e5 + 5, L = 19;

typedef unsigned long long ULL;

int n, ep[N];

ULL rd[N];

char s[N];

int idx = 1, last = 1;

struct SAM{
	int ch[26], len, link;
} t[N];

void inline insert(int c, int i) {
	int x = ++idx, p = last; t[x].len = t[p].len + 1;
	while (p && !t[p].ch[c]) t[p].ch[c] = x, p = t[p].link;
	if (!p) t[x].link = 1;
	else {
		int q = t[p].ch[c];
		if (t[p].len + 1 == t[q].len) t[x].link = q;
		else {
			int y = ++idx; t[y] = t[q]; t[y].len = t[p].len + 1;
			while (p && t[p].ch[c] == q) t[p].ch[c] = y, p = t[p].link;
			t[q].link = t[x].link = y;
		}
	} 
	last = x;
	ep[i] = x;
}

vector<int> e[N];

typedef pair<int, int> PII;

vector<int> q[N];



int sz[N], dfn[N], dfncnt, fa[N][L];

void dfs(int u) {
	dfn[u] = ++dfncnt;
	sz[u] = 1;
	for (int i = 1; i < L; i++) fa[u][i] = fa[fa[u][i - 1]][i - 1];
	for (int i = 0; i < e[u].size(); i++) {
		int v = e[u][i];
		fa[v][0] = u;
 		dfs(v);
		sz[u] += sz[v];
	}
	int L = t[t[u].link].len + 1, R = t[u].len;
	for (int i = L; i <= R; i++) q[i].pb(u);
}

int c[N], d[N];

LL ans;

void inline add(int x, int k) {
	for (; x <= idx; x += x & -x) c[x] += k;
}

int inline ask(int x) {
	int res = 0;
	for (; x; x -= x & -x) res += c[x];
	return res;
}

int inline get(int u) {
	return ask(dfn[u] + sz[u] - 1) - ask(dfn[u] - 1);
}

int main() {
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
	read(n); scanf("%s", s + 1);
	reverse(s + 1, s + 1 + n);
	for (int i = 1; i <= n; i++) insert(s[i] - 'a', i), rd[i] = (LL)rand() * rand();	
	for (int i = 2; i <= idx; i++) e[t[i].link].pb(i);
	dfs(1);
	for (int i = n; i >= 2; i--) {
		add(dfn[ep[i]], 1);
		for (int j = 0; j < q[i].size(); j++) {
			int v = q[i][j], p = v;
			int w = get(v);
			for (int k = L - 1; ~k; k--) {
				if (!fa[v][k]) continue;
				if (get(fa[v][k]) == w) v = fa[v][k];
			}
			ans += i - t[fa[v][0]].len - 1;
		}
	}
	printf("%lld\n", ans);
	return 0;
}


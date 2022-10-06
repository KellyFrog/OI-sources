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
#define rg register
#else
#define rg
#endif

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
    return (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS++) : *iS++);
}
inline void qread() {
}
template <typename T1, typename... T2> inline void qread(T1 &x, T2 &...ls) {
    x = 0;
    rg char ch = ' ';
    rg int ps = 1;
    while (!isdigit(ch) && ch != '-')
        ch = getchar();
    if (ch == '-')
        ps = -1, ch = getchar();
    while (isdigit(ch))
        x = x * 10 + ch - '0', ch = getchar();
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
    if (oS == oT)
        flush();
}
template <typename T> inline void qwrite(T x) {
    if (x < 0)
        putchar('-'), x = -x;
    if (x < 10)
        return putchar('0' + x), void();
    qwrite(x / 10), putchar('0' + (x % 10));
}

template <typename T> inline void qwrite(T x, char ch) {
    qwrite(x), putchar(ch);
}
}; // namespace fastio

#ifndef ONLINE_JUDGE

void debug(const char *s) {
    cerr << s;
}
template <typename T1, typename... T2> void debug(const char *s, const T1 x, T2... ls) {
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

template <typename T> inline void chkadd(T &x, T y) {
    x = x + y >= mod ? x + y - mod : x + y;
}
template <typename T> inline void chkadd(T &x, T y, T z) {
    x = y + z >= mod ? y + z - mod : y + z;
}
template <typename T> inline void chkmns(T &x, T y) {
    x = x - y < 0 ? x - y + mod : x - y;
}
template <typename T> inline void chkmns(T &x, T y, T z) {
    x = y - z < 0 ? y - z + mod : y - z;
}
template <typename T> inline void chkmax(T &x, T y) {
    x = x < y ? y : x;
}
template <typename T> inline void chkmax(T &x, T y, T z) {
    x = y > z ? y : z;
}
template <typename T> inline void chkmin(T &x, T y) {
    x = x < y ? x : y;
}
template <typename T> inline void chkmin(T &x, T y, T z) {
    x = y < z ? y : z;
}

ll qpow(ll x, ll p) {
    rg ll base = x, res = 1;
    while (p) {
        if (p & 1)
            res = (res * base) % mod;
        base = (base * base) % mod;
        p >>= 1;
    }
    return res;
}

/* template ends here */

const int N = 2e5 + 5;
const int M = 1e7 + 5;
const int inf = 1e9;

int head[N], nxt[M], wgt[M], to[M];
int cur[N];
int tot = 1;
int dis[N];
int s, t;

vector<int> adj[N];
int id[N], cnt;
int dfn[N], dfncnt, top[N], son[N], sgn[N], sgncnt, siz[N], fat[N], dep[N];
int pathid[N], nodeid[N];
bool iscut[N];
int n, m;
map<int, int> eg0[N];

inline bool bfs() {
    memset(dis, 0, sizeof dis);
    memcpy(cur, head, sizeof cur);
    static int que[N];
    int hea = 1, tail = 0;
    dis[s] = 1;
    que[++tail] = s;
    while (hea <= tail) {
        int u = que[hea++];
        for (int e = head[u]; e; e = nxt[e]) {
            int v = to[e];
            int w = wgt[e];
            if (w != 0 && dis[v] == 0) {
                dis[v] = dis[u] + 1;
                que[++tail] = v;
            }
        }
    }
    return dis[t];
}

inline int dfs(int u, int in) {
    if (u == t)
        return in;
    int res = 0;
    for (int e = cur[u]; e; e = nxt[e]) {
        int v = to[e];
        int w = wgt[e];
        if (w && dis[v] == dis[u] + 1) {
            cur[u] = e;
            int cur = dfs(v, min(in, w));
            in -= cur;
            res += cur;
            wgt[e] -= cur;
            wgt[e ^ 1] += cur;
            if (!in)
                break;
        }
    }
    if (!res)
        dis[u] = -1;
    return res;
}

inline void addedge(int u, int v, int w) {
    nxt[++tot] = head[u];
    to[tot] = v;
    wgt[tot] = w;
    head[u] = tot;
}

inline int solve(int s0, int t0) {
    s = s0;
    t = t0;
    int ans = 0;
    while (bfs()) {
        int x = dfs(s, inf);
        assert(x != inf);
        ans += x;
    }
    return ans;
}

inline vector<pair<int, int>> cut() {
    vector<pair<int, int>> res;
    static int que[N], hea = 1, tail = 0;
    hea = 1, tail = 0;
    static bool vis1[N], vis2[N];
    memset(vis1, 0, sizeof vis2);
    memset(vis2, 0, sizeof vis2);

    {
        que[++tail] = s;
        vis1[s] = 1;
        while (hea <= tail) {
            int u = que[hea++];
            for (int e = head[u]; e; e = nxt[e]) {
                int v = to[e];
                int w = wgt[e];
                if (w && !vis1[v])
                    vis1[v] = 1, que[++tail] = v;
            }
        }
    }

    rep(u, 1, cnt) {
        for (int e = head[u]; e; e = nxt[e]) {
            int v = to[e];
            if (vis1[u] && !vis1[v]) {
                res.pb(mp(u, v));
            }
        }
    }
    return res;
}


inline void build(int cur, int l, int r) {
    id[cur] = ++cnt;
    if (cur >> 1) {
        addedge(id[cur >> 1], id[cur], inf);
        addedge(id[cur], id[cur >> 1], 0);
    }
    if (l == r) {
        addedge(id[cur], t, 1);
        addedge(t, id[cur], 0);
        nodeid[l] = id[cur];
        return;
    }
    int mid = l + r >> 1;
    build(cur << 1, l, mid);
    build(cur << 1 | 1, mid + 1, r);
}

inline void connect(int cur, int ql, int qr, int x, int l, int r) {
    if (ql <= l && r <= qr) {
        addedge(x, id[cur], inf);
        addedge(id[cur], x, 0);
        return;
    }
    int mid = l + r >> 1;
    if (ql <= mid)
        connect(cur << 1, ql, qr, x, l, mid);
    if (mid < qr)
        connect(cur << 1 | 1, ql, qr, x, mid + 1, r);
}

inline void dfs1(int u, int fa) {
    dep[u] = dep[fa] + 1;
    fat[u] = fa;
    dfn[u] = ++dfncnt;
    siz[u] = 1;
    for (int v : adj[u]) {
        if (v != fa) {
            dfs1(v, u);
            siz[u] += siz[v];
            if (siz[v] > siz[son[u]])
                son[u] = v;
        }
    }
}

inline void dfs2(int u, int fa) {
    top[u] = son[fa] == u ? top[fa] : u;
    sgn[u] = ++sgncnt;
    if (son[u])
        dfs2(son[u], u);
    for (int v : adj[u]) {
        if (v != son[u] && v != fa)
            dfs2(v, u);
    }
}

inline int LCA(int x, int y) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        x = fat[top[x]];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    return x;
}

inline void connectrange(int l, int r, int p, int x) {
    if (l == x)
        l++;
    if (r == x)
        r--;
    if (l > r)
        return;
    connect(1, l, r, p, 1, n);
}

inline void routeconnect(int x, int y, int lca, int p) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        connectrange(sgn[top[x]], sgn[x], p, sgn[lca]);
        x = fat[top[x]];
    }
    if (sgn[x] > sgn[y])
        swap(x, y);
    connectrange(sgn[x], sgn[y], p, sgn[lca]);
}

int main() {
#ifndef ONLING_JUDGE
    //	freopen("CF786E.in", "r", stdin);
#endif
    fastio::qread(n, m);
    s = ++cnt, t = ++cnt;
    build(1, 1, n);
    rep(i, 1, n - 1) {
        int u, v;
        fastio::qread(u, v);
        adj[u].pb(v);
        adj[v].pb(u);
        eg0[u][v] = eg0[v][u] = i;
    }
    dfs1(1, 0);
    dfs2(1, 0);
    rep(i, 1, m) {
        int x, y;
        fastio::qread(x, y);
        pathid[i] = ++cnt;
        addedge(s, pathid[i], 1);
        addedge(pathid[i], s, 0);
        routeconnect(x, y, LCA(x, y), pathid[i]);
    }
    cout << solve(s, t) << "\n";
    vector<int> p1, p2;
    auto eg = cut();
    for (auto [u, v] : eg) {
        if (u == s)
            iscut[v] = 1;
        else
            iscut[u] = 1;
    }
    rep(i, 1, m) if (iscut[pathid[i]]) p1.pb(i);
    rep(i, 1, n) if (iscut[nodeid[sgn[i]]]) p2.pb(i);
    cout << p1.size() << " ";
    for (int x : p1)
        cout << x << " ";
    cout << "\n";
    cout << p2.size() << " ";
    for (int x : p2)
        cout << eg0[x][fat[x]] << " ";
    cout << "\n";
    return 0;
}
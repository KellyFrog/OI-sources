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
    return (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS++) : *iS++);
}
inline void qread() {
}
template <typename T1, typename... T2> inline void qread(T1 &x, T2 &...ls) {
    x = 0;
    char ch = ' ';
    int ps = 1;
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
    ll base = x, res = 1;
    while (p) {
        if (p & 1)
            res = (res * base) % mod;
        base = (base * base) % mod;
        p >>= 1;
    }
    return res;
}

/* template ends here */

const int N = 4e5 + 5;
const int inf = 0x3f3f3f3f;

int anc[N][20], dep[N], dfn[N], siz[N], dfncnt, psn[N], pos[N], poscnt, seq[N], sgn[N], sgncnt, seg[N], son[N], top[N], fat[N];
int lson[N], rson[N];
int tsum[N];
bool ok[N];
int n, q, a[N], d[N];
int ans = 0;

namespace seg1 {
int mi[N << 2];
inline void modify(int cur, int p, int x, int l, int r) {
    if (l == r)
        return mi[cur] = x, void();
    int mid = l + r >> 1;
    if (p <= mid)
        modify(cur << 1, p, x, l, mid);
    else
        modify(cur << 1 | 1, p, x, mid + 1, r);
    chkmin(mi[cur], mi[cur << 1], mi[cur << 1 | 1]);
}

inline int query(int cur, int ql, int qr, int l, int r) {
    if (ql <= l && r <= qr)
        return mi[cur];
    int mid = l + r >> 1;
    int res = inf;
    if (ql <= mid)
        chkmin(res, query(cur << 1, ql, qr, l, mid));
    if (mid < qr)
        chkmin(res, query(cur << 1 | 1, ql, qr, mid + 1, r));
    return res;
}

inline void build() {
    memset(mi, 0x3f, sizeof mi);
}
} // namespace seg1

namespace seg2 {
int sum[N << 2], lazy[N << 2];
inline void build() {
    memset(lazy, -1, sizeof lazy);
}
inline void setlazy(int cur, int l, int r, int x) {
    lazy[cur] = x, sum[cur] = (r - l + 1) * x;
}
inline void pushdown(int cur, int l, int r) {
    if (lazy[cur] != -1) {
        int mid = l + r >> 1;
        setlazy(cur << 1, l, mid, lazy[cur]), setlazy(cur << 1 | 1, mid + 1, r, lazy[cur]);
        lazy[cur] = -1;
    }
}
inline void pushup(int cur) {
    sum[cur] = sum[cur << 1] + sum[cur << 1 | 1];
}
inline void modify(int cur, int ql, int qr, int x, int l, int r) {
    if (ql <= l && r <= qr)
        return setlazy(cur, l, r, x), void();
    pushdown(cur, l, r);
    int mid = l + r >> 1;
    if (ql <= mid)
        modify(cur << 1, ql, qr, x, l, mid);
    if (mid < qr)
        modify(cur << 1 | 1, ql, qr, x, mid + 1, r);
    pushup(cur);
}
inline int query(int cur, int ql, int qr, int l, int r) {
    if (ql <= l && r <= qr)
        return sum[cur];
    pushdown(cur, l, r);
    int mid = l + r >> 1;
    int res = 0;
    if (ql <= mid)
        res += query(cur << 1, ql, qr, l, mid);
    if (mid < qr)
        res += query(cur << 1 | 1, ql, qr, mid + 1, r);
    return res;
}
int routesum(int x, int y) {
    int res = 0;
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        res += query(1, sgn[top[x]], sgn[x], 1, n);
        x = fat[top[x]];
    }
    if (sgn[x] > sgn[y])
        swap(x, y);
    res += (res + query(1, sgn[x], sgn[y], 1, n));
    return res;
}

void routemodify(int x, int y, int z) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        modify(1, sgn[top[x]], sgn[x], z, 1, n);
        x = fat[top[x]];
    }
    if (sgn[x] > sgn[y])
        swap(x, y);
    modify(1, sgn[x], sgn[y], z, 1, n);
}

int subtreesum(int x) {
    return query(1, sgn[x], sgn[x] + siz[x] - 1, 1, n);
}

void subtreemodify(int x, int z) {
    modify(1, sgn[x], sgn[x] + siz[x] - 1, z, 1, n);
}
} // namespace seg2

inline void dfs1(int u, int fa) {
    dep[u] = dep[fa] + 1;
    dfn[u] = ++dfncnt;
    siz[u] = 1;
    fat[u] = fa;
    anc[u][0] = fa;
    rep(i, 1, 19) anc[u][i] = anc[anc[u][i - 1]][i - 1];
    psn[u] = poscnt + 1;
    if (lson[u]) {
        dfs1(lson[u], u), siz[u] += siz[lson[u]];
    }
    pos[u] = ++poscnt;
    seq[poscnt] = u;
    if (rson[u]) {
        dfs1(rson[u], u), siz[u] += siz[rson[u]];
    }
    if (siz[lson[u]] > siz[rson[u]])
        son[u] = lson[u];
    else
        son[u] = rson[u];
}

inline void dfs2(int u, int fa) {
    if (!u)
        return;
    top[u] = u == son[fa] ? top[fa] : u;
    sgn[u] = ++sgncnt;
    dfs2(son[u], u);
    if (lson[u] == son[u])
        dfs2(rson[u], u);
    else
        dfs2(lson[u], u);
}

inline bool check(int u) {
    if (!u)
        return 0;
    if (siz[u] == 1)
        return 1;
    return seg1::query(1, psn[u], psn[u] + siz[u] - 2, 1, n) >= 0;
}

inline void update(int u) {
    if (!u)
        return;
    if (check(u)) {
        int x = u;
        per(i, 0, 19) {
            if (check(anc[x][i])) {
                x = anc[x][i];
            }
        }
        seg2::subtreemodify(x, 1);
        if(fat[x]) seg2::routemodify(1, fat[x], 0);
    } else {
        seg2::routemodify(1, u, 0);
    }
}

inline void dupdate(int u) {
    if (!u)
        return;
    seg1::modify(1, pos[u], d[u] = a[seq[pos[u] + 1]] - a[u], 1, n);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    seg1::build();
    seg2::build();

    cin >> n >> q;
    rep(i, 1, n) cin >> lson[i] >> rson[i];
    rep(i, 1, n) cin >> a[i];
    dfs1(1, 0);
    rep(i, 1, n) {
    	seg1::modify(1, pos[i], d[i] = a[seq[pos[i] + 1]] - a[i], 1, n);
    }
    dfs2(1, 0);
    rep(i, 1, n) update(i);
    while (q--) {
        int x, y;
        cin >> x >> y;
        a[x] = y;
        dupdate(seq[pos[x] - 1]);
        dupdate(seq[pos[x]]);
        update(seq[pos[x] - 1]);
        update(seq[pos[x]]);
        cout << seg2::sum[1] << "\n";
    }

    fastio::flush();
    
    fclose(stdin);
    fclose(stdout);
    return 0;
}

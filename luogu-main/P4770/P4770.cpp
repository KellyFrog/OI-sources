// Problem: P4770 [NOI2018] 你的名字
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4770
// Memory Limit: 768 MB
// Time Limit: 5000 ms

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

#define mp make_pair
#define pb push_back
#define pf push_front

#if __cplusplus >= 201703L
#define rg
#else
#define rg register
#endif

#define rep(i, s, t) for (rg int i = s; i <= t; ++i)
#define per(i, s, t) for (rg int i = t; i >= s; --i)
#define OK debug("OK\n")

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

template <typename T> inline T Min(const T &x, const T &y) {
    return x < y ? x : y;
}

template <typename T> inline T Max(const T &x, const T &y) {
    return x < y ? y : x;
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

const int N = 5e5 + 5;
const int M = 1e6 + 5;
const int L = N + 2 * M;

char SS[L], S[N];
int n, m, rL[N], rR[N];
pair<pair<int, int>, int> cur[L], tmp[L];
int rt[L], lson[N << 6], rson[N << 6], sum[N << 6], ncnt;
int len[N], opos[N];
int rangeL[6][L], rangeR[6][L];
int cnt[L];
bool qres;


int sa[L], rk[L], h[L], st[22][L], lg2[L], oldrk[L], px[L], id[L], sbelong[L], spos[N], nn;

bool cmp(int x, int y, int w) {
    return oldrk[x] == oldrk[y] && oldrk[x + w] == oldrk[y + w];
}

void buildsa() {
    int m = 300;
    int p = 0;
    rep(i, 1, nn)++ cnt[rk[i] = SS[i]];
    rep(i, 1, m) cnt[i] += cnt[i - 1];
    per(i, 1, nn) sa[cnt[rk[i]]--] = i;
    for (int w = 1;; w <<= 1, m = p) {
        p = 0;
        for (int i = nn; i > nn - w; --i)
            id[++p] = i;
        rep(i, 1, nn) if (sa[i] > w) id[++p] = sa[i] - w;
        memset(cnt, 0, sizeof(cnt));
        rep(i, 1, nn)++ cnt[px[i] = rk[id[i]]];
        rep(i, 1, m) cnt[i] += cnt[i - 1];
        per(i, 1, nn) sa[cnt[px[i]]--] = id[i];
        memcpy(oldrk, rk, sizeof(rk));
        p = 0;
        rep(i, 1, nn) rk[sa[i]] = cmp(sa[i], sa[i - 1], w) ? p : ++p;
        if (p == nn) {
            for (int i = 1; i <= nn; ++i)
                sa[rk[i]] = i;
            break;
        }
    }
}

void buildheight() {
    int p = 0;
    rep(i, 1, nn) {
        if (p)
            p--;
        while (i + p <= nn && sa[rk[i] - 1] + p <= nn && SS[i + p] == SS[sa[rk[i] - 1] + p])
            p++;
        h[rk[i]] = p;
    }
}

void buildst() {
    rep(i, 1, nn) st[0][i] = h[i];
    rep(j, 1, 21) {
        rep(i, 1, nn) {
            if (i + (1 << j) - 1 > nn)
                break;
            chkmin(st[j][i], st[j - 1][i], st[j - 1][i + (1 << j - 1)]);
        }
    }
    lg2[0] = -1;
    rep(i, 1, nn) lg2[i] = lg2[i >> 1] + 1;
}

inline int querystmin(int l, int r) {
    return Min(st[lg2[r - l + 1]][l], st[lg2[r - l + 1]][r - (1 << lg2[r - l + 1]) + 1]);
}

inline int lcp(int x, int y) {
    if (x == y)
        return nn + 1;
    x = rk[x];
    y = rk[y];
    if (x > y)
        swap(x, y);
    return querystmin(x + 1, y);
}

void getrange(int s, int len, int &resL, int &resR) {
    int p = rk[s];
    resL = resR = p;
    if (len == 0) {
        resL = 1, resR = nn;
        return;
    }

    {
        int L = 1, R = p - 1;
        if (h[p] < len)
            R = -1;
        while (L <= R) {
            int mid = L + R >> 1;
            if (querystmin(mid + 1, p) >= len)
                resL = mid, R = mid - 1;
            else
                L = mid + 1;
        }
    }
    {
        int L = p + 1, R = nn;
        if (h[p + 1] < len)
            R = -1;
        while (L <= R) {
            int mid = L + R >> 1;
            if (querystmin(p + 1, mid) >= len)
                resR = mid, L = mid + 1;
            else
                R = mid - 1;
        }
    }
}

void add(int &rt, int old, int p, int x, int l, int r) {
    rt = ++ncnt;
    lson[rt] = lson[old];
    rson[rt] = rson[old];
    sum[rt] = sum[old] + x;
    if (l == r)
        return;
    int mid = l + r >> 1;
    if (p <= mid)
        add(lson[rt], lson[old], p, x, l, mid);
    else
        add(rson[rt], rson[old], p, x, mid + 1, r);
}

void querysum(int rt, int old, int ql, int qr, int l, int r) {
    if (!rt || ql > qr || qres)
        return;
    if (ql <= l && r <= qr)
        return qres |= (sum[rt] - sum[old]), void();
    int mid = l + r >> 1;
    if (ql <= mid)
        querysum(lson[rt], lson[old], ql, qr, l, mid);
    if (qres)
        return;
    if (mid < qr)
        querysum(rson[rt], rson[old], ql, qr, mid + 1, r);
    return;
}

int cql, cqr;

int checkcnt = 0;

bool check(int p, int len) {
    if (SS[p + len - 1] == '#')
        return 0;
    checkcnt++;
    int l = -1, r = -1;
    getrange(p, len, l, r);
    qres = 0;
    querysum(rt[r], rt[l - 1], cql, cqr - len + 1, 1, n);
    return qres;
}

int getlen(int p, int st) {
    while (check(p, st + 1))
        st++;
    return st;
}

inline void dfs(int s, int x) {
}

int main() {
    scanf("%s", S + 1);
    n = strlen(S + 1);

    rep(i, 1, n) SS[++nn] = S[i], sbelong[nn] = 1;

    scanf("%d", &m);

    rep(i, 1, m) {
        SS[++nn] = i == 1 ? '$' : '#';
        sbelong[nn] = -1;
        spos[i] = nn + 1;
        static char T[N];
        scanf("%s%d%d", T + 1, &rL[i], &rR[i]);
        len[i] = strlen(T + 1);
        rep(j, 1, len[i]) {
            SS[++nn] = T[j];
            sbelong[nn] = i + 1;
        }
    }

    buildsa();
    buildheight();
    buildst();

    rep(i, 1, n) opos[i] = rk[i];
    sort(opos + 1, opos + n + 1);
    opos[0] = 0;

    rep(i, 1, n) {
        rep(p, opos[i - 1] + 1, opos[i] - 1) {
            rt[p] = rt[p - 1];
        }
        add(rt[opos[i]], rt[opos[i] - 1], sa[opos[i]], 1, 1, n);
    }
    rep(i, opos[n] + 1, nn) rt[i] = rt[i - 1];

    rep(i, 1, m) {
        cql = rL[i];
        cqr = rR[i];
        static pair<int, int> vans[N];

        int s = spos[i];
        int l = len[i] - 1;

        vans[0] = mp(s, getlen(s, 0));
        rep(j, 1, l) vans[j] = mp(s + j, getlen(s + j, Max(0, vans[j - 1].se - 1)));
        rep(j, 0, l) vans[j].fi = rk[vans[j].fi];

        sort(vans, vans + l + 1);

        ll ans = 1ll * l * (l + 1) / 2 + l + 1;

        ans -= vans[0].se;

        rep(j, 1, l) {
            int x = querystmin(vans[j - 1].fi + 1, vans[j].fi);
            ans -= vans[j].se + x - Min(x, vans[j].se);
        }

        fastio::qwrite(ans, '\n');
    }

    fastio::flush();
    return 0;
}

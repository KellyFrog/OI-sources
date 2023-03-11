// Problem: CF1495D BFS Trees
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1495D
// Memory Limit: 500 MB
// Time Limit: 2500 ms
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
    while (isdigit(ch)）
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

// const ll mod = 1e9 + 7;
// const ll mod = 1e9 + 9;
// const ll mod = 19260817;
const ll mod = 998244353;
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

const int N = 4e2 + 5;

vector<int> adj[N];
int n, m;
int dist[N][N], cnt[N][N];

void bfs(int s) {
    queue<int> q;
    memset(dist[s], 0x3f, sizeof dist[s]);
    dist[s][s] = 0, cnt[s][s] = 1;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (dist[s][v] > dist[s][u] + 1) {
                dist[s][v] = dist[s][u] + 1;
                cnt[s][v] = cnt[s][u];
                q.push(v);
            } else if (dist[s][v] == dist[s][u] + 1) {
                cnt[s][v] += cnt[s][u];
            }
        }
    }
}

inline bool onpath(int s, int t, int x) {
    return dist[s][x] + dist[x][t] == dist[s][t];
}

ll solve(int x, int y) {
    ll ans = 1;
    static int a[N];
    rep(i, 1, n) a[i] = i;
    sort(a + 1, a + 1 + n, [&x](const int &i, const int &j) { return dist[x][i] < dist[x][j]; });
    rep(i, 1, n) {
        int u = a[i];
        if (onpath(x, y, u))
            continue;
        int res = 0;
        for (int st : adj[u]) {
            if (dist[x][u] - dist[x][st] == 1 && dist[y][u] - dist[y][st] == 1)
                res++;
        }
        ans = ans * res % mod;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    memset(dist, 0x3f, sizeof dist);

    fastio::qread(n, m);
    rep(i, 1, m) {
        int u, v;
        fastio::qread(u, v);
        adj[u].pb(v);
        adj[v].pb(u);
    }

    rep(i, 1, n) bfs(i);

    rep(i, 1, n) rep(j, 1, n) fastio::qwrite((cnt[i][j] > 1 ? 0ll : solve(i, j)), " \n"[j == n]);

    fastio::flush();
    return 0;
}

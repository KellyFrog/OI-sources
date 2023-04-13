// Problem: P2822 [NOIP2016 提高组] 组合数问题
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P2822
// Memory Limit: 500 MB
// Time Limit: 1000 ms

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

const int N = 2e3 + 5;

int f[N][N], sum[N][N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int t, k;
    cin >> t >> k;
    int n = 2e3, m = 2e3;
    f[0][0] = f[1][0] = f[1][1] = 1;
    rep(i, 2, n) {
        f[i][0] = 1;
        rep(j, 1, i) f[i][j] = (f[i - 1][j - 1] + f[i - 1][j]) % k;
    }

    rep(i, 1, n) rep(j, 1, m) {
        sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + (i >= j && f[i][j] == 0 ? 1 : 0);
    }

    while (t--) {
        int x, y;
        cin >> x >> y;
        cout << sum[x][y] << "\n";
    }

    fastio::flush();
    return 0;
}

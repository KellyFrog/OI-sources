// Problem: CF235C Cyclical Quest
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF235C
// Memory Limit: 500 MB
// Time Limit: 3000 ms

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

const int N = 1e6 + 5;
const int L = 2e6 + 5;

int nn, n, m;
int stp[N];
char S[N], T[N], SS[L];
int len[N];
int cnt[L], sa[L], rk[L], h[L], st[22][L], lg2[L], oldrk[L], px[L], id[L];

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
    return min(st[lg2[r - l + 1]][l], st[lg2[r - l + 1]][r - (1 << lg2[r - l + 1]) + 1]);
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

int rt[L], lson[N << 6], rson[N << 6], sum[N << 6], ncnt;

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

int querysum(int rt, int old, int ql, int qr, int l, int r) {
    if (!rt || ql > qr)
        return 0;
    if (ql <= l && r <= qr)
        return sum[rt] - sum[old];
    int mid = l + r >> 1;
    int res = 0;
    if (ql <= mid) res += querysum(lson[rt], lson[old], ql, qr, l, mid);
    if (mid < qr) res += querysum(rson[rt], rson[old], ql, qr, mid + 1, r);
    return res;
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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	
	fastio::flush();
	return 0;
}

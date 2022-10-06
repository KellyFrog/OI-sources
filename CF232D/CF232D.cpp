// Problem: CF232D Fence
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF232D
// Memory Limit: 250 MB
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

const int N = 2e5 + 5;
const int L = N;

int a[N], b[N], n, p, q;

int cnt[L], sa[L], rk[L], h[L], st[22][L], lg2[L], oldrk[L], px[L], id[L];

bool cmp(int x, int y, int w) {
    return oldrk[x] == oldrk[y] && oldrk[x + w] == oldrk[y + w];
}

void buildsa() {
    int m = n<<1;
    int p = 0;
    rep(i, 1, (n<<1))++ cnt[rk[i] = a[i]];
    rep(i, 1, m) cnt[i] += cnt[i - 1];
    per(i, 1, (n<<1)) sa[cnt[rk[i]]--] = i;
    for (int w = 1;; w <<= 1, m = p) {
        p = 0;
        for (int i = (n<<1); i > (n<<1) - w; --i)
            id[++p] = i;
        rep(i, 1, (n<<1)) if (sa[i] > w) id[++p] = sa[i] - w;
        memset(cnt, 0, sizeof(cnt));
        rep(i, 1, (n<<1))++ cnt[px[i] = rk[id[i]]];
        rep(i, 1, m) cnt[i] += cnt[i - 1];
        per(i, 1, (n<<1)) sa[cnt[px[i]]--] = id[i];
        memcpy(oldrk, rk, sizeof(rk));
        p = 0;
        rep(i, 1, (n<<1)) rk[sa[i]] = cmp(sa[i], sa[i - 1], w) ? p : ++p;
        if (p == (n<<1)) {
            for (int i = 1; i <= (n<<1); ++i)
                sa[rk[i]] = i;
            break;
        }
    }
}

void buildheight() {
    int p = 0;
    rep(i, 1, (n<<1)) {
        if (p)
            p--;
        while (i + p <= (n<<1) && sa[rk[i] - 1] + p <= (n<<1) && a[i + p] == a[sa[rk[i] - 1] + p])
            p++;
        h[rk[i]] = p;
    }
}

void buildst() {
    rep(i, 1, (n<<1)) st[0][i] = h[i];
    rep(j, 1, 21) {
        rep(i, 1, (n<<1)) {
            if (i + (1 << j) - 1 > (n<<1))
                break;
            chkmin(st[j][i], st[j - 1][i], st[j - 1][i + (1 << j - 1)]);
        }
    }
    lg2[0] = -1;
    rep(i, 1, (n<<1)) lg2[i] = lg2[i >> 1] + 1;
}

inline int querystmin(int l, int r) {
    return min(st[lg2[r - l + 1]][l], st[lg2[r - l + 1]][r - (1 << lg2[r - l + 1]) + 1]);
}

inline int lcp(int x, int y) {
    if (x == y)
        return (n<<1) + 1;
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
        resL = 1, resR = (n<<1);
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
        int L = p + 1, R = (n<<1);
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

int rt[N], lson[N << 6], rson[N << 6], sum[N << 6], ncnt;

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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	
	cin >> n;
	rep(i, 1, n) cin >> a[i];
	per(i, 1, n) b[i] = a[i] = a[i] - a[i-1];
	rep(i, 1, n) a[i+n] = b[i+n] = -a[i];
	sort(b + 1, b + 2*n + 1);
	p = unique(b + 1, b + 2*n + 1) - (b + 1);
	rep(i, 1, 2*n) a[i] = lower_bound(b + 1, b + p + 1, a[i]) - b;
	
	buildsa();
	buildheight();
	buildst();
	
	
	rep(i, 1, n<<1) {
		if(sa[i] <= n+1) rt[i] = rt[i-1];
		else add(rt[i], rt[i-1], sa[i]-n, 1, 1, n);
	}
	
	cin >> q;
	while(q--) {
		int l, r;
		cin >> l >> r;
		if(l == r) {
		    fastio::qwrite(n-1, '\n');
			continue;
		} else {
			int l0 = l, r0 = r;
			int ll0 = l - (r - l + 1) + 1;
			int rr0 = r + 2;
			l++;
			int rl = -1, rr = -1;
			getrange(l, r-l+1, rl, rr);
			int res1 = querysum(rt[rr], rt[rl-1], 1, ll0, 1, n);
			int res2 = querysum(rt[rr], rt[rl-1], rr0, n, 1, n);
			fastio::qwrite(res1 + res2, '\n');
		}
	}
	
	fastio::flush();
	return 0;
}


// Problem: CF452E Three strings
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF452E?contestId=41163
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)


// Happy Chinese new year! (Feb. 12th, 2021)

/*
 * Codeforces @Chenkaifeng
 * Luogu @longer_name
 */

// Happy Chinese new year! (Feb. 12th, 2021)

/*
 * Codeforces @Chenkaifeng
 * Luogu @longer_name
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
#define rg register
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
		return (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin),
		        (iS == iT ? EOF : *iS++) : *iS++);
	}
	inline void qread() {}
	template <typename T1, typename... T2>
	inline void qread(T1 &x, T2 &...ls) {
		x = 0;
		rg char ch = ' ';
		rg int ps = 1;
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

ll qpow(ll x, ll p, ll mod) {
	rg ll base = x, res = 1;
	while (p) {
		if (p & 1) res = (res * base) % mod;
		base = (base * base) % mod;
		p >>= 1;
	}
	return res;
}

const int N = 3e5 + 5;
const ll mod = 1e9 + 7;

int n, m = 3e5, k;
char S[N];
int a[N];
int sa[N], rk[N], h[N];
int cnt[N];
pair<int, int> que[N];
int head = 1, tail;
pair<pair<int, int>, int> cur[N], tmp[N];

void RSort() {
	memset(cnt, 0, sizeof cnt);
	per(i, 1, n) cnt[cur[i].fi.se]++;
	rep(i, 1, m) cnt[i] += cnt[i-1];
	per(i, 1, n) tmp[cnt[cur[i].fi.se]--] = cur[i];
	rep(i, 1, n) cur[i] = tmp[i];
	
	memset(cnt, 0, sizeof cnt);
	per(i, 1, n) cnt[cur[i].fi.fi]++;
	rep(i, 1, m) cnt[i] += cnt[i-1];
	per(i, 1, n) tmp[cnt[cur[i].fi.fi]--] = cur[i];
	rep(i, 1, n) cur[i] = tmp[i];
	
	int p = 1;
	rk[cur[1].se] = 1;
	rep(i, 2, n) {
		if(cur[i].fi != cur[i-1].fi) p++;
		rk[cur[i].se] = p;
	}
}

void SA() {
	rep(i, 1, n) rk[i] = S[i];
	for(int len = 1; len / 2 <= n; len <<= 1) {
		rep(i, 1, n) cur[i] = mp(mp(rk[i], rk[i+len]), i);
		RSort();
	}
	rep(i, 1, n) sa[rk[i]] = i;
}

//a,b,c = *,*,*
//A # B $ C

template<typename T>
void chkmns(T& x, T y) {
	x = x - y > 0 ? x - y : x - y + mod;
}

template<typename T>
void chkadd(T& x, T y) {
	x = x + y >= mod ? x + y - mod : x + y;
}

char A1[N], A2[N], A3[N];;
int n1, n2, n3;

ll fa[N], val[N], cnta[N], cntb[N], cntc[N], res[N], ans;
pair<int, int> nd[N];



void BuildH() {
	int siz = 0;
	rep(i, 1, n) {
		if(siz >= 1) siz--;
		while(S[i+siz] == S[sa[rk[i]-1]+siz] && i+siz <= n && sa[rk[i]-1]+siz <= n) siz++;
		h[rk[i]] = siz;
	}
}

int Find(int x) {
	return x == fa[x] ? x : fa[x] = Find(fa[x]);
}

void Merge(int x, int y) {
	debug("[merge] {} {}\n", x, y);
	x = Find(x);
	y = Find(y);
	if(x == y) return;
	chkmns(ans, val[x]);
	chkmns(ans, val[y]);
	fa[y] = x;
	cnta[x] += cnta[y];
	cntb[x] += cntb[y];
	cntc[x] += cntc[y];
	debug("side x = {} {} {}\n", cnta[x], cntb[x], cntc[x]);
	chkadd(ans, val[x] = cnta[x] * cntb[x] * cntc[x] % mod);
}

int main() {
	scanf("%s%s%s", A1 + 1, A2 + 1, A3 + 1);
	n1 = strlen(A1 + 1);
	n2 = strlen(A2 + 1);
	n3 = strlen(A3 + 1);
	rep(i, 1, n1) S[i] = A1[i];
	 S[n1+1] = '$';
	rep(i, 1, n2) S[i+n1+1] = A2[i]; S[n1+n2+2] = '#';
	rep(i, 1, n3) S[i+n1+n2+2] = A3[i];
	n = n1 + n2 + n3 + 2;
	debug("'{}' {}\n", S+1, n);
	
	SA();
	BuildH();
	
	rep(i, 1, n) nd[i] = mp(h[i], i);
	sort(nd + 1, nd + 1 + n);
	
	rep(i, 1, n) fa[i] = i;
	
	rep(i, 1, n1) cnta[rk[i]] = 1;
	rep(i, 1, n2) cntb[rk[i+n1+1]] = 1; 
	rep(i, 1, n3) cntc[rk[i+n1+n2+2]] = 1;
	
	rep(i, 1, n) {
		debug("[{}] cnt=[{},{},{}] rk={} h={} sa={} : {}\n", i, cnta[i], cntb[i], cntc[i], rk[i], h[i], sa[i], S+sa[i]);
	}
	
	int len = min(min(n1, n2), n3);
	int pt = n;
	per(p, 1, len) {
		debug("solve={}\n", p);
		while(nd[pt].fi >= p) {
			int x = nd[pt--].se;
			if(x == 1) continue;
			Merge(x, x-1);
			
		}
		res[p] = ans;
	}
	
	rep(i, 1, len) printf("%lld ", res[i]); puts("");
		
	return 0;
}
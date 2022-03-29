#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <map>

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

const int N = 1e6 + 5;
const ll mod = 317847191;
const int inf = 1e9;

int a[N], b[N], c[N];
int cnt[N], vis[N];
int ans[N], sz;
int n, m;
pair<char, int> opt[N];

ll qpow(ll x, ll p) {
	ll res = 1, base = x;
	while(p) {
		if(p & 1) res = (res * base) % mod;
		base = (base * base) % mod;
		p >>= 1;
	}
	return res;
}

int main() {
	scanf("%d%d", &n, &m);
	rep(i, 1, n) scanf("%d", &a[i]), b[i] = a[i];
	sort(b + 1, b + 1 + n);
	int p = unique(b + 1, b + 1 + n) - b;
	rep(i, 1, n) cnt[c[i] = lower_bound(b + 1, b + 1 + p, a[i]) - b]++;
	rep(i, 1, m) {
		char str[5]; int x = 0;
		scanf("%s", str);
		if(str[0] == 'D') scanf("%d", &x), x = lower_bound(b + 1, b + 1 + p, x) - b, cnt[x]--;
		opt[i] = mp(str[0], x);
	}
	int mini = inf, maxi = -inf;
	ll mul = 1;
	rep(i, 1, n) {
		if(cnt[c[i]] && !vis[c[i]]) {
			vis[c[i]] = 1;
			mini = min(mini, a[i]);
			maxi = max(maxi, a[i]);
			mul = (mul * qpow(a[i], cnt[c[i]])) % mod;
		}
	}
	per(i, 1, m) {
		if(opt[i].fi == 'D') mini = min(mini, b[opt[i].se]), maxi = max(maxi, b[opt[i].se]), mul = (mul * b[opt[i].se]) % mod;
		if(opt[i].fi == 'B') ans[++sz] = maxi;
		if(opt[i].fi == 'S') ans[++sz] = mini;
		if(opt[i].fi == 'M') ans[++sz] = qpow(maxi, mini);
		if(opt[i].fi == 'T') ans[++sz] = mul;
	}
	per(i, 1, sz) printf("%d\n", ans[i]);
	return 0;
}

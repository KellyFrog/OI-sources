// Problem: E. Deleting Numbers
// Contest: Codeforces - Codeforces Round #670 (Div. 2)
// URL: https://codeforces.com/contest/1406/problem/E
// Memory Limit: 512 MB
// Time Limit: 1000 ms
//
// Powered by CP Editor (https://cpeditor.org)

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
	rg ll base = x, res = 1;
	while (p) {
		if (p & 1) res = (res * base) % mod;
		base = (base * base) % mod;
		p >>= 1;
	}
	return res;
}

#define int long long


const int N = 1e5 + 5;
const int M = 9600;
//const int SZ = 56;
//const int S = 15;
const int S = 0;
const int SZ = 1;
bool prime[N];
vector<int> prm;
int n;

int querya(int x) {
	printf("A %lld\n", x);
	fflush(stdout);
	int p;
	scanf("%lld", &p);
	return p;
}


int queryb(int x) {
	printf("B %lld\n", x);
	fflush(stdout);
	int p;
	scanf("%lld", &p);
	return p;
}

bool check1(int x) {
	if(x > n) return 0;
	int p = queryb(x);
	if(p == 0) return 0;
	return querya(x);
}

bool check2(int x) {
	if(x > n) return 0;
	return querya(x);
}

signed main() {
	scanf("%lld", &n);
	int ans = 1;
	memset(prime, 1, sizeof prime);
	prm.pb(0);
	rep(i, 2, n) if(prime[i]) {
		prm.pb(i);
		for(int j = 1; j * i <= n; j++) prime[i * j] = 0;
	}
	memset(prime, 1, sizeof prime);
	rep(i, 1, min((ll)prm.size()-1, S)) {
		int a = prm[i];
		for(int j = 1; j * a <= n; j++) prime[a * j] = 0;
		if(1ll * ans * a > n) break;
		int x = a;
		queryb(x);
		while(check2(x)) ans *= a, x *= a;

	}
	
	
	int lastans = querya(1);
	int cnt0 = 0;
	for(int i = 1; (i - 1) * SZ + S < prm.size()-1; i++) {
		int L = S + (i - 1) * SZ + 1;
		int R = S + i * SZ;
		R = min(R, (ll)prm.size()-1);
		int cnt = 0;
		rep(j, L, R) {
			int x = prm[j];
			for(int k = 1; k * x <= n; k++) if(prime[k * x]) prime[k * x] = 0, cnt++;
		}
		rep(j, L, R) {
			int x = prm[j];
			if(x == 12547) OK;
			if(1ll * x * ans <= n) queryb(x);
		}
		int p = querya(1);
		if(lastans - p != cnt) {
			rep(j, L, R) {
				cnt0++;
				int x = prm[j];
				if(1ll * ans * x > n) break;
				assert(x != 12547);
				while(check2(x)) ans *= prm[j], x *= prm[j];
			}
		}
		lastans = p;
	}
	printf("C %lld\n", ans);
	fflush(stdout);
	fastio::flush();
	return 0;
}

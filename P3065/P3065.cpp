// Problem: P3065 [USACO12DEC]First! G
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3065?contestId=45250
// Memory Limit: 125 MB
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

const int N = 3e5 + 5;
const int M = 27;

int rt, son[N][M], ed[N], cnt;
string S[N];
bool ok[N];
int n;

inline void insert(string S) {
	int l = S.size();
	if(!rt) rt = ++cnt;
	int cur = rt;
	rep(i, 0, l-1) {
		int& nxt = son[cur][S[i]-'a'];
		if(!nxt) nxt=++cnt;
		cur = nxt;
	}
	ed[cur]++;
}

inline bool check(string S) {
	int cur = rt;
	int l = S.size();
	static vector<int> adj[M];
	static int ind[N], que[N], head, tail;
	rep(i, 0, 25) adj[i].clear(), ind[i] = 0;
	head = 1, tail = 0;
	rep(i, 0, l-1) {
		rep(j, 0, S[i]-'a'-1) if(son[cur][j]) adj[S[i]-'a'].pb(j);
		rep(j, S[i]-'a'+1, 25) if(son[cur][j]) adj[S[i]-'a'].pb(j);
		cur = son[cur][S[i]-'a'];
		if(i == l-1) {
			if(ed[cur] > 1) return 0;
		} else {
			if(ed[cur]) return 0;
		}
	}
	rep(u, 0, 25) for(int v : adj[u]) ind[v]++;
	rep(u, 0, 25) if(!ind[u]) que[++tail] = u;
	while(head <= tail) {
		int u = que[head++];
		for(int v : adj[u]) if(--ind[v] == 0) que[++tail] = v;
	}
	rep(i, 0, 25) if(ind[i]) return 0;
	return 1;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	rep(i, 1, n) cin >> S[i], insert(S[i]);
	int ans = 0;
	rep(i, 1, n) if(check(S[i])) ok[i] = 1, ans++;
	cout << ans << "\n";
	rep(i, 1, n) if(ok[i]) cout << S[i] << "\n";
  fastio::flush();
  return 0;
}

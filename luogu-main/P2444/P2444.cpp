// Problem: P2444 [POI2000]病毒
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P2444
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

const int N = 3e4 + 5;

int son[N][2], fail[N], hasend[N], rt, cnt;
char S[N];
vector<int> adj[N];
int vis[N], ind[N], que[N], head = 1, tail;
int n;

inline void insert() {
	int len = strlen(S+1);
	if(!rt) rt = ++cnt;
	int cur = rt;
	rep(i, 1, len) {
		if(!son[cur][S[i]-'0']) son[cur][S[i]-'0'] = ++cnt;
		cur = son[cur][S[i]-'0'];
	}
	hasend[cur] = 1;
}

inline void buildfail() {
	fail[rt] = rt;
	if(son[rt][0]) fail[son[rt][0]] = rt, que[++tail] = son[rt][0];
	else son[rt][0] = rt;
	
	if(son[rt][1]) fail[son[rt][1]] = rt, que[++tail] = son[rt][1];
	else son[rt][1] = rt;
	
	while(head <= tail) {
		int cur = que[head++];
		
		if(son[cur][0]) fail[son[cur][0]] = son[fail[cur]][0], que[++tail] = son[cur][0];
		else son[cur][0] = son[fail[cur]][0];
		
		if(son[cur][1]) fail[son[cur][1]] = son[fail[cur]][1], que[++tail] = son[cur][1];
		else son[cur][1] = son[fail[cur]][1];
	}
	rep(i, 1, cnt) hasend[que[i]] |= hasend[fail[que[i]]];
	rep(i, 1, cnt) {
		if(son[i][0]) adj[son[i][0]].pb(i), ind[i]++;
		if(son[i][1]) adj[son[i][1]].pb(i), ind[i]++;
	}
}

int main() {
	scanf("%d", &n);
	rep(i, 1, n) scanf("%s", S+1), insert();
	buildfail();
	head = 1, tail = 0;
	rep(i, 1, cnt) if(!ind[i] || hasend[i]) que[++tail] = i;
	while(head <= tail) {
		int u = que[head++];
		if(!hasend[u] || vis[u]) continue;
		vis[u] = 1;
		for(int v : adj[u]) {
			if(!vis[v]) {
				if(--ind[v] == 0) {
					hasend[v] = 1;
					que[++tail] = v;
				}
			}
		}
	}
	puts(ind[rt] ? "TAK" : "NIE");
  fastio::flush();
  return 0;
}

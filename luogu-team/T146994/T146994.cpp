
// Problem: T146994 最大公约数
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T146994?contestId=38911
// Memory Limit: 500 MB
// Time Limit: 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

//Author: Chenkaifeng

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

#define rep(i, s, t) for(rg int i = s; i <= t; i++)
#define per(i, s, t) for(rg int i = t; i >= s; i--)
#define OK cerr << "OK!\n"


namespace fastio {
	const int SIZE = (1 << 20) + 1;
	char ibuf[SIZE], *iS, *iT, obuf[SIZE],*oS = obuf, *oT = obuf + SIZE - 1;
	char _st[55];
	int _qr = 0;

	inline char getchar() {
		return (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS++) : *iS++);
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
		return ;
	}
	inline void putchar(char _x) {
		*oS++ = _x;
		if(oS == oT) flush();
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
}; //namespace fastio


void debug(const char* s) {
	cerr << s;
}
template<typename T1, typename ...T2>
void debug(const char * s, const T1 x, T2 ...ls) {
	int p = 0;
	while(*(s + p) != '\0') {
		if(*(s + p) == '{' && *(s + p + 1) == '}') {
			cerr << x;
			debug(s + p + 2, ls...);
			return;
		}
		cerr << *(s + p++);
	}
}

ll qpow(ll x, ll p, ll mod) {
	rg ll base = x, res = 1;
	while(p) {
		if(p & 1) res = (res * base) % mod;
		base = (base * base) % mod;
		p >>= 1;
	}
	return res;
}

const int N = 2e3 + 5;

ll a[N][N];
bool vis[N][N];
int n, m, x, y;
int nxt[4][2] = {
	{-1, 0}, {1, 0}, {0, -1}, {0, 1}
};

int dis(int x0, int y0) {
	return abs(x - x0) + abs(y - y0);
}

int main() {
	fastio::qread(n, m);
	rep(i, 1, n) rep(j, 1, m) fastio::qread(a[i][j]);
	fastio::qread(x, y);
	queue<pair<int, int> > q;
	q.push(mp(x, y));
	ll ans = a[x][y];
	while(!q.empty()) {
		int x = q.front().fi, y = q.front().se;
		q.pop();
		if(vis[x][y]) continue;
		vis[x][y] = 1;
		ans = __gcd(ans, a[x][y]);
		if(ans == 1) {
			cout << dis(x, y) << endl;
			return 0;
		}
		rep(i, 0, 3) {
			rg int nx = x + nxt[i][0], ny = y + nxt[i][1];
			if(!a[nx][ny]) continue;
			if(dis(nx, ny) != dis(x, y) + 1) continue;
			q.push(mp(nx, ny));
		}
	}
	cout << -1 << endl;
	return 0;
}

//FUckyou!! RE
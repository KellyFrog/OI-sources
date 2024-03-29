
// Problem: T115724 拯救公主2
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T115724?contestId=39107
// Memory Limit: 125 MB
// Time Limit: 1000 ms
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
#define debug(x) cerr << (#x) << " = " << (x) << "\n"
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

ll qpow(ll x, ll p, ll mod) {
	rg ll base = x, res = 1;
	while(p) {
		if(p & 1) res = (res * base) % mod;
		base = (base * base) % mod;
		p >>= 1;
	}
	return res;
}

const int N = 105;

struct Node {
	int x, y, z;
	Node() {}
	Node(int x0, int y0, int z0) : x(x0), y(y0), z(z0) {}
};

int nxt[6][3] = {
	{-1, 0, 0},
	{1, 0, 0},
	{0, -1, 0},
	{0, 1, 0},
	{0, 0, -1},
	{0, 0, 1}
};
int ok[N][N][N];
int dis[N][N][N];
int n, m, k, t;

void Solve() {
	memset(ok, 0, sizeof ok);
	memset(dis, -1, sizeof dis);
	fastio::qread(n, m, k, t);
	rep(i, 1, n) rep(j, 1, m) rep(p, 1, k) fastio::qread(ok[i][j][p]), ok[i][j][p] ^= 1;
	queue<Node> q;
	q.push(Node(1, 1, 1));
	dis[1][1][1] = 0;
	while(!q.empty()) {
		Node p = q.front();
		q.pop();
		rg int x = p.x, y = p.y, z = p.z;
		rep(i, 0, 5) {
			rg int nx = x + nxt[i][0];
			rg int ny = y + nxt[i][1];
			rg int nz = z + nxt[i][2];
			if(ok[nx][ny][nz] && dis[nx][ny][nz] == -1) {
				dis[nx][ny][nz] = dis[x][y][z] + 1;
				q.push(Node(nx, ny, nz));
			}
		}
	}
	fastio::qwrite((dis[n][m][k] == -1 ? -1 : dis[n][m][k] <= t ? dis[n][m][k] : -1), '\n');
}

int main() {
	int t;
	fastio::qread(t);
	while(t--) Solve();
	fastio::flush();
	return 0;
}
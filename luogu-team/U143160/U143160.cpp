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

inline void qread() {}
template<typename T1, typename ...T2>
inline void qread(T1 &x, T2&... ls) {
	x = 0;
	rg char ch = ' '; rg int ps = 1;
	while(!isdigit(ch) && ch != '-') ch = getchar();
	if(ch == '-') ps = -1, ch = getchar();
	while(isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
	x *= ps;
	qread(ls...);
}

template<typename T>
inline void qwrite(T x) {
	if(x < 0) putchar('-'), x = -x;
	if(x < 10) return putchar('0' + x), void();
	qwrite(x / 10), putchar('0' + (x % 10));
}

template<typename T>
inline void qwrite(T x, char ch) {
	qwrite(x), putchar(ch);
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


const double inf = 1e18;
const int N = 1005;

struct Circ {
	ll x, y, r;
};

Circ a[N];
double dis[N], adj[N][N];
bool vis[N];
ll n, sx, sy, ex, ey;

double Calc(Circ x, Circ y) {
	return max(0.0, sqrt((x.x - y.x) * (x.x - y.x) + (x.y - y.y) * (x.y - y.y)) - x.r - y.r);
}

void Dij(int s) {
	rep(i, 1, n+2) dis[i] = inf;
	dis[s] = 0;
	rep(i, 1, n+1) {
		double mi = inf; int ps = 0;
		rep(j, 1, n+2) if(!vis[j] && dis[j] < mi) mi = dis[j], ps = j;
		vis[ps] = 1;
		rep(j, 1, n+2) dis[j] = min(dis[j], dis[ps] + adj[ps][j]);
	}
}

int main() {
	qread(sx, sy, ex, ey);
	qread(n);
	rep(i, 1, n) qread(a[i].x, a[i].y, a[i].r);
	a[n+1].x = sx, a[n+1].y = sy;
	a[n+2].x = ex, a[n+2].y = ey;
	rep(i, 1, n+2) rep(j, 1, n+2) adj[i][j] = Calc(a[i], a[j]);
	Dij(n+1);
	//rep(i, 1, n+2) fprintf(stderr, "%.10lf\n", dis[i]);
	printf("%.10lf\n", dis[n+2]);
	return 0;
}

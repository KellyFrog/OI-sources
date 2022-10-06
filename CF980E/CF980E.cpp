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

const int N = 1e6 + 5;

vector<int> adj[N];
int sum[N], fat[N], dep[N], dfn[N], siz[N], dfncnt;
bool ans[N];
int n, k;

int lowbit(int x) {
	return x & (-x);
}

void Add(int x, int p) {
	while(x <= n) {
		sum[x] += p;
		x += lowbit(x);
	}
}

void Add(int l, int r, int p) {
	Add(l, p), Add(r+1, -p);
}

int Sum(int x) {
	int res = 0;
	while(x > 0) {
		res += sum[x];
		x -= lowbit(x);
	}
	return res;
}

void Dfs(int u, int fa) {
	dep[u] = dep[fa] + 1;
	siz[u] = 1;
	fat[u] = fa;
	dfn[u] = ++dfncnt;
	for(int v : adj[u]) if(v != fa) Dfs(v, u), siz[u] += siz[v];
}

int main() {
	qread(n, k);
	rep(i, 1, n-1) {
		int u, v;
		qread(u, v);
		adj[u].pb(v), adj[v].pb(u);
	}
	Dfs(n, 0);
	k = n - k;
	per(i, 1, n) {
		int x = Sum(dfn[i]);
		if(dep[i] - x <= k) {
			k -= dep[i] - x;
			int u = i;
			while(u) {
				if(ans[u]) break;
				Add(dfn[u], dfn[u] + siz[u] - 1, 1);
				ans[u] = 1;
				u = fat[u];
			}
		}
	}
	rep(i, 1, n) if(!ans[i]) qwrite(i, ' ');
	putchar('\n');
	return 0;
}

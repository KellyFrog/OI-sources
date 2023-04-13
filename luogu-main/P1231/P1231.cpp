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

template<typename T>
inline void chkmax(T& x, T y) {
	if(x < y) x = y;
}

template<typename T>
inline void chkmin(T& x, T y) {
	if(x > y) x = y;
}

template<typename T>
inline void chkmod(T& x, ll mod) {
	x = x > mod ? x - mod : x;
}

template<typename T>
inline void chkadd(T& x, T y, ll mod) {
	x = x + y > mod ? x + y - mod : x + y;
}

template<typename T>
inline void chkmns(T& x, T y, ll mod) {
	x = x - y < 0 ? x - y + mod : x - y;
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
template<const int N, const int M, const ll inf>
class MaxFlow {
	private:
		int head[N], nxt[M << 1], to[M << 1], tot = 1;
		ll wgt[M << 1];
		int dep[N], vis[N];
		int s, t;
		ll ans = 0;

		void AddEdge_(int u, int v, int w) {
			nxt[++tot] = head[u];
			to[tot] = v;
			wgt[tot] = w;
			head[u] = tot;
		}

		bool Bfs() {
			memset(vis, 0, sizeof vis);
			memset(dep, -1, sizeof dep);
			queue<int> q;
			dep[s] = 0;
			q.push(s);
			while(!q.empty()) {
				rg int u = q.front();
				q.pop();
				for(rg int i = head[u]; i; i = nxt[i]) {
					rg int v = to[i];
					rg ll w = wgt[i];
					if(w != 0 && dep[v] == -1) dep[v] = dep[u] + 1, q.push(v);
				}
			}
			return dep[t] != -1;
		}

		ll Dfs(int u, ll in) {
			if(u == t) return in;
			ll out = 0;
			vis[u] = 1;
			for(rg int i = head[u]; i; i = nxt[i]) {
				rg int v = to[i];
				if(wgt[i] == 0 || vis[v]) continue;
				if(wgt[i] && dep[v] == dep[u] + 1) {
					ll nxt = Dfs(v, min(in, wgt[i]));
					wgt[i] -= nxt;
					wgt[i ^ 1] += nxt;
					in -= nxt;
					out += nxt;
				}
			}
			return out == 0 ? dep[u] = 0 : out;
		}

	public:
		void AddEdge(int u, int v, int w) {
			AddEdge_(u, v, w);
			AddEdge_(v, u, 0);
		}
		ll Query(int x, int y) {
			s = x, t = y;
			ans = 0;
			while(Bfs()) ans += Dfs(s, inf);
			return ans;
		}
};

const int N = 1e4 + 5;
const int M = 2e4 + 5;
const ll inf = 1e18;

MaxFlow<N << 3, M << 3, inf> flow;
int n1, n2, n3, m1, m2;
int s, t;

int id(int x, int tp) {
	if(tp == 1) return x * 2 - 1;		//book
	if(tp == 2) return x + 2 * n1;		//exercise
	if(tp == 3) return x + 2 * n1 + n2;	//answer
}

int main() {
	qread(n1, n2, n3);
	qread(m1);
	rep(i, 1, m1) {
		int x, y; qread(x, y);
		flow.AddEdge(id(x, 1), id(y, 2), 1);
	}
	qread(m2);
	rep(i, 1, m2) {
		int x, y; qread(x, y);
		flow.AddEdge(id(y, 3), id(x, 1) + 1, 1);
	}
	s = 2 * n1 + n2 + n3 + 1;
	t = s + 1;
	rep(i, 1, n1) flow.AddEdge(id(i, 1) + 1, id(i, 1), 1);
	rep(i, 1, n2) flow.AddEdge(id(i, 2), t, 1);
	rep(i, 1, n3) flow.AddEdge(s, id(i, 3), 1);
	qwrite(flow.Query(s, t), '\n');
	return 0;
}

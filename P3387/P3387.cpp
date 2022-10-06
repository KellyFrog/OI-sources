#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
#include <stack>

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

const int N = 1e4 + 5;
const int M = 1e5 + 5;

vi adj[N], dag[N];
int dfn[N], low[N], scc[N], ins[N], dfncnt, scccnt;
stack<int> s;
int n, m;
int a[N], sum[N], ind[N], dp[N];

void Tarjan(int u) {
	dfn[u] = low[u] = ++dfncnt;
	ins[u] = 1, s.push(u);
	for(int v : adj[u]) {
		if(dfn[v] == 0) {
			Tarjan(v);
			low[u] = min(low[v], low[u]);
		} else if(ins[v]) {
			low[u] = min(low[v], low[u]);
		}
	}
	if(dfn[u] == low[u]) {
		int x = 0; scccnt++;
		while((x = s.top()) != u) {
			scc[x] = scccnt;
			ins[x] = 0, s.pop();
		}
		scc[x] = scccnt;
		ins[x] = 0, s.pop();
	}
}

int main() {
	qread(n, m);
	qreadarr(a + 1, a + 1 + n);
	rep(i, 1, m) {
		int u, v; qread(u, v);
		adj[u].pb(v);
	}
	rep(i, 1, n) if(dfn[i] == 0) Tarjan(i);
	rep(i, 1, n) sum[scc[i]] += a[i];
	rep(u, 1, n) for(int v : adj[u]) if(scc[u] != scc[v]) dag[scc[u]].pb(scc[v]), ind[scc[v]]++;
	queue<int> q;
	rep(i, 1, scccnt) if(ind[i] == 0) dp[i] = sum[i], q.push(i);
	while(!q.empty()) {
		int u = q.front(); q.pop();
		for(int v : dag[u]) {
			dp[v] = max(dp[v], dp[u] + sum[v]);
			ind[v]--; if(ind[v] == 0) q.push(v);
		}
	}
	int ans = 0;
	rep(i, 1, scccnt) ans = max(ans, dp[i]);
	printf("%d\n", ans);
	return 0;
}

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

const int N = 3005;

pii a[N];
vi adj[N], dag[N];
int dfn[N], low[N], ins[N], scc[N], in[N], dfncnt, scccnt;
stack<int> s; 
int money[N], has[N], vis[N];
int n, m, p;

void Tarjan(int u) {
	dfn[u] = low[u] = ++dfncnt;
	ins[u] = 1; s.push(u);
	for(int v : adj[u]) {
		if(!dfn[v]) {
			Tarjan(v);
			low[u] = min(low[u], low[v]);
		} else if(ins[v]) {
			low[u] = min(low[u], low[v]);
		}
	}
	if(dfn[u] == low[u]) {
		int x;
		scccnt++;
		while((x = s.top()) != u) {
			scc[x] = scccnt;
			ins[x] = 0;
			s.pop();
		}
		scc[x] = scccnt;
		ins[x] = 0;
		s.pop();
	}
}

int main() {
	qread(n, p);
	rep(i, 1, p) {
		int x, y; qread(x, y);
		a[i] = mp(x ,y);
	}
	qread(m);
	rep(i, 1, m) {
		int u, v; qread(u, v);
		adj[u].pb(v);
	}
	rep(i, 1, n) if(!dfn[i]) Tarjan(i);
//	rep(i, 1, n) cerr << dfn[i] << " " << low[i] << " " << scc[i] << "\n";
	rep(u, 1, n) for(int v : adj[u]) if(scc[u] != scc[v]) dag[scc[u]].pb(scc[v]), in[scc[v]]++;
	rep(i, 1, p) money[scc[a[i].fi]] = money[scc[a[i].fi]] == 0 ? a[i].se : min(money[scc[a[i].fi]], a[i].se);
	queue<int> q;
	rep(i, 1, scccnt) if(!in[i]) q.push(i);
	ll res = 0;
	while(!q.empty()) {
		int u = q.front(); q.pop();
		if(!vis[u]) if(money[u]) vis[u] = 1, res += money[u];
		for(int v : dag[u]) {
			in[v]--;
			if(vis[u]) vis[v] = 1;
			if(in[v] == 0) q.push(v);
		}
	}
	rep(i, 1, n) if(!vis[scc[i]]) return printf("NO\n%d\n", i), 0;
	printf("YES\n%d\n", res);
	return 0;
}

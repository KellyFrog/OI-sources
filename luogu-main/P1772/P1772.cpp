#include <bits/stdc++.h>

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

const int N = 105;
const int T = 105;
const ll inf = 1e8;

int t, n, m, k, d;
bool ok[T][N], vis[N], inq[N];
vc<pii> adj[N];
ll dis[T][T][N], dp[T];

void Dij(int l, int r) {
	rep(i, 1, n) dis[l][r][i] = inf, inq[i] = 0, vis[i] = 0;
	rep(i, 1, n) rep(j, l, r) if(ok[j][i]) vis[i] = 1;
	pq<pii, vc<pii>, grt<pii> > q;
	q.push(mp(dis[l][r][1] = 0, 1));
	while(!q.empty()) {
		int u = q.top().se; q.pop();
		if(inq[u]) continue; inq[u] = 1;
		for(auto x : adj[u]) {
			int v = x.fi, w = x.se;
			if(dis[l][r][u] + w < dis[l][r][v] && !vis[v]) q.push(mp(dis[l][r][v] = dis[l][r][u] + w, v));
		}
	}
}

int main() {
	qread(t, n, k, m);
	rep(i, 1, m) {
		int u, v, w; qread(u, v, w);
		adj[u].pb(mp(v, w)), adj[v].pb(mp(u, w));
	}
	qread(d);
	rep(i, 1, d) {
		int p, l, r; qread(p, l, r);
		rep(j, l, r) ok[j][p] = 1;
	}
	rep(i, 1, t) rep(j, i, t) Dij(i, j);
	rep(i, 1, t) {
		dp[i] = 1ll*dis[1][i][n]*i;
		rep(j, 0, i-1) dp[i] = min(dp[i], dp[j]+1ll*(i-j)*dis[j+1][i][n]+k);
	}
	printf("%d\n", dp[t]);
	return 0;
}

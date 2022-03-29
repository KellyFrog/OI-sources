#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <map>

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

const int N = 1005;
const int INF = 1e9 + 5;

int a[N][N];
int mx[N][N], mn[N][N];
int n, m, p;

int main() {
	qread(n, m, p);
	rep(i, 1, n) rep(j, 1, m) qread(a[i][j]);
	deque<pii> q1, q2;
	rep(i, 1, n) {
		q1.clear(), q2.clear();
		rep(j, 1, m) {
			while(!q1.empty() && q1.back().se < a[i][j]) q1.pop_back();
			q1.pb(mp(j, a[i][j]));
			if(j >= p) {
				if(!q1.empty() && q1.front().fi <= j - p) q1.pop_front();
				mx[i][j-p+1] = q1.front().se;
			}
			while(!q2.empty() && q2.back().se > a[i][j]) q2.pop_back();
			q2.pb(mp(j, a[i][j]));
			if(j >= p) {
				if(!q2.empty() && q2.front().fi <= j - p) q2.pop_front();
				mn[i][j-p+1] = q2.front().se;
			}
		}
	}
	int ans = INF;
	rep(j, 1, m - p + 1) {
		q1.clear(), q2.clear();
		rep(i, 1, n) {
			int mini = -1, maxi = -1;
			while(!q1.empty() && q1.back().se < mx[i][j]) q1.pop_front();
			q1.pb(mp(i, mx[i][j]));
			if(i >= p) {
				if(!q1.empty() && q1.front().fi <= i - p) q1.pop_front();
				maxi = q1.front().se;
			}
			while(!q2.empty() && q2.back().se > mn[i][j]) q2.pop_front();
			q2.pb(mp(i, mn[i][j]));
			if(i >= p) {
				if(!q2.empty() && q2.front().fi <= i - p) q2.pop_front();
				mini = q2.front().se;
			}
			if(maxi != -1) ans = min(ans, maxi - mini);
//			cerr << i << " " << j << " " << maxi << " " << mini << " " << maxi - mini << "\n";
		}
	}
	printf("%d\n", ans);
	return 0;
}

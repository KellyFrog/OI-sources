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
}
using namespace IO;

#define rep(i, s, t) for(rg int (i) = s; (i) <= t; (i)++)

/*templates end here*/

const int N = 1e6 + 5;

int maxi[N << 2];
int a[N];
int x, y, n, q;

void Build(int cur, int l, int r) {
	if(l == r) return maxi[cur] = a[l], void();
	rg int mid = l + r >> 1;
	Build(cur << 1, l, mid), Build(cur << 1 | 1, mid + 1, r);
	maxi[cur] = max(maxi[cur << 1], maxi[cur << 1 | 1]);
}

int Max(int cur, int ql, int qr, int l, int r) {
	if(ql <= l && r <= qr) return maxi[cur];
	rg int mid = l + r >> 1;
	rg int res = 0;
	if(ql <= mid) res = max(res, Max(cur << 1, ql, qr, l, mid));
	if(mid < qr) res = max(res, Max(cur << 1 | 1, ql, qr, mid + 1, r));
	return res;
}

int main() {
	qread(x, y);
	n = x * y / __gcd(x, y);
	rep(i, 1, n) a[i] = i % x + i % y;
	Build(1, 1, n);
	qread(q);
	while(q--) {
		rg int l, r;
		qread(l, r);
		printf("%d\n", r - l + 1 >= n ? Max(1, 1, n, 1, n) : (r - 1) % n + 1 < (l - 1) % n + 1 ? max(Max(1, 1, (r - 1) % n + 1, 1, n), Max(1, (l - 1) % n + 1, n, 1, n)) : Max(1, (l - 1) % n + 1, (r - 1) % n + 1, 1, n));
	}
}

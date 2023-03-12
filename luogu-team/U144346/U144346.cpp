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

const int N = 4e5 + 5;

struct Query {
	int op, x, y;
	int bef, aft;
};

int fa[N << 1], sys[N], sysrt[N], rtcnt;
int a[N], b[N], c[N << 1], sz;
Query op[N];
int sum[N << 5], lson[N << 5], rson[N << 5], rt[N << 1], cnt;
int n, m, q, p;

void Add(int& cur, int p, int x, int l, int r) {
	if(cur == 0) cur = ++cnt;
	sum[cur] += x;
	if(l == r) return;
	rg int mid = l + r >> 1;
	if(p <= mid) Add(lson[cur], p, x, l, mid);
	else Add(rson[cur], p, x, mid + 1, r);
}

int Kth(int cur, int k, int l, int r) {
	if(sum[cur] < k) return -1;
	if(cur == 0) return -1;
	if(l == r) return l;
	rg int mid = l + r >> 1;
	if(k <= sum[lson[cur]]) return Kth(lson[cur], k, l, mid);
	else return Kth(rson[cur], k - sum[lson[cur]], mid + 1, r);
}

void Merge(int& cur, int old, int l, int r) {
	if(cur == 0 || old == 0) return cur += old, void();
	sum[cur] += sum[old];
	if(l == r) return;
	rg int mid = l + r >> 1;
	Merge(lson[cur], lson[old], l, mid);
	Merge(rson[cur], rson[old], mid + 1, r);
}

int Find(int x) {
	return x == fa[x] ? x : fa[x] = Find(fa[x]);
}

//没能清空，需要一个新的数组

int main() {
	qread(q, n, m);
	rep(i, 1, n) qread(a[i]), c[i] = b[i] = a[i];
	sz = n;
	rep(i, 1, m + q) fa[i] = i;
	rep(i, 1, m) sysrt[i] = i;
	rtcnt = m;
	rep(i, 1, q) {
		qread(op[i].op);
		if(op[i].op == 2) qread(op[i].x);
		else qread(op[i].x, op[i].y);
		if(op[i].op == 3) op[i].bef = b[op[i].x], c[++sz] = op[i].aft = (b[op[i].x] += op[i].y);
	}
	sort(c + 1, c + 1 + sz);
	p = unique(c + 1, c + 1 + sz) - (c + 1);
	rep(i, 1, q) if(op[i].op == 3) op[i].bef = lower_bound(c + 1, c + 1 + p, op[i].bef) - c, op[i].aft = lower_bound(c + 1, c + 1 + p, op[i].aft) - c;
	rep(i, 1, n) b[i] = lower_bound(c + 1, c + 1 + p, a[i]) - c;
	rep(i, 1, q) {
		//cerr << "query=" << op[i].op << " " << op[i].x << " " << op[i].y << endl;
		if(op[i].op == 1) {
			sysrt[op[i].y] = Find(sysrt[op[i].y]);
			//cerr << "added " << b[op[i].x] << " to " << sysrt[op[i].y] << endl;
			Add(rt[sysrt[op[i].y]], b[op[i].x], 1, 1, sz);
			sys[op[i].x] = op[i].y;
		} else if(op[i].op == 2) {
			sysrt[sys[op[i].x]] = Find(sysrt[sys[op[i].x]]);
			//cerr << "deled " << b[op[i].x] << " from " << sysrt[sys[op[i].x]] << endl;
			Add(rt[sysrt[sys[op[i].x]]], b[op[i].x], -1, 1, sz);
			sys[op[i].x] = 0;
		} else if(op[i].op == 3) {
			//cerr << "replaced " << b[op[i].x] << " to " << op[i].aft << " in " << sysrt[sys[op[i].x]] << endl;
			sysrt[sys[op[i].x]] = Find(sysrt[sys[op[i].x]]);
			Add(rt[sysrt[sys[op[i].x]]], b[op[i].x], -1, 1, sz);
			b[op[i].x] = op[i].aft;
			Add(rt[sysrt[sys[op[i].x]]], b[op[i].x], 1, 1, sz);
		} else if(op[i].op == 4) {
			sysrt[op[i].x] = Find(sysrt[op[i].x]);	
			sysrt[op[i].y] = Find(sysrt[op[i].y]);
			//cerr << "merged " << sysrt[op[i].x] << " " << sysrt[op[i].y] << endl;
			Merge(rt[sysrt[op[i].x]], rt[sysrt[op[i].y]], 1, sz);
			fa[sysrt[op[i].y]] = sysrt[op[i].x];
			sysrt[op[i].y] = ++rtcnt;
		} else {
			sysrt[op[i].x] = Find(sysrt[op[i].x]);
			//cerr << "kthed " << op[i].y << " " << sysrt[op[i].x] << endl;
			rg int res = Kth(rt[sysrt[op[i].x]], op[i].y, 1, sz);
			qwrite(res == -1 ? -1 : c[res], '\n');
		}
	}
	return 0;
}

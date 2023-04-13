// Problem: P7963 [NOIP2021] 棋局【民间数据】
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7963
// Memory Limit: 1 MB
// Time Limit: 4000 ms

/*
 * Author: chenkaifeng @BDFZ
 */
 
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define pf push_front
#define rep(i, s, t) for (int i = s; i <= t; ++i)
#define per(i, s, t) for (int i = t; i >= s; --i)

namespace nqio{const unsigned R=4e5,W=4e5;char*a,*b,i[R],o[W],*c=o,*d=o+W,h[40],*p=h,y;bool s;struct q{void r(char&x){x=a==b&&(b=(a=i)+fread(i,1,R,stdin),a==b)?-1:*a++;}void f(){fwrite(o,1,c-o,stdout);c=o;}~q(){f();}void w(char x){*c=x;if(++c==d)f();}q&operator>>(char&x){do r(x);while(x<=32);return*this;}q&operator>>(char*x){do r(*x);while(*x<=32);while(*x>32)r(*++x);*x=0;return*this;}template<typename t>q&operator>>(t&x){for(r(y),s=0;!isdigit(y);r(y))s|=y==45;if(s)for(x=0;isdigit(y);r(y))x=x*10-(y^48);else for(x=0;isdigit(y);r(y))x=x*10+(y^48);return*this;}q&operator<<(char x){w(x);return*this;}q&operator<<(char*x){while(*x)w(*x++);return*this;}q&operator<<(const char*x){while(*x)w(*x++);return*this;}template<typename t>q&operator<<(t x){if(!x)w(48);else if(x<0)for(w(45);x;x/=10)*p++=48|-(x%10);else for(;x;x/=10)*p++=48|x%10;while(p!=h)w(*--p);return*this;}}qio;}using nqio::qio;

#define OK debug("OK!\n")
#ifndef ONLINE_JUDGE
namespace debuger{void debug(const char *s) {cerr << s;}template<typename T1,typename... T2>void debug(const char*s, const T1 x, T2...ls) { int p=0; while(*(s + p)!='\0') {if(*(s+p)=='{'&&*(s+p+1)=='}'){cerr << x;debug(s + p + 2, ls...);return;}cerr << *(s + p++);}}}using debuger::debug;
#else
#define debug(...) void(0)
#endif

// const int mod = 1e9 + 7;
const int mod = 998244353;

int qpow(int x, ll p) {
	int res = 1, base = x;
	while(p) {
		if(p & 1) res = 1ll * res * base % mod;
		base = 1ll * base * base % mod;
		p >>= 1;
	}
	return res;
}

template<typename T> inline void upd(T& x, const T& y) {	x += y;	if(x >= mod) x -= mod; }
template<typename T> inline void upd(T& x, const T& y, const T& z) { x = y + z; if(x >= mod) x -= mod; }

/* template ends here */

std::mt19937 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

const int N = 2e5 + 5;
const int L = 20;

char S1[N], S2[N];
int n, m, q;

inline int id1(int i, int j) { return (i-1) * m + j; }
inline int id2(int i, int j) { return (j-1) * n + i; }

namespace seg1 {
	int rt[N][2], lson[N*L], rson[N*L], sum[N*L];
	set<int> ss[N*L];
	int tcnt;
	
	inline void insert(int& rt, int p, int id, int l, int r) {
		if(!rt) {
			rt = ++tcnt;
			sum[rt] = lson[rt] = rson[rt] = 0;
			ss[rt].clear();
		}
		if(l == r) {
			ss[rt].insert(id);
			sum[rt] = ss[rt].size();
			return;
		}
		int mid = (l + r) >> 1;
		if(p <= mid) insert(lson[rt], p, id, l, mid);
		else insert(rson[rt], p, id, mid+1, r);
		sum[rt] = sum[lson[rt]] + sum[rson[rt]];
	}
	
	inline void erase(int& rt, int p, int id, int l, int r) {
		if(!rt) return;
		if(l == r) {
			ss[rt].erase(id);
			sum[rt] = ss[rt].size();
			return;
		}
		int mid = (l + r) >> 1;
		if(p <= mid) erase(lson[rt], p, id, l, mid);
		else erase(rson[rt], p, id, mid+1, r);
		sum[rt] = sum[lson[rt]] + sum[rson[rt]];
	}
	
	inline void merge(int& rt1, int rt2, int l, int r) {
		debug("seg1::merge({}, {}, {}, {}), sum = {} {}\n", rt1, rt2, l, r, sum[rt1], sum[rt2]);
		if(!rt1 || !rt2) return rt1 = rt1 + rt2, void();
		if(l == r) {
			if(ss[rt1].size() < ss[rt2].size()) swap(rt1, rt2);
			for(int x : ss[rt2]) ss[rt1].insert(x);
			return;
		}
		int mid = (l + r) >> 1;
		merge(lson[rt1], lson[rt2], l, mid);
		merge(rson[rt1], rson[rt2], mid+1, r);
		sum[rt1] = sum[lson[rt1]] + sum[rson[rt1]];
	}
	
	inline int query(int rt, int ql, int qr, int l, int r) {
		if(!rt) return 0;
		if(l == 1 && r == q) debug("seg1::query({}, {})\n", l, r);
		if(ql <= l && r <= qr) {
			debug("get [{}, {}] at {}, sum = {}\n", l, r, rt, sum[rt]);
			return sum[rt];
		}
		int mid = (l + r) >> 1;
		int res = 0;
		if(ql <= mid) res += query(lson[rt], ql, qr, l, mid);
		if(mid < qr) res += query(rson[rt], ql, qr, mid+1, r);
		return res;
	}
	
	inline bool find(int rt, int p, int id, int l, int r) {
		if(!rt) return 0;
		if(l == r) return ss[rt].count(id);
		int mid = l + r >> 1;
		if(p <= mid) return find(lson[rt], p, id, l, mid);
		else return find(rson[rt], p, id, mid+1, r);
	}
	
	inline void clear() {
		memset(rt, 0, sizeof rt);
		tcnt = 0;
	}
}

namespace seg2 {
	int rt[N][2], lson[N*L*4], rson[N*L*4], sum[N*L*4];
	int tcnt;
	
	inline void add(int& rt, int p, int val, int l, int r) {
		if(!rt) {
			rt = ++tcnt;
			sum[rt] = lson[rt] = rson[rt] = 0;
		}
		sum[rt] += val;
		if(l == r) return;
		int mid = (l + r) >> 1;
		if(p <= mid) add(lson[rt], p, val, l, mid);
		else add(rson[rt], p, val, mid+1, r);
	}
	
	inline void merge(int& rt1, int rt2, int l, int r) {
		if(!rt1 || !rt2) return rt1 = rt1 + rt2, void();
		if(l == r) return sum[rt1] = 1, void();
		int mid = (l + r) >> 1;
		merge(lson[rt1], lson[rt2], l, mid);
		merge(rson[rt1], rson[rt2], mid+1, r);
		sum[rt1] = sum[lson[rt1]] + sum[rson[rt1]];
	}
	
	inline int query(int rt, int ql, int qr, int l, int r) {
		if(!rt) return 0;
		if(l == 1 && r == n*m) debug("seg2::query = {} {}\n", ql, qr);
		if(ql <= l && r <= qr) return sum[rt];
		int mid = (l + r) >> 1;
		int res = 0;
		if(ql <= mid) res += query(lson[rt], ql, qr, l, mid);
		if(mid < qr) res += query(rson[rt], ql, qr, mid+1, r);
		return res;
	}
	
	inline void clear() {
		memset(rt, 0, sizeof rt);
		tcnt = 0;
	}
}

int col[N], lv[N], qcol[N], qlv[N], qx[N], qy[N], qi[N], ans[N];
int u1[N], u2[N], u3[N];
int l1[N], l2[N], r1[N], r2[N];

inline int find1(int x) { return u1[x] == x ? x : u1[x] = find1(u1[x]); }
inline int find2(int x) { return u2[x] == x ? x : u2[x] = find2(u2[x]); }
inline int find3(int x) { return u3[x] == x ? x : u3[x] = find3(u3[x]); }
inline void umerge1(int x, int y) {
	int fx = find1(x), fy = find1(y);
	if(fx != fy) { u1[fy] = fx; l1[fx] = min(l1[fx], l1[fy]), r1[fx] = max(r1[fx], r1[fy]); }
}
inline void umerge2(int x, int y) {
	int fx = find2(x), fy = find2(y);
	if(fx != fy) { u2[fy] = fx; l2[fx] = min(l2[fx], l2[fy]), r2[fx] = max(r2[fx], r2[fy]); }
}

void solve() {
	seg1::clear();
	seg2::clear();
	memset(col, -1, sizeof col);
	memset(S1, 0, sizeof S1);
	memset(S2, 0, sizeof S2);
	
	debug("-----------solve------------\n");
	
	cin >> n >> m >> q;
	rep(i, 1, n) rep(j, 1, m-1) cin >> S1[id1(i, j)];
	rep(i, 1, n-1) rep(j, 1, m) cin >> S2[id1(i, j)];
	
	rep(i, 1, n) rep(j, 1, m) {
		int p = id1(i, j);
		u1[p] = u2[p] = u3[p] = p;
		l1[p] = r1[p] = j;
		l2[p] = r2[p] = i;
		seg2::add(seg2::rt[p][0], id1(i, j), 1, 1, n*m);
		seg2::add(seg2::rt[p][1], id2(i, j), 1, 1, n*m);
	}
	
	debug("init ok!\n");
	
	rep(i, 1, q) {
		cin >> qcol[i] >> qlv[i] >> qx[i] >> qy[i];
		qi[i] = id1(qx[i], qy[i]);
		col[qi[i]] = qcol[i];
		lv[qi[i]] = qlv[i];
	}
	
	auto update = [&](int x, int y) {
		assert(col[x] == -1);
		int fx = find3(x), fy = find3(y);
		if(col[y] == -1) {
			if(fx == fy) return;
			seg2::merge(seg2::rt[fx][0], seg2::rt[fy][0], 1, n*m);
			seg2::merge(seg2::rt[fx][1], seg2::rt[fy][1], 1, n*m);
			seg1::merge(seg1::rt[fx][0], seg1::rt[fy][0], 1, q);
			seg1::merge(seg1::rt[fx][1], seg1::rt[fy][1], 1, q);
			
			u3[fy] = fx;
		} else {
			debug("seg1::insert col = {}, lv = {}, pid = {} to rt[{}]\n", col[y], lv[y], y, fx);
			seg1::insert(seg1::rt[fx][col[y]], lv[y], y, 1, q);
		}
	};
	
	auto combine = [&](int i, int j) {
		debug("combine = {} {}\n", i, j);
		int ij = id1(i, j);
		if(col[ij] != -1) return;
		debug("ok ij = {}\n", ij);
		
		if(j<m && S1[ij] == '2' && col[ij+1] == -1) umerge1(ij, ij+1);
		if(j>1 && S1[ij-1] == '2' && col[ij-1] == -1) umerge1(ij, ij-1);
		if(i>1 && S2[ij-m] == '2' && col[ij-m] == -1) umerge2(ij, ij-m);
		if(i<n && S2[ij] == '2' && col[ij+m] == -1) umerge2(ij, ij+m);
		
		if(j<m && S1[ij] == '3') update(ij, ij+1);
		if(j>1 && S1[ij-1] == '3') update(ij, ij-1);
		if(i>1 && S2[ij-m] == '3') update(ij, ij-m);
		if(i<n && S2[ij] == '3') update(ij, ij+m);
	};
	
	rep(i, 1, n) rep(j, 1, m) {
		combine(i, j);
	}
	
	auto getans1 = [&](int i, int j, int l, int c) {
		int res = 0;
		int ij = id1(i, j);
		
		auto check = [&](int x, int y) {
			debug("getans1::check = {} {} {} {} {} {}\n", i, j, x, y, l, c);
			int xy = id1(x, y);
			int ok1 = 0, ok2 = 0;
			if(col[xy] == -1) {
				return int(find3(xy) != find3(ij));
			}
			if(lv[xy] > l || c == col[xy]) return 0;
			debug("ok\n");
			return int(!seg1::find(seg1::rt[find3(ij)][col[xy]], lv[xy], xy, 1, q));
		};
		
		if(j<m && S1[ij] == '1') res += check(i, j+1);
		if(j>1 && S1[ij-1] == '1') res += check(i, j-1);
		if(i<n && S2[ij] == '1') res += check(i+1, j);
		if(i>1 && S2[ij-m] == '1') res += check(i-1, j);
		
		return res;
	};
	
	auto getans2 = [&](int i, int j, int l, int c) {
		debug("getans2 = {} {} {} {}\n", i, j, l, c);
		int res = 0;
		int ij = id1(i, j);
		int p = ij;
		int rt1 = find1(ij), rt2 = find2(ij);
		
		res += r1[rt1] - l1[rt1] + 1; 
		res += r2[rt2] - l2[rt2] + 1;
		
		debug("get range = [{}, {}], [{}, {}], res = {}\n", l1[rt1], r1[rt1], l2[rt2], r2[rt2], res);
		
		res -= seg2::query(seg2::rt[find3(ij)][0], id1(i, l1[rt1]), id1(i, r1[rt1]), 1, n*m);
		res -= seg2::query(seg2::rt[find3(ij)][1], id2(l2[rt2], j), id2(r2[rt2], j), 1, n*m);
		
		debug("get res = {}\n", res);
		
		auto check = [&](int i, int j) {
			debug("check = {} {}\n", i, j);
			int ij = id1(i, j);
			if(col[ij] != c && lv[ij] <= l) {
				debug("ok\n");
				if(!seg1::find(seg1::rt[p][col[ij]], lv[ij], ij, 1, q)) return 1;
			}
			debug("ret = 0\n");
			return 0;
		};
		
		if(r1[rt1] < m && S1[id1(i, r1[rt1])] == '2') res += check(i, r1[rt1]+1);
		if(l1[rt1] > 1 && S1[id1(i, l1[rt1]-1)] == '2') res += check(i, l1[rt1]-1);
		if(r2[rt2] < n && S2[id1(r2[rt2], j)] == '2') res += check(r2[rt2]+1, j);
		if(l2[rt2] > 1 && S2[id1(l2[rt2]-1, j)] == '2') res += check(l2[rt2]-1, j);
		
		return res;
	};
	
	auto getans3 = [&](int i, int j, int l, int c) {
		int res = 0;
		int ij = id1(i, j);
		
		res += seg2::sum[seg2::rt[find3(ij)][0]] - 1;
		
		debug("dsu size = {}\n", res);
		
		debug("seg1::query(rt[{}][{}], {})\n", find3(ij), c^1, l);
		
		res += seg1::query(seg1::rt[find3(ij)][c^1], 1, l, 1, q);
		
		return res;
	};
	
	auto print = [&]() {
		/*
		debug("uni2:\n");
		rep(i, 1, n) rep(j, 1, m) cerr << find2(id1(i, j)) << " \n"[j == m];
		debug("uni3:\n");
		rep(i, 1, n) rep(j, 1, m) cerr << find3(id1(i, j)) << " \n"[j == m];
		*/
	};
	
	print();
	
	per(i, 1, q) {
		
		debug("-----------i = {}-----------\n", i);
		
		int c = qcol[i], clv = qlv[i];
		int ij = qi[i];
		
		col[ij] = -1;
		lv[ij] = 0;
		
		combine(qx[i], qy[i]);
		
		print();
		
		debug("erase = {} {} {} {} {}, {} {}\n", ij, ij+1, ij-1, ij+m, ij-1, clv, i);
		seg1::erase(seg1::rt[find3(ij)][c], clv, ij, 1, q);
		seg1::erase(seg1::rt[find3(ij+1)][c], clv, ij, 1, q);
		seg1::erase(seg1::rt[find3(ij-1)][c], clv, ij, 1, q);
		seg1::erase(seg1::rt[find3(ij+m)][c], clv, ij, 1, q);
		seg1::erase(seg1::rt[find3(ij-m)][c], clv, ij, 1, q);
		
		int res1 = 0, res2 = 0, res3 = 0, res4 = 0;
		
		res1 = getans1(qx[i], qy[i], clv, c);
		res2 = getans2(qx[i], qy[i], clv, c);
		res3 = getans3(qx[i], qy[i], clv, c);
		
		ans[i] = res1 + res2 + res3;
		
		debug("res = {} {} {}\n", res1, res2, res3);
	}
	
	rep(i, 1, q) cout << ans[i] << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	int t;
	cin >> t;
	while(t--) solve();
	
	return 0;
}

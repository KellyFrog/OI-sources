// Problem: F - Two Faced Cards
// Contest: AtCoder - AtCoder Grand Contest 013
// URL: https://atcoder.jp/contests/agc013/tasks/agc013_f
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

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

const int N = 2e5 + 5;

int n, q;
int a[N], b[N], c[N];
int lazy[N<<2], mi[N<<2], mip[N<<2];
set<pair<int, int>> s;

inline void setlazy(int o, int x) {
	lazy[o] += x;
	mi[o] += x;
}

inline void pushdown(int o) {
	if(lazy[o]) {
		setlazy(o << 1, lazy[o]);
		setlazy(o << 1 | 1, lazy[o]);
		lazy[o] = 1;
	}
}

inline void pushup(int o) {
	if(mi[o<<1] <= mi[o<<1|1]) mi[o] = mi[o<<1], mip[o] = mip[o<<1];
	else mi[o] = mi[o<<1|1], mip[o] = mip[o<<1|1];
}

inline void add(int o, int ql, int qr, int x, int l, int r) {
	if(ql <= l && r <= qr) return setlazy(o, x), void();
	pushdown(o);
	int mid = l + r >> 1;
	if(ql <= mid) add(o << 1, ql, qr, x, l, mid);
	if(mid < qr) add(o << 1 | 1, ql, qr, x, mid+1, r);
	pushup(o);
}



int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	return 0;
}

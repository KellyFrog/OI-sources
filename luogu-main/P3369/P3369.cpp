// Problem: P3369 【模板】普通平衡树
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3369
// Memory Limit: 128 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define rep(i, s, t) for(int i = (s); i <= (t); ++i)
#define per(i, s, t) for(int i = (t); i >= (s); --i)
#define fi first
#define se second
#define pb push_back
#define mp make_pair

mt19937 mtrnd(0x114514);

const int N = 1e5 + 5;

int q;
int rt, siz[N], ls[N], rs[N], val[N], tt;
unsigned pri[N];

inline int newnode(int v) {
	int o = ++tt;
	siz[o] = 1, ls[o] = rs[o] = 0, val[o] = v;
	pri[o] = mtrnd();
	return o;
}

inline void pushup(int o) {
	siz[o] = siz[ls[o]] + siz[rs[o]] + 1;
}

// (-inf, v) and [v, +inf)
inline void splitval(int& o1, int& o2, int o, int v) {
	if(!o) {
		o1 = o2 = 0;
		return;
	}
	if(val[o] < v) {
		o1 = o;
		splitval(rs[o1], o2, rs[o], v);
		pushup(o1);
	} else {
		o2 = o;
		splitval(o1, ls[o2], ls[o], v);
		pushup(o2);
	}
}

// siz1=v, siz2=tot-v
inline void splitsiz(int& o1, int& o2, int o, int k) {
	if(!o) {
		o1 = o2 = 0;
		return;
	}
	if(k >= siz[ls[o]] + 1) {
		o1 = o;
		splitsiz(rs[o1], o2, rs[o], k-siz[ls[o]]-1);
		pushup(o1);
	} else {
		o2 = o;
		splitsiz(o1, ls[o2], ls[o], k);
		pushup(o2);
	}
}

inline void merge(int& o, int o1, int o2) {
	if(!o1 || !o2) {
		o = o1 + o2;
		return;
	}
	if(pri[o1] < pri[o2]) {
		o = o1;
		merge(rs[o], rs[o1], o2);
		pushup(o);
	} else {
		o = o2;
		merge(ls[o], o1, ls[o2]);
		pushup(o);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	cin >> q;
	while(q--) {
		int op, x; cin >> op >> x;
		if(op == 1) {
			int o = newnode(x);
			int a, b; splitval(a, b, rt, x);
			merge(rt, a, o);
			merge(rt, rt, b);
		} else if(op == 2) {
			int a, b, c; splitval(a, b, rt, x), splitsiz(b, c, b, 1);
			merge(rt, a, c);
		} else if(op == 3) {
			int a, b; splitval(a, b, rt, x);
			cout << siz[a] + 1 << "\n";
			merge(rt, a, b);
		} else if(op == 4) {
			int a, b, c; splitsiz(a, b, rt, x-1), splitsiz(b, c, b, 1);
			cout << val[b] << "\n";
			merge(rt, a, b), merge(rt, rt, c);
		} else if(op == 5) {
			int a, b, c; splitval(a, c, rt, x), splitsiz(a, b, a, siz[a]-1);
			cout << val[b] << "\n";
			merge(rt, a, b), merge(rt, rt, c);
		} else if(op == 6) {
			int a, b, c; splitval(a, b, rt, x+1), splitsiz(b, c, b, 1);
			cout << val[b] << "\n";
			merge(rt, a, b), merge(rt, rt, c);
		}
	}

	return 0;
}


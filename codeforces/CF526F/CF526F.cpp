// Problem: CF526F Pudding Monsters
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF526F
// Memory Limit: 250 MB
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

const int N = 3e5 + 5;

int n, a[N];
int t[N<<2], tc[N<<2], lazy[N<<2];
int s1[N], s2[N], t1, t2;

inline void setlazy(int o, int x) {
	t[o] += x, lazy[o] += x;
}

inline void pushdown(int o) {
	if(lazy[o]) {
		setlazy(o << 1, lazy[o]);
		setlazy(o << 1 | 1, lazy[o]);
		lazy[o] = 0;
	}
}

inline void pushup(int o) {
	t[o] = min(t[o << 1], t[o << 1 | 1]);
	tc[o] = tc[o << 1] * (t[o] == t[o << 1]) + tc[o << 1 | 1] * (t[o] == t[o << 1 | 1]);
}

inline void add(int o, int ql, int qr, int x, int l, int r) {
	if(ql <= l && r <= qr) return setlazy(o, x);
	pushdown(o);
	int mid = l + r >> 1;
	if(ql <= mid) add(o << 1, ql, qr, x, l, mid);
	if(mid < qr) add(o << 1 | 1, ql, qr, x, mid + 1, r);
	pushup(o);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n;
	rep(i, 1, n) {
		int x, y; cin >> x >> y;
		a[x] = y;
	}
	rep(i, 1, 4*n) tc[i] = 1;
	rep(i, 1, n) add(1, i, i, i, 1, n);
	ll ans = 0;
	rep(i, 1, n) {
		while(t1 && a[s1[t1]] < a[i]) {
			add(1, s1[t1-1] + 1, s1[t1], -a[s1[t1]], 1, n);
			--t1;
		}
		s1[++t1] = i;
		add(1, s1[t1-1] + 1, s1[t1], a[s1[t1]], 1, n);

		while(t1 && a[s2[t2]] > a[i]) {
			add(1, s2[t2-1] + 1, s2[t2], a[s2[t2]], 1, n);
			--t2;
		}
		s2[++t2] = i;
		add(1, s2[t2-1] + 1, s2[t2], -a[s2[t2]], 1, n);
		if(t[1] == i) ans += tc[1];
	}

	cout << ans << "\n";

	return 0;
}

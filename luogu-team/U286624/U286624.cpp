// Problem: U286624 蓄水池
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/U286624
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// Create Time: 2023-03-19 19:44:10
// Input/Output: stdin/stdout
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

struct T {
	int l, r, c;
};

int n, q, c;
int a[N];
T t[N<<2];

inline T merge(const T& t1, const T& t2) {
	auto [l1, r1, c1] = t1;
	auto [l2, r2, c2] = t2;
	return {max(l1, l2-c1), min(max(r1, l2-c1), r2-c1), c1+c2};
}

inline void pushup(int o) {
	t[o] = merge(t[o<<1], t[o<<1|1]);
}

inline void modify(int o, int p, int v, int l, int r) {
	if(l == r) {
		t[o] = {0, c, v};
		return;
	}
	int mid = l + r >> 1;
	if(p <= mid) modify(o << 1, p, v, l, mid);
	else modify(o << 1 | 1, p, v, mid + 1, r);
	pushup(o);
}

inline void build(int o, int l, int r) {
	if(l == r) {
		t[o] = {0, c, a[l]};
		return;
	}
	int mid = l + r >> 1;
	build(o << 1, l, mid);
	build(o << 1 | 1, mid + 1, r);
	pushup(o);
}

inline T query(int o, int ql, int qr, int l, int r) {
	if(ql <= l && r <= qr) {
		return t[o];
	}
	int mid = l + r >> 1;
	T res = {0, c, 0};
	if(ql <= mid) res = merge(res, query(o << 1, ql, qr, l, mid));
	if(mid < qr) res = merge(res, query(o << 1 | 1, ql, qr, mid+1, r));
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> q >> c;
	rep(i, 1, n) cin >> a[i<<1], a[i<<1] *= -1;
	build(1, 1, 2*n);
	while(q--) {
		int op; cin >> op;
		if(op == 1) {
			int x, y; cin >> x >> y;
			a[2*x-1] += y;
			modify(1, 2*x-1, a[2*x-1], 1, 2*n);
		} else if(op == 2) {
			int x, y; cin >> x >> y;
			a[2*x] = -y;
			modify(1, 2*x, a[2*x], 1, 2*n);
		} else {
			int x; cin >> x;
			auto [l, r, ans] = query(1, 1, 2*x, 1, 2*n);
			cout << min(c, max(0, min(r, max(l, 0)) + ans)) << "\n";
		}
	}

	
	return 0;
}

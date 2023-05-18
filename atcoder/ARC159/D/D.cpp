// Problem: D - LIS 2
// Contest: AtCoder - AtCoder Regular Contest 159
// URL: https://atcoder.jp/contests/arc159/tasks/arc159_d
// Memory Limit: 1024 MB
// Time Limit: 2500 ms
// Create Time: 2023-04-12 20:20:51
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
const int inf = 0x3f3f3f3f;

int n, a[N], b[N], c[N], f[N];

struct segt {
int t[N<<2];

inline void pushup(int o) {
	t[o] = max(t[o<<1], t[o<<1|1]);
}

inline int query(int o, int ql, int qr, int l, int r) {
	if(ql > qr) return -inf;
	if(ql <= l && r <= qr) return t[o];
	int mid = l + r >> 1;
	int res = -inf;
	if(ql <= mid) res = max(res, query(o << 1, ql, qr, l, mid));
	if(mid < qr) res = max(res, query(o << 1 | 1, ql, qr, mid + 1, r));
	return res;
}

inline void modify(int o, int p, int v, int l, int r) {
	if(l == r) {
		t[o] = v;
		return;
	}
	int mid = l + r >> 1;
	if(p <= mid) modify(o << 1, p, v, l, mid);
	else modify(o << 1 | 1, p, v, mid + 1, r);
	pushup(o);
}

inline void build(int o, int l, int r) {
	t[o] = -inf;
	if(l == r) return;
	int mid = l + r >> 1;
	build(o << 1, l, mid);
	build(o << 1 | 1, mid + 1, r);
}

} t1, t2;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n;
	rep(i, 1, n) cin >> a[i] >> b[i], c[i] = b[i] + 1;
	sort(c + 1, c + n + 1);
	int m = unique(c + 1, c + n + 1) - c - 1;
	t1.build(1, 1, m);
	t2.build(1, 1, m);
	rep(i, 1, n) {
		f[i] = b[i] - a[i] + 1;
		int p = lower_bound(c + 1, c + m + 1, a[i]) - c;
		int v1 = t1.query(1, p, m, 1, m);
		int v2 = t2.query(1, 1, p-1, 1, m);
		f[i] = max(f[i], v1 + b[i]);
		f[i] = max(f[i], v2 + b[i] - a[i] + 1);
		p = lower_bound(c + 1, c + m + 1, b[i] + 1) - c;
		t1.modify(1, p, f[i] - b[i], 1, m);
		t2.modify(1, p, f[i], 1, m);
	}
	int ans = 0;
	rep(i, 1, n) ans = max(ans, f[i]);
	cout << ans << "\n";
	return 0;
}

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

const int N = 1e6 + 5;

int n, m, q;
int a[N], b[N];

struct T {
	int ans, sum;
	T() {}
	T(int ans, int sum) : ans(ans), sum(sum) {}
} t[N<<2];

void pushup(int o) {
	t[o] = T(min(t[o<<1|1].ans, t[o<<1].ans + t[o<<1|1].sum), t[o<<1].sum + t[o<<1|1].sum);
}

inline void modify(int o, int p, int x, int l, int r) {
	if(l == r) {
		t[o].sum += x;
		t[o].ans = min(0, t[o].sum);
		return;
	}
	int mid = l + r >> 1;
	if(p <= mid) modify(o << 1, p, x, l, mid);
	else modify(o << 1 | 1, p, x, mid + 1, r);
	pushup(o);
}

inline int query(int o, int sum, int l, int r) {
	if(l == r) {
		if(sum + t[o].sum < 0) return l;
		return -1;
	}
	int mid = l + r >> 1;
	if(t[o<<1|1].ans + sum < 0) return query(o << 1 | 1, sum, mid + 1, r);
	else return query(o << 1, sum + t[o<<1|1].sum, l, mid);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> m;
	rep(i, 1, n) cin >> a[i], modify(1, a[i], -1, 1, 1e6);
	rep(i, 1, m) cin >> b[i], modify(1, b[i], 1, 1, 1e6);
	cin >> q;
	while(q--) {
		int op, x, y; cin >> op >> x >> y;
		if(op == 1) {
			modify(1, a[x], 1, 1, 1e6);
			modify(1, a[x] = y, -1, 1, 1e6);
		} else {
			modify(1, b[x], -1, 1, 1e6);
			modify(1, b[x] = y, 1, 1, 1e6);
		}
		cout << query(1, 0, 1, 1e6) << "\n";
	}
	return 0;
}

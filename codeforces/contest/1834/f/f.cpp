/*
 * Author: zhengguoge@codeforces
 * Create Time: 2023.06.18, 16:05:04 (UTC +8)
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

const int N = 4e5 + 5;
const int M = N * 22;

int n, q;
int a[N];
int rt[N][2], ls[M], rs[M], cnt[M], tt;

inline int newnode(int o) {
	int e = ++tt;
	ls[e] = ls[o], rs[e] = rs[o], cnt[e] = cnt[o];
	return e;
}

inline void ins(int& o1, int o2, int p, int l, int r) {
	o1 = newnode(o2);
	++cnt[o1];
	if(l == r) return;
	int mid = l + r >> 1;
	if(p <= mid) ins(ls[o1], ls[o2], p, l, mid);
	else ins(rs[o1], rs[o2], p, mid + 1, r);
}

inline int query(int o, int ql, int qr, int l, int r) {
	if(!o) return 0;
	if(ql <= l && r <= qr) return cnt[o];
	int mid = l + r >> 1;
	int res = 0;
	if(ql <= mid) res += query(ls[o], ql, qr, l, mid);
	if(mid < qr) res += query(rs[o], ql, qr, mid + 1, r);
	return res;
}

int solve(int p, bool rev) {
	int ans = 0;
	if(!rev) {
		int d = n - p + 1;
		ans += query(rt[p][0], -n, d-2, -n, n);
		ans += query(rt[n][0], -n, p-1, -n, n) - query(rt[p][0], -n, p-1, -n, n);
	} else {
		int d = n - p + 1;
		ans += query(rt[p][1], -n, p-1, -n, n);
		ans += query(rt[1][1], -n, d-2, -n, n) - query(rt[p][1], -n, d-2, -n, n);
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n;
	rep(i, 1, n) cin >> a[i];
	rep(i, 1, n) ins(rt[i][0], rt[i-1][0], a[i] - i, -n, n);
	per(i, 1, n) ins(rt[i][1], rt[i+1][1], a[i] - (n-i+1), -n, n);
	int p = n;
	bool rev = 0;
	cout << solve(p, rev) << "\n";
	cin >> q;
	while(q--) {
		int op; cin >> op;
		if(op == 1) {
			int k; cin >> k;
			p -= k;
			if(p < 1) p += n;
		} else if(op == 2) {
			int k; cin >> k;
			p += k;
			if(p > n) p -= n;
		} else {
			rev ^= 1;
		}
		cout << solve(p, rev) << "\n";
	}
	return 0;
}

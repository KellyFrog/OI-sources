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
const int M = N * 21;

int n, m, k;
pair<int, int> a[N];
int b[N];
ll ans = -1e18;
int rt[N], ls[M], rs[M], cnt[M], tt;
ll sum[M];

inline int newnode(int o) {
	int r = ++tt;
	ls[r] = ls[o];
	rs[r] = rs[o];
	cnt[r] = cnt[o];
	sum[r] = sum[o];
	return r;
}

inline void ins(int& o1, int o2, int p, int l, int r) {
	o1 = newnode(o2);
	sum[o1] += b[k-p+1];
	++cnt[o1];
	if(l == r) return;
	int mid = l + r >> 1;
	if(p <= mid) ins(ls[o1], ls[o2], p, l, mid);
	else ins(rs[o1], rs[o2], p, mid + 1, r);
}

inline ll query(int o1, int o2, int k, int l, int r) {
	if(k == 0) return 0;
	if(k == cnt[o1]-cnt[o2]) return sum[o1]-sum[o2];
	if(l == r) return 1ll * k * b[::k-l+1];
	int mid = l + r >> 1;
	if(k < cnt[ls[o1]]-cnt[ls[o2]]) return query(ls[o1], ls[o2], k, l, mid);
	else return query(rs[o1], rs[o2], k-(cnt[ls[o1]]-cnt[ls[o2]]), mid+1, r) + sum[ls[o1]]-sum[ls[o2]];
}

void solve(int l, int r, int ql, int qr) {
	if(l > r) return;
	int mid = l + r >> 1;
	ll res = -1e18;
	int j = -1;
	rep(i, ql, qr) {
		if(mid-i+1 < m) continue;
		ll s = query(rt[mid], rt[i-1], m, 1, k);
		ll sum = s - 2ll * (a[mid].fi - a[i].fi);
		if(sum > res) res = sum, j = i;
	}
	ans = max(ans, res);
	solve(l, mid-1, ql, j);
	solve(mid+1, r, j, qr);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> m;
	rep(i, 1, n) cin >> a[i].se >> a[i].fi;
	sort(a + 1, a + n + 1);
	rep(i, 1, n) b[i] = a[i].se;
	sort(b + 1, b + n + 1);
	k = unique(b + 1, b + n + 1) - b - 1;
	rep(i, 1, n) a[i].se = lower_bound(b + 1, b + k + 1, a[i].se) - b;
	rep(i, 1, n) ins(rt[i], rt[i-1], k-a[i].se+1, 1, k);
	solve(m, n, 1, n);
	cout << ans << "\n";
	
	return 0;
}

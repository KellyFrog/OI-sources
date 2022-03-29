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

mt19937_64 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

const int N = 1e6 + 5;

struct Seg {
	int mxc[N<<2], mxd[N<<2];
	
	inline void pushup(int o) {
		mxc[o] = max(mxc[o << 1], mxc[o << 1 | 1]);
		mxd[o] = max(mxd[o << 1], mxd[o << 1 | 1]);
	}
	
	inline void modify(int o, int p, int vc, int vd, int l, int r) {
		if(l == r) {
			mxc[o] = max(mxc[o], vc);
			mxd[o] = max(mxd[o], vd);
			return;
		}
		int mid = l + r >> 1;
		if(p <= mid) modify(o << 1, p, vc, vd, l, mid);
		else modify(o << 1 | 1, p, vc, vd, mid + 1, r);
		pushup(o);
	}
	
	inline void query(int o, int& tc, int& td, int ql, int qr, int l, int r) {
		if(ql <= l && r <= qr) {
			tc = max(tc, mxc[o]);
			td = max(td, mxd[o]);
			return;
		}
		int mid = l + r >> 1;
		if(ql <= mid) query(o << 1, tc, td, ql, qr, l, mid);
		if(mid < qr) query(o << 1 | 1, tc, td, ql, qr, mid + 1, r);
	}
	
	void clear() {
		memset(mxc, -1, sizeof mxc);
		memset(mxd, -1, sizeof mxd);
	}
} sa, sb;
int vala[N], valb[N];
int n;
int a[N], b[N], c[N], d[N];
int va[N], vb[N], pa, pb;

void solve() {
	sa.clear();
	sb.clear();
	memset(vala, 0x3f, sizeof vala);
	memset(valb, 0x3f, sizeof valb);
	cin >> n;
	rep(i, 1, n) cin >> a[i] >> b[i] >> c[i] >> d[i];
	rep(i, 1, n) va[i] = a[i], vb[i] = b[i];
	sort(va + 1, va + n + 1);
	sort(vb + 1, vb + n + 1);
	pa = unique(va + 1, va + n + 1) - va - 1;
	pb = unique(vb + 1, vb + n + 1) - vb - 1;
	rep(i, 1, n) a[i] = lower_bound(va + 1, va + pa + 1, a[i]) - va;
	rep(i, 1, n) b[i] = lower_bound(vb + 1, vb + pb + 1, b[i]) - vb;
	rep(i, 1, n) {
		sa.modify(1, a[i], c[i], d[i], 1, pa);
		sb.modify(1, b[i], c[i], d[i], 1, pb);
		
		vala[a[i]] = min(vala[a[i]], b[i]);
		valb[b[i]] = min(valb[b[i]], a[i]);
	}
	int mi = INT_MAX;
	rep(i, 1, n) mi = min(mi, c[i] + d[i]);
	ll ans = 1e18;
	rep(i, 1, pa) rep(j, 1, pb) {
		if(vala[i] > j) continue;
		if(valb[j] > i) continue;
		int mxc = -1, mxd = -1;
		if(i != pa) sa.query(1, mxc, mxd, i + 1, pa, 1, pa);
		if(j != pb) sb.query(1, mxc, mxd, j + 1, pb, 1, pb);
		if(mxc != -1) ans = min(ans, (ll)va[i] + vb[j] + mxc + mxd);
		else ans = min(ans, (ll)va[i] + vb[j] + mi);
	}
	cout << ans << "\n";
}

int main() {
	freopen("tinyds.in", "r", stdin);
	freopen("tinyds.out", "w", stdout);
	
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	int t;
	cin >> t;
	while(t--) solve();
	cout.flush();
	
	return 0;
}


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

const int N = 2e3 + 5;

int n;
ll L;
ll ansl[N], ansr[N];
mt19937 mtrnd(0x114514);
map<pair<int, ll>, int> mem;

ll query(int i, ll x) {
	if(mem.count(mp(i, x))) return mem[mp(i, x)];
	cout << "? " << i << " " << x << endl;
	ll ret; cin >> ret; return mem[mp(i, x)] = ret;
}

ll getpos(int i, ll y) {
	ll x = 0;
	per(j, 0, 4) if(query(i, x | 1ll << j) < y) x |= 1ll << j;
	return x + 1;
}

void solve(vector<int> v, int l, int r, ll ql, ll qr) {
	if(v.size() == 1) {
		int i = v[0];
		ansl[i] = ql, ansr[i] = qr;
		return;
	}
	vector<int> vl, vr;
	int mid = (l + r) >> 1;
	ll y = L / n * mid;
	ll qmid = -1;
	do {
		int i = v[mtrnd() % v.size()];
		ll x = getpos(i, y);
		qmid = x;
		vector<int> v1, v2;
		bool eq = 1;
		for(int j : v) {
			ll r = query(j, x);
			if(r >= y) v1.pb(j);
			else v2.pb(j);
			eq &= r == y;
		}
		if(eq) {
			int d = mid-l+1 - vl.size();
			vl.insert(vl.end(), v.begin(), v.begin() + d);
			vr.insert(vr.end(), v.begin() + d, v.end());
			assert(vl.size() + vr.size() == r-l+1);
		} else {
			v.clear();
			if(vl.size() + v1.size() <= mid-l+1) vl.insert(vl.end(), v1.begin(), v1.end());
			else v.insert(v.end(), v1.begin(), v1.end());
			if(vr.size() + v2.size() <= r-mid) vr.insert(vr.end(), v2.begin(), v2.end());
			else v.insert(v.end(), v2.begin(), v2.end());
		}
	} while(vl.size() + vr.size() != r-l+1);
	solve(vl, l, mid, ql, qmid);
	solve(vr, mid+1, r, qmid, qr);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	int N, M;
	cin >> N >> M;
	rep(i, 1, N) rep(j, 1, M) cin >> mem[mp(i, j)];

	cin >> n >> L;
	vector<int> v;
	rep(i, 1, n) v.pb(i);
	solve(v, 1, n, 0, (ll)1e18);
	cout << "!" << "\n";
	rep(i, 1, n) {
		cout << ansl[i] << " " << ansr[i] << "\n";
	}
	cout.flush();
	
	return 0;
}
